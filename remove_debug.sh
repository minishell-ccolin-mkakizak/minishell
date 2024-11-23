#!/bin/bash

# Find relevant source files only
find . -type f \( -name "*.c" -o -name "*.h" \) | while IFS= read -r file; do
	# Check if the file is not empty
	if [[ -s "$file" ]]; then
		# Create a temporary file for safe processing
		tmp_file=$(mktemp)
		
		# Print and mark the lines containing " //debug" anywhere on the line
		grep "//debug" "$file" | while IFS= read -r line; do
			echo "Removed: $line"
		done
		
		# Remove lines containing "//debug" and save to the temporary file
		grep -v "//debug" "$file" > "$tmp_file"
		
		# Only replace the original file if the operation succeeds
		if [[ $? -eq 0 ]]; then
			mv "$tmp_file" "$file"
		else
			echo "Error processing: $file"
			rm "$tmp_file" # Cleanup the temporary file in case of failure
		fi
	fi
done

