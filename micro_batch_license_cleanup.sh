#!/bin/bash
# micro_batch_license_cleanup.sh - License cleanup for a single small directory

cd "$(git rev-parse --show-toplevel)" || exit 1

echo "Starting micro-batch license cleanup for ./kernel/kern/ ..."
FILES_PROCESSED_COUNT=0
# General pattern for the copyright line
LICENSE_PATTERN_GENERAL="Copyright.*The University of Utah"
# Number of lines to remove for the header
LICENSE_LINES_TO_REMOVE=18

# Define target directory
TARGET_DIR="./kernel/kern/"

echo "Processing directory: $TARGET_DIR"
# Process C and Header files
find "$TARGET_DIR" -type f \( -name "*.c" -o -name "*.h" \) -print0 | while IFS= read -r -d $'\0' file; do
    # Check if file's *initial lines* contain the general license pattern
    if head -n "${LICENSE_LINES_TO_REMOVE}" "$file" | grep -qE "$LICENSE_PATTERN_GENERAL"; then
        echo "Processing: $file"

        tail -n "+$(($LICENSE_LINES_TO_REMOVE + 1))" "$file" > "$file.tmp"

        {
            echo "/* SPDX-License-Identifier: Utah-BSD-Style */"
            echo "/* See LICENSE file for full copyright notice */"
            echo ""
            cat "$file.tmp"
        } > "$file.new"

        mv "$file.new" "$file"
        rm "$file.tmp"
        FILES_PROCESSED_COUNT=$((FILES_PROCESSED_COUNT + 1))
    fi
done

# Process Assembly files (.S) in this directory (if any)
find "$TARGET_DIR" -type f -name "*.S" -print0 | while IFS= read -r -d $'\0' file; do
    if head -n "${LICENSE_LINES_TO_REMOVE}" "$file" | grep -qE "$LICENSE_PATTERN_GENERAL"; then
        echo "Processing Assembly file: $file"

        tail -n "+$(($LICENSE_LINES_TO_REMOVE + 1))" "$file" > "$file.tmp"

        {
            echo "# SPDX-License-Identifier: Utah-BSD-Style"
            echo "# See LICENSE file for full copyright notice"
            echo ""
            cat "$file.tmp"
        } > "$file.new"

        mv "$file.new" "$file"
        rm "$file.tmp"
        FILES_PROCESSED_COUNT=$((FILES_PROCESSED_COUNT + 1))
    fi
done

echo "Micro-batch license cleanup complete."
echo "Total C/H and .S files processed in $TARGET_DIR: $FILES_PROCESSED_COUNT"
echo "Total C/H and .S files processed in $TARGET_DIR: $FILES_PROCESSED_COUNT" > micro_batch_license_cleanup_report.txt

echo "Sample of a cleaned C file from $TARGET_DIR (if any was processed):"
first_c_file=$(find "$TARGET_DIR" -name "*.c" -print -quit)
if [ -n "$first_c_file" ]; then
    if grep -q "SPDX-License-Identifier: Utah-BSD-Style" "$first_c_file"; then
        echo "Displaying first 10 lines of $first_c_file:"
        head -n 10 "$first_c_file"
    else
        echo "$first_c_file was not processed or did not contain the SPDX header."
    fi
else
    echo "No C files found in $TARGET_DIR to sample."
fi
