#!/usr/bin/env bash
#help test
read -p "Enter the file name " file
if [ -e $file ]
then
    echo "File exists"
else
    echo "File doesn't exists"
fi

#On Linux A directory (folder)  is also considered a file
read -p "Enter the folder name " folder

if [ -d $folder ]
then
    echo "Folder exists"
else
    echo "Folder doesn't exists"
fi