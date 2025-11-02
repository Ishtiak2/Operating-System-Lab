#!/usr/bin/env bash

# Functions for arithmetic
add() {
    echo $(($1 + $2))
}

subtract() {
    echo $(($1 - $2))
}

multiply() {
    echo $(($1 * $2))
}

divide() {
    if [ $2 -eq 0 ]; then
        echo "Error: Division by zero!"
    else
        echo $(($1 / $2))
    fi
}

# User input
read -p "Enter the value of a: " a
read -p "Enter the value of b: " b

# Operation choice
echo "Choose operation:"
echo "1) Addition (+)"
echo "2) Subtraction (-)"
echo "3) Multiplication (*)"
echo "4) Division (/)"
read -p "Enter choice [1-4]: " choice

# Perform operation using if-elif-else
if [ "$choice" -eq 1 ]
then
    result=$(add $a $b) #way-1
    echo "a + b = $result"

elif [ "$choice" -eq 2 ]
then
    result=$(subtract $a $b)
    echo "a - b = $result"

elif [ "$choice" -eq 3 ]
then
    echo "a * b = $((a*b))"

elif [ "$choice" -eq 4 ]
then
    echo "a / b = $((a/b))"
else
    echo "Invalid choice!"
fi
