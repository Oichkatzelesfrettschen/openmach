#!/bin/bash
# final_license_cleanup.sh - Third attempt at license removal

cd "$(git rev-parse --show-toplevel)" || exit 1

echo "Starting final license cleanup..."
FILES_PROCESSED_COUNT=0
# General pattern for the copyright line
LICENSE_PATTERN_GENERAL="Copyright.*The University of Utah" # Made it more general
# Number of lines to remove for the header, as per The Board's repeated assertion
LICENSE_LINES_TO_REMOVE=18

# Process C and Header files
find . -type f \( -name "*.c" -o -name "*.h" \) -print0 | while IFS= read -r -d $'\0' file; do
    # Check if the file's *initial lines* contain the general license pattern
    # This avoids matching a random mention of "Copyright University of Utah" deep in a file.
    if head -n "${LICENSE_LINES_TO_REMOVE}" "$file" | grep -qE "$LICENSE_PATTERN_GENERAL"; then
        echo "Processing: $file"

        # Remove first N lines (license header)
        tail -n "+$(($LICENSE_LINES_TO_REMOVE + 1))" "$file" > "$file.tmp"

        # Prepend SPDX identifier and new reference
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
# Assembly comments are different (usually # or ; or @ depending on assembler)
# The original license uses #. So we can use similar logic.
# SPDX for assembly would be like: ; SPDX-License-Identifier: Utah-BSD-Style
# For simplicity, let's assume '#' is used for comments in these .S files,
# and apply a similar transformation.
find . -type f -name "*.S" -print0 | while IFS= read -r -d $'\0' file; do
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


echo "Final license cleanup complete."
echo "Total C/H and .S files processed: $FILES_PROCESSED_COUNT"
echo "Total C/H and .S files processed: $FILES_PROCESSED_COUNT" > final_license_cleanup_report.txt

echo "Sample of cleaned C file (first 10 lines if any was processed):"
first_c_file=$(find . -name "*.c" -print -quit)
if [ -n "$first_c_file" ]; then
    if grep -q "SPDX-License-Identifier: Utah-BSD-Style" "$first_c_file"; then
        head -n 10 "$first_c_file"
    else
        echo "$first_c_file was not processed or did not contain the SPDX header."
    fi
else
    echo "No C files found to sample."
fi

echo "Sample of cleaned Assembly file (first 10 lines if any was processed):"
first_S_file=$(find . -name "*.S" -print -quit)
if [ -n "$first_S_file" ]; then
    if grep -q "SPDX-License-Identifier: Utah-BSD-Style" "$first_S_file"; then
        head -n 10 "$first_S_file"
    else
        echo "$first_S_file was not processed or did not contain the SPDX header."
    fi
else
    echo "No .S files found to sample."
fi
