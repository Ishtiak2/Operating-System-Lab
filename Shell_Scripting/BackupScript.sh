#!/usr/bin/env bash

#see man cp
#see man mkdir
mkdir /Users/ishtiakrahman/Desktop/Operating-System-Lab/Shell_Backup_latest

#Copy a group of files to the /tmp directory:
cp *.sh /Users/ishtiakrahman/Desktop/Operating-System-Lab/Shell_Backup_latest

#Copy the directory junk and all of its contents (including any subdirectories) to the /tmp directory:
cp -R /Users/ishtiakrahman/Desktop/Operating-System-Lab/Shell_Scripting /Users/ishtiakrahman/Desktop/Operating-System-Lab/Shell_Backup_latest
