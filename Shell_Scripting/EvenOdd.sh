#!/usr/bin/env bash
echo Enter the number
read a
if [ $((a % 2)) -eq 0 ]
then
    echo The number is even.
else
    echo The number is odd.
fi