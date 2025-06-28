#!/bin/bash
set -e
set -x

# --- Helper function to apply sed changes ---
apply_change() {
    local file="$1"
    local sed_expr="$2"
    local tmp_file=$(mktemp)
    # Use a unique marker for grep to check if change is applied
    local check_marker="$3"

    # Check if the change is already applied to prevent duplicate changes
    # Using a simple grep for a unique part of the sed expression or a comment
    if ! grep -qF -- "$check_marker" "$file"; then
        sed -i.bak "$sed_expr" "$file" # -i.bak for in-place with backup
        echo "Applied change to $file: $check_marker"
    else
        echo "Change already applied to $file (marker '$check_marker' found)"
    fi
    rm -f "$tmp_file" # mktemp file not used if sed -i is used
}

# 1. Modify mig/Makerules to add -g for linking migcom
# The compilation of objects for migcom should get -g via HOST_CFLAGS from Makeconf.in
# Target link line: $(HOST_CC) $(CPPFLAGS) $(CFLAGS) $(HOST_CFLAGS) -o $@ $^ $(LEXLIB)
# Desired link line: $(HOST_CC) -g $(CPPFLAGS) $(CFLAGS) $(HOST_CFLAGS) -o $@ $^ $(LEXLIB)
apply_change "mig/Makerules" \
    "s/\$(HOST_CC) \$(CPPFLAGS) \$(CFLAGS) \$(HOST_CFLAGS) -o \$@/\$(HOST_CC) -g \$(CPPFLAGS) \$(CFLAGS) \$(HOST_CFLAGS) -o \$@/g" \
    "\$(HOST_CC) -g \$(CPPFLAGS)"

# 2. Modify mig/utils.c, function WritePackMsgType
# Add debug prints. This needs careful sed work to insert lines.
# Marker for this change: DEBUG MIG: WritePackMsgType
debug_print_code='fprintf(stderr, "DEBUG MIG: WritePackMsgType: left = [%p] \\"%s\\"\\n", (void*)left, left); fflush(stderr); fprintf(stderr, "DEBUG MIG: WritePackMsgType: right = [%p] \\"%s\\"\\n", (void*)right, right); fflush(stderr);'

# Check if already applied
if ! grep -qF "DEBUG MIG: WritePackMsgType: left" "mig/utils.c"; then
    # Insert after "va_start(pvar, right);"
    awk -v insert_point_pattern="va_start(pvar, right);" \
        -v code_to_insert="$debug_print_code" \
        '{ print } /va_start\(pvar, right\);/ { print code_to_insert }' \
        "mig/utils.c" > "mig/utils.c.tmp" && mv "mig/utils.c.tmp" "mig/utils.c"
    echo "Applied debug prints to mig/utils.c"
else
    echo "Debug prints already in mig/utils.c"
fi

# 3. Rebuild mig
echo "Rebuilding mig (make -C i386/mig clean && make -C i386/mig)"
# Need to ensure i386/mig/Makefile exists from a configure run.
# The i386/configure script generates i386/Makeconf (from Makeconf.in)
# and i386/mig/Makefile (from i386/mig/Makefile.in).
# HOST_CFLAGS with -g should be set in i386/Makeconf by a previous script's modification
# to i386/Makeconf.in. If not, that needs to be ensured.
# For this script, we assume i386/Makeconf.in is already correctly adding -g to HOST_CFLAGS.

echo "Ensuring i386 is configured..."
if [ ! -f "i386/Makefile" ] || [ ! -f "i386/mig/Makefile" ]; then
    echo "Running configure in i386..."
    if ! (cd i386 && ./configure); then
        echo "Configure script failed in i386. Exiting."
        cat i386/config.log # Try to get config.log content
        exit 1
    fi
else
    echo "i386 and i386/mig Makefiles already exist."
fi

# It's important that Makeconf has HOST_CFLAGS += -g from i386/Makeconf.in
# This should have been done by the previous script (debug_build.sh)
# If we want to be certain, we can re-apply it here.
apply_change "i386/Makeconf.in" "/^HOST_CFLAGS[ \t]*=/ s/$/ -g/" "HOST_CFLAGS.*-g"
# And then re-run configure to be absolutely sure Makeconf is updated
if (cd i386 && ./configure); then
    echo "i386 configure run successfully."
else
    echo "i386 configure failed after ensuring HOST_CFLAGS in Makeconf.in. Exiting."
    cat i386/config.log
    exit 1
fi


if ! make -C i386/mig clean; then
    echo "make clean for mig failed, but continuing."
fi
if ! make -C i386/mig; then
    echo "Failed to rebuild mig."
    exit 1
fi
echo "mig rebuilt."

# 4. Attempt full build
echo "Attempting full build in i386..."
cd i386
# ./configure should have been run by previous step or above.

ulimit -c unlimited # Enable core dumps
echo "Core dump pattern: $(cat /proc/sys/kernel/core_pattern || echo 'not available')"
echo "Working directory for make: $(pwd)"

if make VERBOSE=1; then
  echo "Build completed successfully."
else
  echo "Build failed. See output for errors."
  echo "Checking for core dumps in the current directory (i386) and subdirectories..."
  find . -name 'core*' -ls
  # Try to get gdb backtrace if core dump and gdb are available
  if command -v gdb &> /dev/null; then
    core_file=$(find . -name 'core*' -print -quit) # find the first core file
    if [ -n "$core_file" ] && [ -f "$core_file" ]; then # check if found and is a file
        echo "Attempting GDB backtrace for $core_file with mig/migcom"
        # GDB is run from i386 directory, so path to migcom is mig/migcom
        gdb --batch -ex "bt full" -ex "thread apply all bt full" -ex "quit" "mig/migcom" "$core_file"
    else
        echo "No core file found or core_file variable is empty."
    fi
  else
    echo "gdb not available."
  fi
  exit 1
fi
