#!/bin/bash
set -e
set -x

# Navigate to the i386 directory
cd i386

# Run the configure script
if ./configure; then
  echo "Configure script completed successfully."
else
  echo "Configure script failed. Exiting."
  # Cat config.log for debugging
  cat config.log
  exit 1
fi

# Attempt to build mig first
if make -C mig; then
  echo "mig build completed successfully."
else
  echo "mig build failed. Exiting."
  exit 1
fi

# Attempt to build the system
if make; then
  echo "Build completed successfully."
else
  echo "Build failed. See output for errors."
  # The 'make' command will output errors to stdout/stderr,
  # which will be captured by the subtask runner.
  exit 1
fi
