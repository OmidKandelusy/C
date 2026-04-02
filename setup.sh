#!/bin/bash

clear
echo "setting up the C repository"

# List all .c and .h files recursively from current directory
files=( $(find . -type f \( -name "*.c" -o -name "*.h" \)) )


count=0
for file in "${files[@]}"; do
    clang-format -i $file
    ((count++))
done
echo "clng formatting done, ${count} files got formmated "