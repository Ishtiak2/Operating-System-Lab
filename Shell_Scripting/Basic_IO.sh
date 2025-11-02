#!/usr/bin/env bash
echo "What is your name?"
read name
echo My name is: $name
echo The value of a = 
read a
echo The value of b = 
read b
echo the addition of a and b is: $(( $a + $b))

read -p "Please give the string input: " str
echo "The string is: $str"
