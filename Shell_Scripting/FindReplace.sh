#!/usr/bin/env bash

#for more see man sed 
man sed
sentence="My name itiak Rahman. I am a student."
echo "$sentence" | sed 's/itiak/Ishtiak/ '

sed -i '' -e 's/Example/for-Example/g' test.txt
