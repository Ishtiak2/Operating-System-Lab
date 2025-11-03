#!/usr/bin/env bash
dir=/Users/ishtiakrahman/Desktop/Operating-System-Lab/Shell_Scripting

countFiles=$(find $dir -type f | wc -l)
countDir=$(find $dir -type d | wc -l)
countDir=$((countDir - 1)) # exclude the main directory

echo "📂 Directory: $dir"
echo "🗂️ Files:$countFiles"
echo "📦 Subdirectories: $countDir"