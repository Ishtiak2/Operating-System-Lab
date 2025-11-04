#!/usr/bin/env bash
# Count words from user input

read -p "Enter a sentence: " sentence

word_count=$(echo "$sentence" | wc -w) #| → pipe, sends that output as input to the next command.
echo "Your sentence: $sentence"
echo "Word count: $word_count"
