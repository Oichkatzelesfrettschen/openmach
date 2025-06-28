#!/bin/bash
# license_modernization.sh - SPDX-compliant license transformation

# Step 1 is done by creating LICENSE file manually before running this script.

# Step 2: Transform all source files
# Ensure we are in the root of the repository for find
cd "$(git rev-parse --show-toplevel)" || exit 1

echo "Starting license transformation..."
FILES_PROCESSED_COUNT=0
# Process C and Header files
find . -type f \( -name "*.c" -o -name "*.h" \) -print0 | while IFS= read -r -d $'\0' file; do
    # Check if the file likely contains the old license header
    # Looking for a few distinct phrases from the license
    if grep -q "Copyright (c) 1994 The University of Utah" "$file" && \
       grep -q "THE UNIVERSITY OF UTAH AND CSL ALLOW FREE USE" "$file" && \
       grep -q "Author: Bryan Ford, University of Utah CSL" "$file"; then

        echo "Processing: $file"
        # Extract content after the license block.
        # The awk script looks for the first line NOT starting with '#' or '/*' or empty,
        # or a line containing 'Author:', and then starts printing.
        # This is tricky because the license block itself has lines not starting with #
        # A more robust way is to count lines if the header is very regular,
        # or use a more complex marker. The prompt implies 18 lines for the *other* script.
        # Let's assume the license block is identifiable and we need to skip past it.
        # The provided awk '/^[^#]/{p=1} p' is a bit too simple if comments exist before code.
        # A common pattern is that the first non-comment, non-empty line is code.
        # For this specific license, it seems to be mostly comments.
        # Let's try to find the line after "Author: Bryan Ford, University of Utah CSL"

        # Find line number of "Author: Bryan Ford, University of Utah CSL"
        # Add 1 to get the line number *after* it.
        # Add another 1 because tail -n +K starts from line K.
        # This assumes the "Author:" line is the last meaningful line of the header.
        author_line_num=$(grep -n "Author: Bryan Ford, University of Utah CSL" "$file" | cut -d: -f1)

        if [ -n "$author_line_num" ] && [ "$author_line_num" -gt 0 ]; then
            # Determine if there's an empty line or specific comment end after author line
            # For simplicity, let's assume we skip author_line_num lines.
            # If the file only contains the license, tail might produce nothing.

            # Create temp file for content *after* license
            tail -n "+$(($author_line_num + 1))" "$file" > "$file.tmp"

            # Prepend SPDX identifier and new reference
            {
                echo "/* SPDX-License-Identifier: Utah-BSD-Style */"
                echo "/* See LICENSE file for full copyright notice */"
                echo "" # Add a blank line for separation
                cat "$file.tmp"
            } > "$file.new"

            mv "$file.new" "$file"
            rm "$file.tmp"
            FILES_PROCESSED_COUNT=$((FILES_PROCESSED_COUNT + 1))
        else
            echo "Skipping $file: 'Author:' line not found or license pattern mismatch."
        fi
    else
        echo "Skipping $file: Does not appear to contain the full old license."
    fi
done

# Process Assembly files (.S) separately if needed, SPDX comment style for ASM is different
# For now, focusing on C/H as per original prompt for this script.
# find . -type f \( -name "*.S" \) -print0 | while IFS= read -r -d $'\0' file; do ... done

echo "License modernization complete."
echo "Total C/H files processed: $FILES_PROCESSED_COUNT"
# Create a simple report file
echo "Total C/H files processed: $FILES_PROCESSED_COUNT" > license_cleanup_report.txt

# Verify a few files
echo "Sample of cleaned file (first 10 lines of a C file if any was processed):"
first_c_file=$(find . -name "*.c" -print -quit)
if [ -n "$first_c_file" ]; then
    if grep -q "SPDX-License-Identifier: Utah-BSD-Style" "$first_c_file"; then
        head -n 10 "$first_c_file"
    else
        echo "First C file $first_c_file does not seem to have the new header."
    fi
else
    echo "No C files found to sample."
fi
