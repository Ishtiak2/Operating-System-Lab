# FILE MANAGEMENT - EXAM CHEAT SHEET

## 1. FILE MANAGEMENT BASICS

| Concept | Definition | Example |
|---------|-----------|---------|
| **File** | Named collection of data stored on disk | `myfile.txt`, `program.cpp` |
| **Directory** | Container for files and other directories | `/home/user/`, `/tmp/` |
| **Path** | Location of file in file system | `/home/user/file.txt` |
| **Absolute Path** | Full path from root (/) | `/home/user/documents/file.txt` |
| **Relative Path** | Path from current directory | `./documents/file.txt`, `../file.txt` |
| **inode** | Data structure storing file metadata | Permissions, owner, size, timestamps |

---

## 2. ESSENTIAL FILE OPERATIONS

| Operation | Command | Syntax | Example |
|-----------|---------|--------|---------|
| **Create** | `touch` | `touch filename` | `touch myfile.txt` |
| **Copy** | `cp` | `cp source dest` | `cp file.txt backup.txt` |
| **Move/Rename** | `mv` | `mv source dest` | `mv old.txt new.txt` |
| **Delete** | `rm` | `rm filename` | `rm file.txt` |
| **View** | `cat` | `cat filename` | `cat file.txt` |
| **Edit** | `nano/vim` | `nano filename` | `nano file.txt` |
| **List** | `ls` | `ls [options]` | `ls -l` |

---

## 3. FILE CREATION

### touch - Create Empty File
```bash
touch myfile.txt              # Create empty file
touch file1.txt file2.txt     # Create multiple files
```

### Write Content to File

| Method | Command | Description |
|--------|---------|-------------|
| **Overwrite** | `echo "text" > file` | Replace content |
| **Append** | `echo "text" >> file` | Add to end |
| **Interactive** | `cat > file` | Type content, Ctrl+D to save |
| **Heredoc** | `cat << EOF > file` | Multi-line input |

**Examples:**
```bash
echo "Hello World" > file.txt       # Overwrite
echo "New line" >> file.txt         # Append
cat > file.txt                      # Type content, Ctrl+D to finish
```

---

## 4. FILE VIEWING

| Command | Purpose | Usage | When to Use |
|---------|---------|-------|-------------|
| `cat` | Display entire file | `cat file.txt` | Small files |
| `less` | Page through file | `less file.txt` | Large files |
| `head` | First 10 lines | `head file.txt` | Preview file |
| `head -n 5` | First 5 lines | `head -n 5 file.txt` | Custom preview |
| `tail` | Last 10 lines | `tail file.txt` | Check end |
| `tail -n 5` | Last 5 lines | `tail -n 5 file.txt` | Custom end view |
| `tail -f` | Follow file (live) | `tail -f log.txt` | Monitor logs |

---

## 5. FILE COPY (cp)

### Basic Copy
```bash
cp source.txt dest.txt              # Copy file
cp file.txt /path/to/directory/     # Copy to directory
cp file1.txt file2.txt dir/         # Copy multiple files
```

### Important Options

