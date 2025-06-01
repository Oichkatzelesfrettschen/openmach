#!/bin/bash
set -e
set -x

# This script assumes it's being run from the i386 directory.

# Ensure critical autotools are installed
if ! command -v aclocal || ! command -v autoheader || ! command -v autoconf; then
    echo "Autotools not found, attempting to install..."
    sudo apt-get update -y
    sudo apt-get install -y autoconf automake
    if ! command -v aclocal || ! command -v autoheader || ! command -v autoconf; then
        echo "ERROR: Failed to install autotools. Please install them manually."
        exit 1
    fi
    echo "Autotools installed successfully."
fi

# Check if configure.ac exists (it should be part of the repo state for this subtask)
if [ ! -f "configure.ac" ]; then
    echo "ERROR: configure.ac not found in current directory (expected i386/). Please ensure it exists."
    exit 1
fi

echo "--- Running aclocal ---"
aclocal --version
# Removed -I ../../m4 as it does not exist. -I ../../ for top-level aclocal.m4.
aclocal -I /usr/share/aclocal -I ../../
if [ $? -ne 0 ]; then echo "aclocal failed"; exit 1; fi
echo "aclocal completed."
ls -l aclocal.m4

echo "--- Running autoheader ---"
autoheader --version
autoheader
if [ $? -ne 0 ]; then echo "autoheader failed"; exit 1; fi
echo "autoheader completed."
ls -l config.h.in

echo "--- Running autoconf ---"
autoconf --version
autoconf
if [ $? -ne 0 ]; then
    echo "autoconf failed"
    # Try to show relevant part of configure.ac if autoconf fails early
    head -n 50 configure.ac || true
    exit 1;
fi
echo "autoconf completed."
ls -l configure

echo "--- Making new configure script executable ---"
chmod +x configure

echo "--- Running the new ./configure script ---"
# Backup old config.log and config.status if they exist
mv config.log config.log.old || true
mv config.status config.status.old || true

# Run configure. Capture stdout and stderr to a log file as well as printing them.
./configure --with-mach4=.. > configure_run.log 2>&1
configure_exit_status=$?

echo "--- Configure script execution finished. Exit status: $configure_exit_status ---"
echo "--- Configure log (configure_run.log): ---"
cat configure_run.log
echo "--- End of Configure log ---"

if [ $configure_exit_status -ne 0 ]; then
    echo "New ./configure script failed."
    if [ -f config.log ]; then
        echo "--- Dumping config.log for error details: ---"
        cat config.log
        echo "--- End of config.log ---"
    fi
    exit 1
fi
echo "New ./configure script completed successfully."


# Now, proceed with the build attempt
if [ ! -f "Makefile" ] || [ ! -f "Makeconf" ] || [ ! -f "config.h" ]; then
    echo "ERROR: Critical configuration files (Makefile, Makeconf, config.h) still not found after running configure."
    exit 1
fi

echo "--- Attempting to build the system with the new Autoconf configuration ---"

ulimit -c unlimited
echo "Core dump pattern: $(cat /proc/sys/kernel/core_pattern || echo 'not available')"

if make VERBOSE=1; then
  echo "Build completed successfully!"
  echo "This is unexpected, as _setjmp.S errors were anticipated."
else
  build_exit_status=$?
  echo "Build failed with exit status: $build_exit_status"
  echo "This might be the expected assembly errors, or something new."
  echo "Checking for core dumps (primarily interested if mig crashed again)..."
  find . -maxdepth 2 -name 'core*' -ls

  if [ ! -f "libmach/c/_setjmp.o" ]; then
    echo "_setjmp.o was NOT created. Failure likely occurred before or during its compilation."
  else
    echo "_setjmp.o EXISTS. Failure likely occurred at or after its compilation."
  fi
  exit 1
fi

echo "Subtask completed."
