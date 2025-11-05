#!/usr/bin/env bash
# Operations: Create, Copy, Move, Delete

# Create a file
echo "Creating file: myfile.txt ..."
touch myfile.txt
echo "Hello macOS!" > myfile.txt
echo "File created and text added"
echo

# Copy the file
echo "Copying file to backup.txt ..."
cp myfile.txt backup.txt
echo "Copy successful"
echo

#Move (rename) the file
echo "Renaming backup.txt → moved.txt ..."
mv backup.txt moved.txt
echo "File renamed"
echo

# Delete the file
echo "Deleting moved.txt ..."
rm moved.txt
echo "File deleted "
echo

# Show final result
echo "Remaining files in current directory:"
ls -l
echo
echo "🎉 All file operations completed successfully!"
