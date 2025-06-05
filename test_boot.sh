#!/bin/bash
# OpenMach boot test harness

# Default image names, can be overridden by command line arguments
KERNEL_IMAGE_DEFAULT="kernel.bmod"
BOOTSTRAP_DEFAULT="bootstrap.bmod" # Or whatever the second module is named

KERNEL_IMAGE="${1:-$KERNEL_IMAGE_DEFAULT}"
BOOTSTRAP="${2:-$BOOTSTRAP_DEFAULT}"

# Path to mkbootimage - assuming it's in lib/mach-boot relative to project root
# This might need adjustment depending on where we run this script from
# or if mkbootimage is built elsewhere.
# For now, assume it's callable if we are in the i386 dir, or OPENMACH_ROOT is set.
MKBOOTIMAGE_PATH="${OPENMACH_ROOT:-..}/lib/mach-boot/mkbootimage"
# A more robust way might be to find it if OPENMACH_ROOT is set
if [ -n "$OPENMACH_ROOT" ] && [ -f "$OPENMACH_ROOT/lib/mach-boot/mkbootimage" ]; then
    MKBOOTIMAGE_PATH="$OPENMACH_ROOT/lib/mach-boot/mkbootimage"
elif [ -f "../lib/mach-boot/mkbootimage" ]; then # If run from i386 dir
    MKBOOTIMAGE_PATH="../lib/mach-boot/mkbootimage"
elif [ -f "./lib/mach-boot/mkbootimage" ]; then # If run from project root
    MKBOOTIMAGE_PATH="./lib/mach-boot/mkbootimage"
else
    echo "WARNING: mkbootimage not found at expected paths. Boot image creation might fail."
    echo "Please ensure mkbootimage is built and path is correct."
    # Attempt to find mkbootimage in the PATH as a last resort
    if command -v mkbootimage &>/dev/null; then
        MKBOOTIMAGE_PATH="mkbootimage"
    else
        MKBOOTIMAGE_PATH="mkbootimage_not_found" # Placeholder to cause error if not found
    fi
fi


OUTPUT_BOOT_IMAGE="test.boot"

# Check if kernel and bootstrap images exist
if [ ! -f "$KERNEL_IMAGE" ]; then
    echo "ERROR: Kernel image '$KERNEL_IMAGE' not found!"
    exit 1
fi
if [ ! -f "$BOOTSTRAP" ]; then
    echo "ERROR: Bootstrap image '$BOOTSTRAP' not found!"
    exit 1
fi

echo "Attempting to create boot image '$OUTPUT_BOOT_IMAGE' using $MKBOOTIMAGE_PATH..."
# Create boot image
"$MKBOOTIMAGE_PATH" -o "$OUTPUT_BOOT_IMAGE" "$KERNEL_IMAGE" "$BOOTSTRAP"
if [ $? -ne 0 ]; then
    echo "ERROR: mkbootimage failed to create '$OUTPUT_BOOT_IMAGE'."
    exit 1
fi
echo "Boot image '$OUTPUT_BOOT_IMAGE' created successfully."

echo "Launching QEMU..."
echo "Kernel: $KERNEL_IMAGE, Bootstrap: $BOOTSTRAP, Combined: $OUTPUT_BOOT_IMAGE"
echo "GDB will listen on tcp::1234. Connect with: gdb-multiarch $KERNEL_IMAGE (or the main kernel file if .bmod is just a module)"
echo "QEMU monitor on telnet:127.0.0.1:4444"

# Launch with maximum debugging
qemu-system-i386 \
    -kernel "$OUTPUT_BOOT_IMAGE" \
    -m 128M \
    -display none \
    -serial stdio \
    -monitor telnet:127.0.0.1:4444,server,nowait \
    -gdb tcp::1234 \
    -S  # Wait for GDB connection

# In another terminal:
# gdb-multiarch kernel.sym  # Assuming kernel.sym has symbols for kernel.bmod
# target remote :1234
# continue
