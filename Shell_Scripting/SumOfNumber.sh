#!/usr/bin/env bash
# Program to find the sum of N numbers

read -p "Enter how many numbers: " n

sum=0

echo "Enter $n numbers:"
for (( i=1; i<=n; i++ ))
do
    read num
    sum=$((sum + num))
done

echo "The sum of $n numbers is: $sum"