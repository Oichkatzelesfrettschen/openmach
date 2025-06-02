#!/bin/bash
set -e
set -x

# Install essential build tools
sudo apt-get update && sudo apt-get install -y flex bison autoconf

# --- Helper function to apply sed changes ---
apply_change() {
    local file="$1"
    local sed_expr="$2"
    local grep_check_pattern="$3" # Pattern to check if change is already applied
    local tmp_file=$(mktemp)

    # Check if the change is already applied to prevent duplicate changes
    if ! grep -qF -- "$grep_check_pattern" "$file"; then
        sed "$sed_expr" "$file" > "$tmp_file" && mv "$tmp_file" "$file"
        echo "Applied change to $file: $grep_check_pattern"
    else
        echo "Change already applied to $file: $grep_check_pattern"
    fi
    rm -f "$tmp_file"
}

# 1. Modify mig/migcom.c
# Add #include <string.h>
apply_change "mig/migcom.c" "1i\#include <string.h>" "#include <string.h>"
# Change void main to int main
apply_change "mig/migcom.c" "s/void main(int argc, char \*\*argv)/int main(int argc, char **argv)/" "int main(int argc, char **argv)"

# Add return 0; at the end of main if not exiting
if ! tail -n 10 "mig/migcom.c" | sed '/^\s*\*\//d; /^\s*\/\//d' | grep -E -q "(\breturn\b|\bexit\b\s*\()"; then
    sed -i '$i\return 0;' mig/migcom.c
    echo "Added return 0; to mig/migcom.c"
else
    echo "Skipping adding return 0; to mig/migcom.c as exit() or return likely present."
fi


# 2. Attempt to build mig with debug symbols
echo "Attempting to build mig with debug symbols..."

# Modify i386/Makeconf.in to add -g to HOST_CFLAGS
apply_change "i386/Makeconf.in" "/^HOST_CFLAGS[ \t]*=/ s/$/ -g/" "HOST_CFLAGS.*-g"

# Rebuild mig first
echo "Rebuilding mig..."
# Clean previous mig build to ensure new flags are used
if ! make -C i386/mig clean; then
    echo "make clean for mig failed, but continuing."
fi

# Regenerate configure script in i386 directory due to configure.in changes
echo "Running autoreconf in i386 directory..."
if ! (cd i386 && autoreconf -fvi); then
    echo "autoreconf in i386 failed. Exiting."
    exit 1
fi

# Configure i386 first to regenerate Makefiles including i386/mig/Makefile from Makefile.in
echo "Running configure in i386 directory..."
if ! (cd i386 && ./configure --with-mach4=../); then
    echo "Configure script failed in i386. Exiting."
    cat i386/config.log
    exit 1
fi

echo "Building mig in i386/mig directory..."
if ! make -C i386/mig; then
    echo "Failed to rebuild mig with debug symbols."
    exit 1
fi
echo "mig rebuilt successfully with debug symbols."

# 3. Re-attempt the full build
cd i386

echo "Attempting full build again..."
# Enable core dumps
ulimit -c unlimited
echo "Core dump enabled. Pattern: $(cat /proc/sys/kernel/core_pattern 2>/dev/null || echo 'permission denied to read core_pattern')"
echo "Working directory: $(pwd)"

if make VERBOSE=1; then
  echo "Build completed successfully."
else
  echo "Build failed. See output for errors."
  echo "Checking for core dumps in the current directory (i386) and subdirectories..."
  find . -name 'core*' -ls

  # --- GDB Analysis ---
  echo "Attempting GDB analysis..."
  if ! command -v gdb &> /dev/null
  then
      echo "gdb not found, installing..."
      # sudo apt-get update && sudo apt-get install -y gdb # Already done at the top
  fi

  MIG_COMPILED_EXEC="/app/i386/mig/migcom"
  # Try to find a core file, prioritizing more specific paths if they exist
  CORE_FILE=""
  if [ -f "/app/i386/libmach/core" ]; then
    CORE_FILE="/app/i386/libmach/core"
  elif find . -name 'core*' -print -quit | read -r found_core_file; then
    CORE_FILE="$found_core_file"
  fi


  if [ -f "$MIG_COMPILED_EXEC" ] && [ -n "$CORE_FILE" ] && [ -f "$CORE_FILE" ]; then
    echo "Running GDB on migcom with core dump: $CORE_FILE"
    gdb -q "$MIG_COMPILED_EXEC" "$CORE_FILE" -ex "set pagination off" -ex "bt" -ex "quit"
  else
    echo "GDB analysis skipped: migcom executable or core file not found."
    echo "MIG_COMPILED_EXEC: $MIG_COMPILED_EXEC (exists: $(test -f $MIG_COMPILED_EXEC && echo yes || echo no))"
    echo "CORE_FILE: $CORE_FILE (exists: $(test -n "$CORE_FILE" && test -f "$CORE_FILE" && echo yes || echo no))"
  fi

  exit 1
fi
