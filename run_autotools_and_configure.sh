#!/bin/bash
set -e
set -x

# Ensure critical autotools are installed
if ! command -v aclocal || ! command -v autoheader || ! command -v autoconf; then
    echo "Autotools not found, attempting to install..."
    sudo apt-get update -y
    sudo apt-get install -y autoconf automake
    # Verify installation
    if ! command -v aclocal || ! command -v autoheader || ! command -v autoconf; then
        echo "ERROR: Failed to install autotools. Please install them manually."
        exit 1
    fi
    echo "Autotools installed successfully."
fi

# This subtask assumes i386/configure.ac was successfully created by the previous subtask.
if [ ! -f "i386/configure.ac" ]; then
    echo "ERROR: i386/configure.ac not found. Please ensure it was generated."
    exit 1
fi

# Navigate to the i386 directory
cd i386

echo "--- Running aclocal ---"
aclocal --version
# Removed -I ../../m4 as it does not exist and causes errors.
# -I ../../ is for top-level aclocal.m4, -I /usr/share/aclocal for system macros.
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
if [ $? -ne 0 ]; then echo "autoconf failed"; exit 1; fi
echo "autoconf completed."
ls -l configure

echo "--- Making new configure script executable ---"
chmod +x configure

echo "--- Running the new ./configure script ---"
# Backup old config.log and config.status if they exist
mv config.log config.log.old || true
mv config.status config.status.old || true

# Run configure. Capture stdout and stderr to a log file as well as printing them.
# The --with-mach4=.. argument correctly points to the top-level for generic sources.
./configure --with-mach4=.. > configure_run.log 2>&1
configure_exit_status=$?

echo "--- Configure script execution finished. Exit status: $configure_exit_status ---"
echo "--- Configure log (configure_run.log): ---"
cat configure_run.log
echo "--- End of Configure log ---"

if [ $configure_exit_status -ne 0 ]; then
    echo "New ./configure script failed."
    # config.log is the standard place for autoconf failure details
    if [ -f config.log ]; then
        echo "--- Dumping config.log for error details: ---"
        cat config.log
        echo "--- End of config.log ---"
    fi
    exit 1
fi

echo "New ./configure script completed successfully."
echo "--- Generated/updated files: ---"
# Use find to robustly list files even if some directories don't exist yet (though configure should create them)
find . -maxdepth 2 \( -name Makeconf -o -name Makefile -o -name config.status -o -name config.log -o -name config.h \) -ls | sort

echo "Subtask completed."
