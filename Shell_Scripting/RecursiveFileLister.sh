#!/usr/bin/env bash
# 📂 Recursive File Lister

man find
read -p "Enter directory path: " dir


# Recursively list all files
find "$dir" -type f
