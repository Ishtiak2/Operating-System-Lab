# 📖 Shell Scripting Command Reference

A quick reference guide for common Bash scripting commands with syntax, examples, and usage.

---

## 📋 Table of Contents

- [Variables](#-variables)
- [Conditional Statements](#-conditional-statements)
- [Loops](#-loops)
- [File Operations](#-file-operations)
- [String Operations](#-string-operations)
- [Array Operations](#-array-operations)
- [Functions](#-functions)
- [Text Processing](#-text-processing)
- [File System Commands](#-file-system-commands)
- [Comparison Operators](#-comparison-operators)

---

## 📦 Variables

### Declaration & Assignment
```bash
# Format: variable_name=value (no spaces!)
name="John"
age=25
path="/home/user"

# Read user input
read -p "Enter name: " username

# Command substitution
current_date=$(date)
file_count=`ls | wc -l`
```

**Example:**
```bash
greeting="Hello World"
echo $greeting
```

**Usage:** Store and retrieve data throughout the script

---

## 🔀 Conditional Statements

### if Statement

**Format:**
```bash
if [ condition ]; then
    # commands
fi
```

**Single Line:**
```bash
if [ $age -gt 18 ]; then echo "Adult"; fi
```

**if-else:**
```bash
if [ condition ]; then
    # commands
else
    # commands
fi
```

**if-elif-else:**
```bash
if [ $num -gt 0 ]; then
    echo "Positive"
elif [ $num -lt 0 ]; then
    echo "Negative"
else
    echo "Zero"
fi
```

**Example:**
```bash
if [ -f "file.txt" ]; then echo "File exists"; fi
```

**Usage:** Make decisions based on conditions

---

### case Statement

**Format:**
```bash
case $variable in
    pattern1)
        commands
        ;;
    pattern2)
        commands
        ;;
    *)
        default commands
        ;;
esac
```

**Example:**
```bash
case $1 in
    start) echo "Starting..." ;;
    stop) echo "Stopping..." ;;
    *) echo "Invalid option" ;;
esac
```

**Usage:** Multiple condition checking (alternative to if-elif-else)

---

## 🔁 Loops

### for Loop

**Format 1: Range**
```bash
for variable in {start..end}; do
    commands
done
```

**Format 2: List**
```bash
for item in item1 item2 item3; do
    commands
done
```

**Format 3: C-style**
```bash
for ((i=0; i<10; i++)); do
    commands
done
```

**Single Line:**
```bash
for i in {1..5}; do echo $i; done
```

**Examples:**
```bash
# Loop through range
for i in {1..10}; do echo "Number: $i"; done

# Loop through files
for file in *.txt; do echo $file; done

# C-style loop
for ((i=1; i<=5; i++)); do echo $i; done
```

**Usage:** Iterate over sequences, lists, or files

---

### while Loop

**Format:**
```bash
while [ condition ]; do
    commands
done
```

**Single Line:**
```bash
i=1; while [ $i -le 5 ]; do echo $i; ((i++)); done
```

**Example:**
```bash
counter=1
while [ $counter -le 5 ]; do
    echo "Count: $counter"
    ((counter++))
done
```

**Usage:** Repeat commands while condition is true

---

### until Loop

**Format:**
```bash
until [ condition ]; do
    commands
done
```

**Example:**
```bash
num=1
until [ $num -gt 5 ]; do
    echo $num
    ((num++))
done
```

**Usage:** Repeat commands until condition becomes true

---

## 📁 File Operations

### File Test Operators

```bash
# Format: [ operator filename ]

# Common operators:
-e file   # File exists
-f file   # Regular file exists
-d file   # Directory exists
-r file   # File is readable
-w file   # File is writable
-x file   # File is executable
-s file   # File is not empty
```

**Single Line:**
```bash
[ -f "test.txt" ] && echo "File exists" || echo "File not found"
```

**Example:**
```bash
if [ -f "data.txt" ]; then
    echo "File exists"
fi

if [ -d "mydir" ]; then
    echo "Directory exists"
fi
```

**Usage:** Check file/directory properties before operations

---

## 🔤 String Operations

### String Comparison

```bash
# Format: [ string1 operator string2 ]

=       # Equal
!=      # Not equal
-z      # String is empty
-n      # String is not empty
```

**Single Line:**
```bash
[ "$name" = "John" ] && echo "Hello John"
```

**Example:**
```bash
str1="hello"
str2="world"

if [ "$str1" = "$str2" ]; then
    echo "Strings are equal"
else
    echo "Strings are different"
fi

# Check if empty
if [ -z "$var" ]; then
    echo "Variable is empty"
fi
```

**Usage:** Compare and validate string values

---

### String Manipulation

```bash
# Length
${#string}

# Substring
${string:position:length}

# Replace first occurrence
${string/pattern/replacement}

# Replace all occurrences
${string//pattern/replacement}

# Uppercase/Lowercase
${string^^}  # uppercase
${string,,}  # lowercase
```

**Examples:**
```bash
text="Hello World"
echo ${#text}           # 11
echo ${text:0:5}        # Hello
echo ${text/World/Bash} # Hello Bash
echo ${text^^}          # HELLO WORLD
```

**Usage:** Manipulate string content

---

## 📊 Array Operations

### Array Declaration

**Format:**
```bash
# Method 1
array=(item1 item2 item3)

# Method 2
array[0]=item1
array[1]=item2
```

**Single Line:**
```bash
arr=(apple banana cherry); echo ${arr[1]}
```

**Examples:**
```bash
# Declaration
fruits=("apple" "banana" "cherry")

# Access element
echo ${fruits[0]}        # apple

# All elements
echo ${fruits[@]}        # apple banana cherry

# Array length
echo ${#fruits[@]}       # 3

# Loop through array
for fruit in "${fruits[@]}"; do
    echo $fruit
done
```

**Usage:** Store and manipulate lists of data

---

## ⚙️ Functions

**Format:**
```bash
function_name() {
    commands
    return value  # optional
}
```

**Single Line:**
```bash
greet() { echo "Hello $1"; }; greet "World"
```

**Example:**
```bash
# Function definition
add() {
    result=$(($1 + $2))
    echo $result
}

# Function call
sum=$(add 5 3)
echo "Sum: $sum"

# Function with return
is_even() {
    if [ $(($1 % 2)) -eq 0 ]; then
        return 0  # true
    else
        return 1  # false
    fi
}

is_even 4 && echo "Even" || echo "Odd"
```

**Usage:** Organize reusable code blocks

---

## 🔍 Text Processing

### grep - Search Text

**Format:**
```bash
grep [options] pattern filename
```

**Single Line:**
```bash
grep "error" logfile.txt
```

**Options:**
```bash
-i    # Case insensitive
-v    # Invert match (exclude)
-n    # Show line numbers
-c    # Count matches
-r    # Recursive search
```

**Examples:**
```bash
grep "hello" file.txt           # Search for "hello"
grep -i "error" log.txt         # Case insensitive
grep -n "TODO" *.sh             # Show line numbers
grep -v "^#" config.txt         # Exclude comments
```

**Usage:** Search for patterns in text files

---

### sed - Stream Editor

**Format:**
```bash
sed 's/pattern/replacement/flags' filename
```

**Single Line:**
```bash
sed 's/old/new/g' file.txt
```

**Common Operations:**
```bash
# Substitute (replace)
sed 's/old/new/' file.txt          # First occurrence per line
sed 's/old/new/g' file.txt         # All occurrences
sed 's/old/new/gi' file.txt        # Case insensitive

# Delete lines
sed '/pattern/d' file.txt          # Delete matching lines
sed '5d' file.txt                  # Delete line 5
sed '1,3d' file.txt                # Delete lines 1-3

# In-place editing
sed -i 's/old/new/g' file.txt      # Modify file directly
```

**Examples:**
```bash
# Replace text
sed 's/error/warning/g' log.txt

# Delete empty lines
sed '/^$/d' file.txt

# Replace and save
sed -i.bak 's/foo/bar/g' data.txt
```

**Usage:** Text transformation and manipulation

---

### awk - Text Processing

**Format:**
```bash
awk 'pattern {action}' filename
```

**Single Line:**
```bash
awk '{print $1}' file.txt
```

**Examples:**
```bash
# Print specific columns
awk '{print $1, $3}' data.txt      # Print 1st and 3rd columns

# With condition
awk '$3 > 100 {print $1}' data.txt # Print if 3rd column > 100

# Sum a column
awk '{sum+=$1} END {print sum}' numbers.txt

# Field separator
awk -F: '{print $1}' /etc/passwd   # Use : as separator
```

**Usage:** Process and analyze structured text data

---

### cut - Extract Columns

**Format:**
```bash
cut -d'delimiter' -f field_number filename
```

**Single Line:**
```bash
cut -d: -f1 /etc/passwd
```

**Examples:**
```bash
# Extract first field (: delimiter)
cut -d: -f1 /etc/passwd

# Extract characters
cut -c1-5 file.txt                 # First 5 characters

# Multiple fields
cut -d, -f1,3 data.csv             # 1st and 3rd fields
```

**Usage:** Extract specific fields from text

---

## 🗂️ File System Commands

### cd - Change Directory

**Format:**
```bash
cd [directory]
```

**Examples:**
```bash
cd /home/user           # Absolute path
cd Documents            # Relative path
cd ..                   # Parent directory
cd ~                    # Home directory
cd -                    # Previous directory
```

**Usage:** Navigate file system

---

### ls - List Files

**Format:**
```bash
ls [options] [directory]
```

**Single Line:**
```bash
ls -lah
```

**Options:**
```bash
-l    # Long format
-a    # Show hidden files
-h    # Human readable sizes
-R    # Recursive
-t    # Sort by modification time
```

**Examples:**
```bash
ls -la                  # Detailed list with hidden files
ls -lh *.txt            # List txt files with sizes
ls -R                   # Recursive listing
```

**Usage:** View directory contents

---

### mkdir - Make Directory

**Format:**
```bash
mkdir [options] directory_name
```

**Single Line:**
```bash
mkdir -p parent/child/grandchild
```

**Examples:**
```bash
mkdir mydir             # Create directory
mkdir -p path/to/dir    # Create parent directories
mkdir dir1 dir2 dir3    # Multiple directories
```

**Usage:** Create new directories

---

### cp - Copy Files

**Format:**
```bash
cp [options] source destination
```

**Single Line:**
```bash
cp -r source_dir dest_dir
```

**Examples:**
```bash
cp file.txt backup.txt          # Copy file
cp -r dir1 dir2                 # Copy directory recursively
cp *.txt /backup/               # Copy all txt files
```

**Usage:** Duplicate files and directories

---

### mv - Move/Rename

**Format:**
```bash
mv source destination
```

**Single Line:**
```bash
mv oldname.txt newname.txt
```

**Examples:**
```bash
mv file.txt /home/user/         # Move file
mv old.txt new.txt              # Rename file
mv *.log logs/                  # Move all log files
```

**Usage:** Move or rename files

---

### rm - Remove Files

**Format:**
```bash
rm [options] filename
```

**Single Line:**
```bash
rm -rf directory
```

**Examples:**
```bash
rm file.txt             # Remove file
rm -r mydir             # Remove directory
rm -f file.txt          # Force remove
rm -rf dir/             # Force remove directory
```

**Usage:** Delete files and directories (⚠️ Be careful!)

---

### find - Search Files

**Format:**
```bash
find [path] [options] [expression]
```

**Single Line:**
```bash
find . -name "*.txt"
```

**Examples:**
```bash
find . -name "*.sh"              # Find shell scripts
find /home -type f -name "*.log" # Find log files
find . -type d -name "backup"    # Find directories
find . -size +100M               # Files larger than 100MB
find . -mtime -7                 # Modified in last 7 days
```

**Usage:** Locate files by name, type, size, etc.

---

### cat - Concatenate/Display Files

**Format:**
```bash
cat [options] filename
```

**Single Line:**
```bash
cat file1.txt file2.txt > combined.txt
```

**Examples:**
```bash
cat file.txt                     # Display file
cat file1.txt file2.txt          # Display multiple files
cat > newfile.txt                # Create file (Ctrl+D to save)
cat file1.txt file2.txt > out.txt # Concatenate to new file
```

**Usage:** View and combine file contents

---

### echo - Print Text

**Format:**
```bash
echo [options] "text"
```

**Single Line:**
```bash
echo "Hello World" > file.txt
```

**Examples:**
```bash
echo "Hello World"               # Print text
echo -e "Line1\nLine2"          # Enable escape sequences
echo -n "No newline"            # No trailing newline
echo $PATH                      # Print variable
echo "Text" > file.txt          # Write to file
echo "More" >> file.txt         # Append to file
```

**Usage:** Display text and variables

---

### wc - Word Count

**Format:**
```bash
wc [options] filename
```

**Single Line:**
```bash
wc -l file.txt
```

**Options:**
```bash
-l    # Line count
-w    # Word count
-c    # Byte count
-m    # Character count
```

**Examples:**
```bash
wc file.txt                      # Lines, words, bytes
wc -l file.txt                   # Count lines
ls | wc -l                       # Count files in directory
```

**Usage:** Count lines, words, or characters

---

## 🔢 Comparison Operators

### Numeric Comparison

```bash
-eq    # Equal to
-ne    # Not equal to
-gt    # Greater than
-ge    # Greater than or equal to
-lt    # Less than
-le    # Less than or equal to
```

**Examples:**
```bash
if [ $a -eq $b ]; then echo "Equal"; fi
if [ $num -gt 10 ]; then echo "Greater than 10"; fi
```

---

### String Comparison

```bash
=      # Equal to
!=     # Not equal to
<      # Less than (alphabetically)
>      # Greater than (alphabetically)
-z     # String is empty
-n     # String is not empty
```

**Examples:**
```bash
if [ "$str1" = "$str2" ]; then echo "Equal"; fi
if [ -z "$var" ]; then echo "Empty"; fi
```

---

### Logical Operators

```bash
&&     # AND
||     # OR
!      # NOT
```

**Examples:**
```bash
if [ $a -gt 5 ] && [ $b -lt 10 ]; then echo "Both true"; fi
if [ $x -eq 1 ] || [ $y -eq 1 ]; then echo "At least one is 1"; fi
if [ ! -f file.txt ]; then echo "File doesn't exist"; fi
```

---

## 💡 Special Variables

```bash
$0     # Script name
$1-$9  # Script arguments
$#     # Number of arguments
$@     # All arguments as separate strings
$*     # All arguments as single string
$?     # Exit status of last command
$$     # Process ID of current shell
$!     # Process ID of last background command
```

**Example:**
```bash
#!/bin/bash
echo "Script name: $0"
echo "First argument: $1"
echo "All arguments: $@"
echo "Number of arguments: $#"
```

---

## 🎯 Quick Tips

1. **Always quote variables:** `"$variable"` to handle spaces
2. **Check exit status:** `$?` returns 0 for success, non-zero for error
3. **Use double brackets for conditions:** `[[ ]]` is more powerful than `[ ]`
4. **Debug scripts:** `bash -x script.sh` shows each command executed
5. **Make executable:** `chmod +x script.sh` before running

---

## 📚 Additional Resources

- `man command` - View manual for any command
- `command --help` - Quick help for most commands
- [ShellCheck](https://www.shellcheck.net/) - Online shell script analyzer

---

**Last Updated:** November 4, 2025
