#!/usr/bin/env bash
# Array demonstration script

# Declare array
number=(1 2 3 5 7 9)

# Print the full array
echo "Full array: ${number[*]}"

# Print number of elements
echo "Array length: ${#number[@]}"

# Access specific elements
echo "First element: ${number[0]}"
echo "Second Element: ${number[1]}"

# Modify an element
number[2]=99
echo "After modification: ${number[*]}"

# Add a new element
number+=(11)
echo "After adding new element: ${number[*]}"

# Loop through array
echo "Looping through array values:"

size=${number[@]}

for (( i=0; i<$size; i++ )); do
    echo "Index $i → ${number[i]}"
done

# Using a simpler 'for each' style loop
echo "Using 'for each' style loop:"
for value in "${number[@]}"; do
    echo "$value"
done

# Remove an element
unset number[1]
echo "After removing index 1: ${number[*]}"