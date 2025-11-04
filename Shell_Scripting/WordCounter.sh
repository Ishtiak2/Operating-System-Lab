#!/usr/bin/env bash
# Count words from user input

read -p "Enter a sentence: " sentence

word_count=$(echo "$sentence" | wc -w)
echo "🧾 Your sentence: $sentence"
echo "🔢 Word count: $word_count"
