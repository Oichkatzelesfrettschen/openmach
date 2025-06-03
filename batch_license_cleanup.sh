#!/bin/bash
# batch_license_cleanup.sh - License cleanup for specific directories

cd "$(git rev-parse --show-toplevel)" || exit 1

echo "Starting batch license cleanup for ./kernel/ and ./libmach/ ..."
FILES_PROCESSED_COUNT=0
# General pattern for the copyright line
LICENSE_PATTERN_GENERAL="Copyright.*The University of Utah"
# Number of lines to remove for the header
LICENSE_LINES_TO_REMOVE=18

# Define target directories
TARGET_DIRS=( "./kernel/" "./libmach/" )

for dir in "${TARGET_DIRS[@]}"; do
    echo "Processing directory: $dir"
    # Process C and Header files
    find "$dir" -type f \( -name "*.c" -o -name "*.h" \) -print0 | while IFS= read -r -d $'\0' file; do
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

    # Process Assembly files (.S)
    find "$dir" -type f -name "*.S" -print0 | while IFS= read -r -d $'\0' file; do
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
done

echo "Batch license cleanup complete."
echo "Total C/H and .S files processed in ./kernel/ and ./libmach/: $FILES_PROCESSED_COUNT"
echo "Total C/H and .S files processed in ./kernel/ and ./libmach/: $FILES_PROCESSED_COUNT" > batch_license_cleanup_report.txt

echo "Sample of cleaned C file from ./kernel/ (if any was processed):"
first_c_file=$(find ./kernel/ -name "*.c" -print -quit)
if [ -n "$first_c_file" ]; then
    if grep -q "SPDX-License-Identifier: Utah-BSD-Style" "$first_c_file"; then
        head -n 10 "$first_c_file"
    else
        echo "$first_c_file was not processed or did not contain the SPDX header."
    fi
else
    echo "No C files found in ./kernel/ to sample."
fi
