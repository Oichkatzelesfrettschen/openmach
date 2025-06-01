#!/bin/bash
set -e
set -x

# --- Helper function to apply sed changes ---
apply_change() {
    local file="$1"
    local sed_expr="$2"
    local tmp_file=$(mktemp)
    local check_marker="$3"

    if ! grep -qF -- "$check_marker" "$file"; then
        sed -i.bak "$sed_expr" "$file"
        echo "Applied change to $file: $check_marker"
    else
        echo "Change already applied to $file (marker '$check_marker' found)"
    fi
    rm -f "$tmp_file"
}

# 1. Ensure migcom is built with debug symbols
# Modify i386/Makeconf.in for HOST_CFLAGS (for object files)
apply_change "i386/Makeconf.in" "/^HOST_CFLAGS[ \t]*=/ s/$/ -g/" "HOST_CFLAGS.*-g"

# Modify mig/Makerules for migcom linking
apply_change "mig/Makerules" \
    "s/\$(HOST_CC) \$(CPPFLAGS) \$(CFLAGS) \$(HOST_CFLAGS) -o \$@/\$(HOST_CC) -g \$(CPPFLAGS) \$(CFLAGS) \$(HOST_CFLAGS) -o \$@/g" \
    "\$(HOST_CC) -g \$(CPPFLAGS)"

# 2. Add debug print in mig/server.c:WriteRoutine
# Marker for this change: DEBUG MIG: WriteRoutine: Processing routine
# Corrected to use rt->rtRetCode->argName and check for NULL pointers
routine_debug_code='fprintf(stderr, "DEBUG MIG: WriteRoutine: Processing routine: %s, rtRetCode->argName: %s\\n", rt->rtName, (rt->rtRetCode && rt->rtRetCode->argName) ? rt->rtRetCode->argName : "NULL"); fflush(stderr);'

# Corrected to use rt->rtRetCode->argName and check for NULL pointers
routine_debug_code='fprintf(stderr, "DEBUG MIG: WriteRoutine: Processing routine: %s, rtRetCode->argName: %s\\n", rt->rtName, (rt->rtRetCode && rt->rtRetCode->argName) ? rt->rtRetCode->argName : "NULL"); fflush(stderr);'

# Clean any previous "DEBUG MIG: WriteRoutine" lines from mig/server.c
echo "Cleaning old WriteRoutine debug prints from mig/server.c..."
sed -i.bak '/DEBUG MIG: WriteRoutine: Processing routine/d' "mig/server.c"
echo "Old WriteRoutine debug prints cleaned."