| Option | Purpose | Example |
|--------|---------|---------|
| `-r` or `-R` | Copy directory recursively | `cp -r dir1/ dir2/` |
| `-i` | Interactive (ask before overwrite) | `cp -i file.txt backup.txt` |
| `-v` | Verbose (show what's copied) | `cp -v file.txt backup.txt` |
| `-p` | Preserve attributes (permissions, timestamps) | `cp -p file.txt backup.txt` |
| `-u` | Update (copy only if newer) | `cp -u file.txt backup.txt` |

### Common Patterns
```bash
cp file.txt backup.txt              # Simple copy
cp -r folder1/ folder2/             # Copy entire directory
cp *.txt backup/                    # Copy all .txt files
cp -i file.txt dest.txt             # Ask before overwriting
```

---

## 6. FILE MOVE/RENAME (mv)

### Move vs Rename
- **Same directory** → Rename
- **Different directory** → Move
- **Both supported** by `mv` command

### Basic Usage
```bash
mv oldname.txt newname.txt          # Rename file
mv file.txt /path/to/directory/     # Move file
mv file1.txt file2.txt dir/         # Move multiple files
mv dir1/ dir2/                      # Rename/move directory
```

### Important Options

| Option | Purpose | Example |
|--------|---------|---------|
| `-i` | Interactive (confirm overwrite) | `mv -i old.txt new.txt` |
| `-v` | Verbose | `mv -v file.txt newfile.txt` |
| `-n` | No overwrite | `mv -n file.txt existing.txt` |
| `-f` | Force overwrite | `mv -f file.txt dest.txt` |

### Key Differences: cp vs mv

| Aspect | `cp` | `mv` |
|--------|------|------|
| **Original file** | Kept | Deleted |
| **Disk space** | Doubles | No change |
| **Speed** | Slow (copies data) | Fast (just updates inode) |
| **Cross-filesystem** | Works | May be slower |

---

## 7. FILE DELETION (rm)

### Basic Deletion
```bash
rm file.txt                         # Delete file
rm file1.txt file2.txt              # Delete multiple files
rm *.txt                            # Delete all .txt files
```

### Important Options

| Option | Purpose | Example | ⚠️ Warning |
|--------|---------|---------|-----------|
| `-r` or `-R` | Recursive (delete directory) | `rm -r folder/` | Deletes everything inside |
| `-f` | Force (no confirmation) | `rm -f file.txt` | No undo! |
| `-i` | Interactive (ask each file) | `rm -i file.txt` | Safe |
| `-v` | Verbose | `rm -v file.txt` | Shows what's deleted |
| `-rf` | Force recursive | `rm -rf folder/` | 🚨 VERY DANGEROUS |

### ⚠️ CRITICAL WARNINGS

| Command | Danger Level | Effect |
|---------|--------------|--------|
| `rm -rf /` | 🔥🔥🔥 FATAL | Deletes ENTIRE system |
| `rm -rf /*` | 🔥🔥🔥 FATAL | Deletes all files |
| `rm -rf ~` | 🔥🔥 CRITICAL | Deletes home directory |
| `rm -rf .` | 🔥 SEVERE | Deletes current directory |
| `rm -rf *` | ⚠️ HIGH | Deletes all in current dir |

### Safe Deletion Practices
```bash
rm -i file.txt                      # Always confirm
ls -l file.txt                      # Check before deleting
rm -iv *.txt                        # Interactive + verbose
```

---

## 8. DIRECTORY OPERATIONS

| Operation | Command | Example |
|-----------|---------|---------|
| **Create directory** | `mkdir` | `mkdir newfolder` |
| **Create nested** | `mkdir -p` | `mkdir -p a/b/c` |
| **Remove empty dir** | `rmdir` | `rmdir folder` |
| **Remove directory** | `rm -r` | `rm -r folder/` |
| **Change directory** | `cd` | `cd /path/to/dir` |
| **Print working dir** | `pwd` | `pwd` |
| **List contents** | `ls` | `ls -la` |

### Directory Navigation

| Command | Description | Example |
|---------|-------------|---------|
| `cd /path` | Go to absolute path | `cd /home/user` |
| `cd folder` | Go to relative path | `cd Documents` |
| `cd ..` | Go up one level | `cd ..` |
| `cd ../..` | Go up two levels | `cd ../..` |
| `cd ~` | Go to home directory | `cd ~` |
| `cd -` | Go to previous directory | `cd -` |

---

## 9. LISTING FILES (ls)

### Common Options

| Option | Purpose | Example |
|--------|---------|---------|
| `-l` | Long format (detailed) | `ls -l` |
| `-a` | Show hidden files (. files) | `ls -a` |
| `-h` | Human-readable sizes | `ls -lh` |
| `-t` | Sort by modification time | `ls -lt` |
| `-r` | Reverse order | `ls -lr` |
| `-R` | Recursive (subdirectories) | `ls -R` |
| `-S` | Sort by size | `ls -lS` |
| `-1` | One file per line | `ls -1` |

### Combining Options
```bash
ls -la          # Long format + hidden files
ls -lht         # Long + human-readable + sorted by time
ls -lhS         # Long + human-readable + sorted by size
ls -latr        # All files, long, sorted by time, reversed
```

### Understanding ls -l Output
```
-rw-r--r--  1 user group  1234 Nov 5 10:30 file.txt
│  │  │  │  │  │    │      │    │         │
│  │  │  │  │  │    │      │    │         └─ filename
│  │  │  │  │  │    │      │    └─ modification time
│  │  │  │  │  │    │      └─ size in bytes
│  │  │  │  │  │    └─ group
│  │  │  │  │  └─ owner
│  │  │  │  └─ number of hard links
│  │  │  └─ others permissions (r--)
│  │  └─ group permissions (r--)
│  └─ owner permissions (rw-)
└─ file type (- = regular file, d = directory)
```

---

## 10. FILE PERMISSIONS

### Permission Types

| Symbol | Meaning | Numeric |
|--------|---------|---------|
| `r` | Read | 4 |
| `w` | Write | 2 |
| `x` | Execute | 1 |
| `-` | No permission | 0 |

### Permission Groups

| Position | Who | Example |
|----------|-----|---------|
| 1st trio | Owner (user) | `rwx` |
| 2nd trio | Group | `r-x` |
| 3rd trio | Others | `r--` |

### Common Permissions

| Symbolic | Numeric | Meaning |
|----------|---------|---------|
| `-rw-r--r--` | 644 | Owner: read+write, Others: read only |
| `-rwxr-xr-x` | 755 | Owner: all, Others: read+execute |
| `-rwx------` | 700 | Owner: all, Others: none |
| `-rw-rw-rw-` | 666 | Everyone: read+write |
| `-rwxrwxrwx` | 777 | Everyone: all (dangerous!) |

### Changing Permissions

| Command | Example | Description |
|---------|---------|-------------|
| `chmod` | `chmod 644 file.txt` | Set permissions numerically |
| `chmod` | `chmod u+x file.sh` | Add execute for owner |
| `chmod` | `chmod go-w file.txt` | Remove write for group+others |
| `chmod` | `chmod a+r file.txt` | Add read for all |

**Symbolic Notation:**
- `u` = user (owner), `g` = group, `o` = others, `a` = all
- `+` = add, `-` = remove, `=` = set exactly
- `r` = read, `w` = write, `x` = execute

```bash
chmod u+x script.sh         # Add execute for owner
chmod go-w file.txt         # Remove write for group and others
chmod a+r file.txt          # Add read for everyone
chmod 755 script.sh         # rwxr-xr-x
```

---

## 11. FILE OWNERSHIP

| Command | Purpose | Example |
|---------|---------|---------|
| `chown` | Change owner | `chown user file.txt` |
| `chown` | Change owner+group | `chown user:group file.txt` |
| `chgrp` | Change group only | `chgrp group file.txt` |

```bash
chown alice file.txt            # Change owner to alice
chown alice:staff file.txt      # Change owner and group
chown -R alice folder/          # Recursive ownership change
```

---

## 12. FILE SEARCH

### find - Search Files

| Usage | Command | Description |
|-------|---------|-------------|
| By name | `find . -name "*.txt"` | Find all .txt files |
| By type | `find . -type f` | Find only files |
| By type | `find . -type d` | Find only directories |
| By size | `find . -size +1M` | Files larger than 1MB |
| By time | `find . -mtime -7` | Modified in last 7 days |
| By permission | `find . -perm 644` | Files with 644 permissions |

**Examples:**
```bash
find . -name "*.cpp"                    # Find all C++ files
find /home -type f -name "*.txt"        # Find .txt files in /home
find . -type f -size +10M               # Files > 10MB
find . -name "*.log" -mtime -1          # .log files modified today
find . -type f -perm 777                # World-writable files
```

### locate - Fast Search (indexed)
```bash
locate filename             # Fast search (uses database)
updatedb                    # Update locate database (sudo)
```

### grep - Search Inside Files
```bash
grep "pattern" file.txt                 # Search in file
grep -r "pattern" directory/            # Search recursively
grep -i "pattern" file.txt              # Case-insensitive
grep -n "pattern" file.txt              # Show line numbers
grep -v "pattern" file.txt              # Invert match
```

---

## 13. FILE COMPRESSION & ARCHIVING

### tar - Archive Files

| Operation | Command | Description |
|-----------|---------|-------------|
| **Create** | `tar -cvf archive.tar files/` | Create tar archive |
| **Extract** | `tar -xvf archive.tar` | Extract tar archive |
| **List** | `tar -tvf archive.tar` | List contents |
| **Create gzip** | `tar -czvf archive.tar.gz files/` | Create + compress |
| **Extract gzip** | `tar -xzvf archive.tar.gz` | Extract compressed |

**Options:**
- `c` = create
- `x` = extract
- `t` = list
- `v` = verbose
- `f` = file
- `z` = gzip compression
- `j` = bzip2 compression

### Compression Tools

| Tool | Extension | Compress | Decompress |
|------|-----------|----------|------------|
| gzip | `.gz` | `gzip file` | `gunzip file.gz` |
| bzip2 | `.bz2` | `bzip2 file` | `bunzip2 file.bz2` |
| zip | `.zip` | `zip archive.zip files` | `unzip archive.zip` |

---

## 14. FILE INFORMATION

| Command | Purpose | Example |
|---------|---------|---------|
| `file` | Determine file type | `file document.pdf` |
| `stat` | Detailed file info | `stat file.txt` |
| `du` | Disk usage | `du -sh folder/` |
| `df` | Filesystem disk space | `df -h` |
| `wc` | Count lines/words/bytes | `wc file.txt` |
| `wc -l` | Count lines only | `wc -l file.txt` |

```bash
file myfile.txt             # Shows file type
stat myfile.txt             # Detailed metadata
du -sh folder/              # Folder size
df -h                       # Disk space usage
wc -l file.txt              # Count lines
```

---

## 15. FILE REDIRECTION & PIPES

### Redirection Operators

| Operator | Purpose | Example |
|----------|---------|---------|
| `>` | Redirect output (overwrite) | `ls > files.txt` |
| `>>` | Redirect output (append) | `ls >> files.txt` |
| `<` | Redirect input | `sort < input.txt` |
| `2>` | Redirect stderr | `cmd 2> errors.log` |
| `&>` | Redirect stdout+stderr | `cmd &> output.log` |
| `\|` | Pipe (output → input) | `ls \| grep ".txt"` |

### Common Patterns
```bash
command > output.txt                # Save output to file
command >> output.txt               # Append output
command 2> errors.log               # Save errors
command &> all.log                  # Save all output
command > /dev/null                 # Discard output
command1 | command2                 # Pipe output
```

### Useful Pipe Combinations
```bash
ls -l | grep ".txt"                 # List only .txt files
cat file.txt | wc -l                # Count lines
ps aux | grep "process"             # Find process
history | grep "git"                # Search command history
cat file.txt | sort | uniq          # Sort and remove duplicates
```

---

## 16. WILDCARDS & PATTERNS

| Wildcard | Matches | Example | Matches |
|----------|---------|---------|---------|
| `*` | Zero or more characters | `*.txt` | All .txt files |
| `?` | Exactly one character | `file?.txt` | file1.txt, fileA.txt |
| `[abc]` | Any one of a, b, c | `file[123].txt` | file1.txt, file2.txt, file3.txt |
| `[a-z]` | Range a to z | `[a-z]*.txt` | All .txt starting with letter |
| `[!abc]` | NOT a, b, or c | `file[!0-9].txt` | file with non-digit |

**Examples:**
```bash
ls *.txt                # All .txt files
ls file?.txt            # file1.txt, fileA.txt
ls [abc]*.txt           # Files starting with a, b, or c
ls *.{txt,md}           # All .txt and .md files
rm temp*                # Delete all files starting with temp
```

---

## 17. HARD LINKS vs SOFT LINKS

### Link Types

| Type | Command | Characteristics |
|------|---------|----------------|
| **Hard Link** | `ln file link` | Same inode, can't cross filesystems |
| **Soft Link** | `ln -s file link` | Different inode, can cross filesystems |

### Comparison

| Feature | Hard Link | Soft Link (Symlink) |
|---------|-----------|---------------------|
| **inode** | Same as original | Different |
| **Across filesystems** | ❌ No | ✅ Yes |
| **Link to directory** | ❌ No | ✅ Yes |
| **Original deleted** | Link still works | ❌ Link breaks |
| **Size** | Same as file | Small (path only) |
| **Symbol in ls -l** | None | `->` arrow |

**Examples:**
```bash
ln original.txt hardlink.txt        # Create hard link
ln -s original.txt softlink.txt     # Create soft link
ln -s /path/to/file link            # Absolute path symlink
```

**Viewing Links:**
```bash
ls -li                              # Show inode numbers
ls -l                               # Symlinks show ->
```

---

## 18. COMMON EXAM PATTERNS

### Pattern 1: Create, Write, View
```bash
touch file.txt
echo "Hello World" > file.txt
cat file.txt
```

### Pattern 2: Copy, Rename, Delete
```bash
cp file.txt backup.txt
mv backup.txt renamed.txt
rm renamed.txt
```

### Pattern 3: Directory Operations
```bash
mkdir newfolder
cd newfolder
touch file.txt
cd ..
rm -r newfolder
```

### Pattern 4: Find and Process
```bash
find . -name "*.txt" -exec rm {} \;     # Find and delete
find . -type f | wc -l                  # Count files
```

### Pattern 5: Permission Management
```bash
chmod 644 file.txt              # Set read/write for owner
chmod u+x script.sh             # Make executable
ls -l                           # Verify permissions
```

---

## 19. COMMON MISTAKES & EXAM TIPS

| Mistake | Consequence | Fix |
|---------|-------------|-----|
| `rm -rf *` without checking | Deletes everything | Use `ls` first, `rm -i` |
| Forgetting `-r` for directories | cp/rm fails | Add `-r` flag |
| Using `>` instead of `>>` | Overwrites file | Use `>>` to append |
| `mv` without checking destination | Overwrites existing file | Use `mv -i` |
| Wrong permissions on script | Can't execute | `chmod +x script.sh` |
| Hard link across filesystems | Fails | Use soft link (`ln -s`) |

### ✅ Exam Tips

1. **Always check before deleting**: `ls` before `rm`
2. **Use `-i` for safety**: `cp -i`, `mv -i`, `rm -i`
3. **Permissions**: 644 for files, 755 for executables/directories
4. **Directory operations need `-r`**: `cp -r`, `rm -r`
5. **`>` overwrites, `>>` appends**
6. **Wildcards**: `*` = many, `?` = one
7. **Links**: Hard = same inode, Soft = pointer
8. **`mv` is rename** when in same directory
9. **Path**: `/` = absolute, `./` = relative
10. **Hidden files**: Start with `.`, use `ls -a`

---

## 20. QUICK COMMAND REFERENCE

### Essential Commands
```bash
# File operations
touch file.txt                  # Create
cp file.txt backup.txt         # Copy
mv file.txt newname.txt        # Rename/Move
rm file.txt                    # Delete
cat file.txt                   # View

# Directory operations
mkdir dir                      # Create directory
cd dir                         # Change directory
pwd                           # Print working directory
ls -la                        # List all files
rm -r dir                     # Remove directory

# Permissions
chmod 644 file.txt            # Set permissions
chmod +x script.sh            # Make executable
chown user file.txt           # Change owner

# Search
find . -name "*.txt"          # Find files
grep "text" file.txt          # Search in file

# Compression
tar -czvf archive.tar.gz dir/ # Create archive
tar -xzvf archive.tar.gz      # Extract archive
```

---

## 21. FILE SYSTEM STRUCTURE (Linux/Unix)

| Directory | Purpose | Examples |
|-----------|---------|----------|
| `/` | Root directory | Top of filesystem |
| `/home` | User home directories | `/home/alice`, `/home/bob` |
| `/root` | Root user home | Admin home |
| `/bin` | Essential binaries | `ls`, `cp`, `mv` |
| `/usr/bin` | User programs | Most commands |
| `/etc` | Configuration files | System config |
| `/tmp` | Temporary files | Cleared on reboot |
| `/var` | Variable data | Logs, databases |
| `/dev` | Device files | Hardware |

---

## 22. FORMULAS & CALCULATIONS

### Permission Calculation
```
Owner: rwx = 4+2+1 = 7
Group: r-x = 4+0+1 = 5
Other: r-- = 4+0+0 = 4
Result: 754
```

### Disk Space
- **KB** = 1024 bytes
- **MB** = 1024 KB = 1,048,576 bytes
- **GB** = 1024 MB = 1,073,741,824 bytes

---

## SUMMARY CHECKLIST FOR EXAM

- [ ] Know basic operations: touch, cp, mv, rm
- [ ] Understand `>` vs `>>` (overwrite vs append)
- [ ] Remember `-r` for directory operations
- [ ] Know permission numbers: 644, 755, 777
- [ ] Understand symbolic permissions: u+x, go-w
- [ ] Know wildcards: `*`, `?`, `[abc]`
- [ ] Understand hard vs soft links
- [ ] Remember dangerous commands: `rm -rf`
- [ ] Know ls -l output format
- [ ] Understand absolute vs relative paths
- [ ] Remember find command patterns
- [ ] Know tar options: c, x, v, f, z
- [ ] Understand pipe `|` and redirection `>`, `>>`
- [ ] Remember file type symbols in ls -l: `-`, `d`, `l`

---

**Good Luck! 📁🚀**
