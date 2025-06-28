#!/bin/bash
# revised_license_cleanup.sh - More aggressive license removal

# Ensure we are in the root of the repository for find
cd "$(git rev-parse --show-toplevel)" || exit 1

echo "Starting revised license cleanup..."
FILES_PROCESSED_COUNT=0
# Pattern for the first line of the license header
# Making it slightly more flexible with grep -E for potential whitespace variations
LICENSE_PATTERN_FIRST_LINE="Copyright (c) 1994 The University of Utah"
# Number of lines to remove for the header
# The Board mentioned 18 lines. This is critical.
LICENSE_LINES_TO_REMOVE=18

# Process C and Header files
find . -type f \( -name "*.c" -o -name "*.h" \) -print0 | while IFS= read -r -d $'\0' file; do
    # Check if file has the first line of the license header
    # Using grep -m 1 to only check the beginning of the file quickly
    if head -n "$LICENSE_LINES_TO_REMOVE" "$file" | grep -qE "$LICENSE_PATTERN_FIRST_LINE"; then
        echo "Processing: $file"

        # Remove first N lines (license header)
        # tail -n +K starts printing from line K. So + (N+1)
        tail -n "+$(($LICENSE_LINES_TO_REMOVE + 1))" "$file" > "$file.tmp"

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
        # For debugging, let's see the first line of files that don't match
        # echo "Skipping $file: First line pattern not found. Head:"
        # head -n 1 "$file"
        : # Do nothing
    fi
done

echo "Revised license cleanup complete."
echo "Total C/H files processed: $FILES_PROCESSED_COUNT"
# Create a simple report file
echo "Total C/H files processed: $FILES_PROCESSED_COUNT" > revised_license_cleanup_report.txt

# Verify a few files
echo "Sample of cleaned file (first 10 lines of a C file if any was processed):"
first_c_file=$(find . -name "*.c" -print -quit)
if [ -n "$first_c_file" ]; then
    if grep -q "SPDX-License-Identifier: Utah-BSD-Style" "$first_c_file"; then
        head -n 10 "$first_c_file"
    else
        echo "First C file $first_c_file does not seem to have the new header. It might not have matched the old pattern."
        echo "First few lines of $first_c_file are:"
        head -n 5 "$first_c_file"
    fi
else
    echo "No C files found to sample."
fi