# Now, apply the correct debug print.
echo "Applying debug prints to mig/server.c:WriteRoutine"
# Insert after the opening brace of WriteRoutine
awk -v code_to_insert="$routine_debug_code" \
    'BEGIN{found_func=0; printed=0}
        {
            # Match the function signature
            if (index($0, "WriteRoutine(FILE *file, register const routine_t *rt)") > 0) {
                found_func=1;
                print $0;
                next;
            }
            # If signature found and current line is the opening brace
            if (found_func && $0 ~ /^\s*{\s*$/) {
                print $0;
                print code_to_insert;
                printed=1;
                found_func=0;
                next;
            }
            print $0;
        }' \
        "mig/server.c" > "mig/server.c.tmp" && mv "mig/server.c.tmp" "mig/server.c"
echo "Verifying change in mig/server.c:"
grep 'rtRetCode->argName) ? rt->rtRetCode->argName : "NULL"' mig/server.c || echo "DEBUG PRINT FOR WriteRoutine NOT APPLIED CORRECTLY"


# 3. Keep existing debug prints for WriteEpilog and WritePackMsgType
# These should ideally also be restored if they get messed up, but for now,
# the focus is WriteRoutine. We assume they are okay or re-applied correctly
# by their own checks if they were somehow removed.
epilog_debug_marker="DEBUG MIG: WriteEpilog: About to call WritePackMsgType"
if ! grep -qF "$epilog_debug_marker" "mig/server.c"; then
    epilog_debug_insertion_point='WritePackMsgType(file, itRetCodeType,'
    epilog_debug_code='fprintf(stderr, "DEBUG MIG: WriteEpilog: About to call WritePackMsgType\\n"); fflush(stderr); fprintf(stderr, "DEBUG MIG: WriteEpilog: left_arg_ptr = [%p] pointing to: \\"%s\\"\\n", (void*)"OutP->RetCodeType", "OutP->RetCodeType"); fflush(stderr); fprintf(stderr, "DEBUG MIG: WriteEpilog: right_arg_ptr = [%p] pointing to: \\"%s\\"\\n", (void*)"RetCodeType", "RetCodeType"); fflush(stderr);'
    # Note: This awk script for WriteEpilog is simpler and might add duplicates if run multiple times
    # without a .bak restore for server.c or a more precise check_marker.
    awk -v insert_point_pattern="$epilog_debug_insertion_point" -v code_to_insert="$epilog_debug_code" 'BEGIN{found=0} { if (index($0, insert_point_pattern) > 0 && !found) { print code_to_insert; found=1; } print $0; }' "mig/server.c" > "mig/server.c.tmp" && mv "mig/server.c.tmp" "mig/server.c"
    echo "Re-applied debug prints to mig/server.c:WriteEpilog"
else
    echo "Debug prints for WriteEpilog already present in mig/server.c"
fi

utils_debug_marker="DEBUG MIG: WritePackMsgType: left"
if ! grep -qF "$utils_debug_marker" "mig/utils.c"; then
    utils_debug_insertion_point='va_start(pvar, right);'
    utils_debug_code='fprintf(stderr, "DEBUG MIG: WritePackMsgType: left = [%p] \\"%s\\"\\n", (void*)left, left); fflush(stderr); fprintf(stderr, "DEBUG MIG: WritePackMsgType: right = [%p] \\"%s\\"\\n", (void*)right, right); fflush(stderr);'
    awk -v insert_point_pattern="$utils_debug_insertion_point" -v code_to_insert="$utils_debug_code" '{ print } /va_start\(pvar, right\);/ { print code_to_insert }' "mig/utils.c" > "mig/utils.c.tmp" && mv "mig/utils.c.tmp" "mig/utils.c"
    echo "Re-applied debug prints to mig/utils.c:WritePackMsgType"
else
    echo "Debug prints for WritePackMsgType already present in mig/utils.c"
fi


# 4. Configure i386 (after potential Makeconf.in changes) and Rebuild mig
echo "Configuring i386 and rebuilding mig..."
cd i386
if ! ./configure; then
    echo "Configure script failed in i386. Exiting."
    cat config.log
    exit 1
fi
cd ..

if ! make -C i386/mig clean; then echo "make clean for mig failed, but continuing."; fi
if ! make -C i386/mig; then echo "Failed to rebuild mig."; exit 1; fi
echo "mig rebuilt."

# 5. Attempt full build
echo "Attempting full build in i386..."
cd i386

ulimit -c unlimited
echo "Core dump pattern: $(cat /proc/sys/kernel/core_pattern || echo 'not available')"

if make VERBOSE=1; then
  echo "Build completed successfully."
else
  echo "Build failed. See output for errors."
  echo "Checking for core dumps..."
  find . -name 'core*' -ls
  if command -v gdb &> /dev/null; then
    core_file=$(find . -name 'core*' -print -quit)
    migcom_path="mig/migcom"
    if [ -f "$migcom_path" ] && [ -n "$core_file" ] && [ -f "$core_file" ]; then
        echo "Attempting GDB backtrace for $core_file with $migcom_path"
        gdb --batch -ex "bt full" -ex "thread apply all bt full" -ex "quit" "$migcom_path" "$core_file"
    else
        echo "No core file found, migcom not found at $migcom_path, or core_file variable is empty."
    fi
  else
    echo "gdb not available."
  fi
  exit 1
fi
