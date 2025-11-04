# 📝 Shell Scripting Exam Cheat Sheet

Quick reference table for Bash scripting - Perfect for exams!

---

## Variables & I/O

| Command | Syntax | Example |
|---------|--------|---------|
| **Variable** | `var=value` | `name="John"` |
| **Use Variable** | `$var` or `${var}` | `echo $name` |
| **Read Input** | `read var` | `read -p "Name: " name` |
| **Command Sub** | `$(command)` | `date=$(date)` |
| **Echo** | `echo "text"` | `echo "Hello $name"` |
| **Printf** | `printf "format" args` | `printf "%s\n" $var` |

---

## Conditionals

| Statement | Syntax | Example |
|-----------|--------|---------|
| **if** | `if [ condition ]; then commands; fi` | `if [ $a -eq 5 ]; then echo "5"; fi` |
| **if-else** | `if [ cond ]; then cmd1; else cmd2; fi` | `if [ -f file ]; then cat file; else echo "No file"; fi` |
| **if-elif** | `if [ c1 ]; then cmd1; elif [ c2 ]; then cmd2; else cmd3; fi` | `if [ $n -gt 0 ]; then echo "+"; elif [ $n -lt 0 ]; then echo "-"; else echo "0"; fi` |
| **case** | `case $var in p1) cmd;; p2) cmd;; esac` | `case $1 in start) run;; stop) stop;; esac` |
| **One-liner** | `[ cond ] && cmd1 \|\| cmd2` | `[ -f file ] && echo "Found" \|\| echo "Not found"` |

---

## Loops

| Loop | Syntax | Example |
|------|--------|---------|
| **for (range)** | `for i in {start..end}; do cmd; done` | `for i in {1..5}; do echo $i; done` |
| **for (list)** | `for item in list; do cmd; done` | `for f in *.txt; do cat $f; done` |
| **for (C-style)** | `for ((i=0; i<n; i++)); do cmd; done` | `for ((i=1; i<=10; i++)); do echo $i; done` |
| **while** | `while [ cond ]; do cmd; done` | `while [ $i -le 5 ]; do echo $i; ((i++)); done` |
| **until** | `until [ cond ]; do cmd; done` | `until [ $i -gt 5 ]; do echo $i; ((i++)); done` |
| **break** | `break` | `for i in {1..10}; do if [ $i -eq 5 ]; then break; fi; done` |
| **continue** | `continue` | `for i in {1..5}; do if [ $i -eq 3 ]; then continue; fi; echo $i; done` |

---

## Comparison Operators

| Type | Operator | Meaning | Example |
|------|----------|---------|---------|
| **Numeric** | `-eq` | Equal | `[ $a -eq $b ]` |
| | `-ne` | Not equal | `[ $a -ne $b ]` |
| | `-gt` | Greater than | `[ $a -gt 5 ]` |
| | `-ge` | Greater or equal | `[ $a -ge 5 ]` |
| | `-lt` | Less than | `[ $a -lt 10 ]` |
| | `-le` | Less or equal | `[ $a -le 10 ]` |
| **String** | `=` | Equal | `[ "$str1" = "$str2" ]` |
| | `!=` | Not equal | `[ "$str1" != "$str2" ]` |
| | `-z` | Empty string | `[ -z "$var" ]` |
| | `-n` | Not empty | `[ -n "$var" ]` |
| **File** | `-e` | Exists | `[ -e file ]` |
| | `-f` | Regular file | `[ -f file.txt ]` |
| | `-d` | Directory | `[ -d /path ]` |
| | `-r` | Readable | `[ -r file ]` |
| | `-w` | Writable | `[ -w file ]` |
| | `-x` | Executable | `[ -x script.sh ]` |
| | `-s` | Not empty | `[ -s file ]` |
| **Logical** | `&&` | AND | `[ $a -gt 0 ] && [ $b -lt 10 ]` |
| | `\|\|` | OR | `[ $a -eq 1 ] \|\| [ $b -eq 1 ]` |
| | `!` | NOT | `[ ! -f file ]` |

---

## String Operations

| Operation | Syntax | Example | Output |
|-----------|--------|---------|--------|
| **Length** | `${#var}` | `str="hello"; echo ${#str}` | `5` |
| **Substring** | `${var:pos:len}` | `str="hello"; echo ${str:0:3}` | `hel` |
| **Replace First** | `${var/old/new}` | `str="hi hi"; echo ${str/hi/bye}` | `bye hi` |
| **Replace All** | `${var//old/new}` | `str="hi hi"; echo ${str//hi/bye}` | `bye bye` |
| **Uppercase** | `${var^^}` | `str="hello"; echo ${str^^}` | `HELLO` |
| **Lowercase** | `${var,,}` | `str="HELLO"; echo ${str,,}` | `hello` |
| **Default Value** | `${var:-default}` | `echo ${name:-"Guest"}` | `Guest` (if name unset) |

---

## Arrays

| Operation | Syntax | Example |
|-----------|--------|---------|
| **Declare** | `arr=(item1 item2 item3)` | `fruits=(apple banana)` |
| **Access Element** | `${arr[index]}` | `echo ${fruits[0]}` |
| **All Elements** | `${arr[@]}` | `echo ${fruits[@]}` |
| **Length** | `${#arr[@]}` | `echo ${#fruits[@]}` |
| **Add Element** | `arr+=(item)` | `fruits+=(cherry)` |
| **Loop Array** | `for i in "${arr[@]}"; do cmd; done` | `for f in "${fruits[@]}"; do echo $f; done` |

---

## Functions

| Operation | Syntax | Example |
|-----------|--------|---------|
| **Define** | `func() { commands; }` | `greet() { echo "Hello $1"; }` |
| **Call** | `func args` | `greet "World"` |
| **Return** | `return value` | `return 0` |
| **Parameters** | `$1, $2, ..., $@, $#` | `add() { echo $(($1 + $2)); }` |

---

## File System Commands

| Command | Syntax | Example | Description |
|---------|--------|---------|-------------|
| **cd** | `cd path` | `cd /home` | Change directory |
| **ls** | `ls [opts]` | `ls -lah` | List files (-l long, -a all, -h human) |
| **pwd** | `pwd` | `pwd` | Print working directory |
| **mkdir** | `mkdir name` | `mkdir -p a/b/c` | Make directory (-p parents) |
| **touch** | `touch file` | `touch file.txt` | Create empty file |
| **cp** | `cp src dest` | `cp -r dir1 dir2` | Copy (-r recursive) |
| **mv** | `mv src dest` | `mv old.txt new.txt` | Move/rename |
| **rm** | `rm file` | `rm -rf dir/` | Remove (-r recursive, -f force) |
| **cat** | `cat file` | `cat file.txt` | Display file |
| **head** | `head -n N file` | `head -5 file.txt` | First N lines |
| **tail** | `tail -n N file` | `tail -10 file.txt` | Last N lines |
| **wc** | `wc file` | `wc -l file.txt` | Count (-l lines, -w words) |
| **chmod** | `chmod mode file` | `chmod +x script.sh` | Change permissions |
| **find** | `find path -name pattern` | `find . -name "*.txt"` | Find files |

---

## Text Processing

| Command | Syntax | Example | Description |
|---------|--------|---------|-------------|
| **grep** | `grep pattern file` | `grep "error" log.txt` | Search text |
| | | `grep -i "error" file` | Case insensitive |
| | | `grep -v "^#" file` | Invert match (exclude) |
| | | `grep -n "TODO" file` | Show line numbers |
| **sed** | `sed 's/old/new/g' file` | `sed 's/foo/bar/g' file` | Replace all |
| | | `sed '/pattern/d' file` | Delete lines |
| | | `sed -i 's/old/new/g' file` | Edit in-place |
| **awk** | `awk '{print $N}' file` | `awk '{print $1}' file` | Print column N |
| | | `awk -F: '{print $1}' file` | Custom delimiter |
| | | `awk '$3>100 {print}' file` | Conditional print |
| **cut** | `cut -d'delim' -fN file` | `cut -d: -f1 /etc/passwd` | Extract field |
| | | `cut -c1-5 file` | Extract characters |
| **sort** | `sort file` | `sort -n numbers.txt` | Sort (-n numeric, -r reverse) |
| **uniq** | `uniq file` | `sort file \| uniq` | Remove duplicates |
| **tr** | `tr 'set1' 'set2'` | `tr 'a-z' 'A-Z'` | Translate characters |

---

## Redirection & Pipes

| Symbol | Meaning | Example |
|--------|---------|---------|
| `>` | Redirect output (overwrite) | `echo "text" > file.txt` |
| `>>` | Append output | `echo "more" >> file.txt` |
| `<` | Input from file | `wc -l < file.txt` |
| `2>` | Redirect errors | `cmd 2> error.log` |
| `&>` | Redirect all (stdout+stderr) | `cmd &> all.log` |
| `\|` | Pipe (output → input) | `cat file \| grep "pattern"` |
| `2>&1` | Redirect stderr to stdout | `cmd > file 2>&1` |

---

## Special Variables

| Variable | Meaning | Example |
|----------|---------|---------|
| `$0` | Script name | `echo "Running: $0"` |
| `$1, $2, ...` | Arguments | `echo "First: $1"` |
| `$@` | All arguments (separate) | `for arg in "$@"; do echo $arg; done` |
| `$*` | All arguments (single string) | `echo "$*"` |
| `$#` | Number of arguments | `if [ $# -lt 2 ]; then echo "Need 2 args"; fi` |
| `$?` | Exit status of last command | `cmd; if [ $? -eq 0 ]; then echo "OK"; fi` |
| `$$` | Current process ID | `echo "PID: $$"` |
| `$!` | Last background process ID | `cmd & echo "BG: $!"` |

---

## Arithmetic

| Operation | Syntax | Example |
|-----------|--------|---------|
| **Add** | `$((a + b))` | `sum=$((5 + 3))` → `8` |
| **Subtract** | `$((a - b))` | `diff=$((10 - 3))` → `7` |
| **Multiply** | `$((a * b))` | `prod=$((4 * 5))` → `20` |
| **Divide** | `$((a / b))` | `quot=$((10 / 2))` → `5` |
| **Modulo** | `$((a % b))` | `rem=$((10 % 3))` → `1` |
| **Increment** | `((var++))` | `i=5; ((i++)); echo $i` → `6` |
| **Decrement** | `((var--))` | `i=5; ((i--)); echo $i` → `4` |
| **Power** | `$((a ** b))` | `pow=$((2 ** 3))` → `8` |

---

## Common Patterns

| Task | Command |
|------|---------|
| **Check if file exists** | `if [ -f "file.txt" ]; then echo "Exists"; fi` |
| **Check if directory exists** | `if [ -d "mydir" ]; then echo "Dir exists"; fi` |
| **Loop through files** | `for file in *.txt; do echo $file; done` |
| **Read file line by line** | `while IFS= read -r line; do echo "$line"; done < file.txt` |
| **Count files in directory** | `ls -1 \| wc -l` |
| **Get filename without extension** | `filename="${file%.txt}"` |
| **Get file extension** | `ext="${file##*.}"` |
| **Create backup** | `cp file.txt file.txt.bak` |
| **Check command exists** | `if command -v git &> /dev/null; then echo "Git installed"; fi` |
| **Run command if previous succeeds** | `cmd1 && cmd2` |
| **Run command if previous fails** | `cmd1 \|\| cmd2` |
| **Suppress all output** | `cmd &> /dev/null` |
| **Get current date** | `date=$(date +%Y-%m-%d)` |
| **Sleep** | `sleep 5` (5 seconds) |
| **Exit script** | `exit 0` (0=success, 1+=error) |

---

## Shebang & Execution

```bash
#!/bin/bash              # First line of script
chmod +x script.sh       # Make executable
./script.sh             # Run script
bash script.sh          # Run with bash
bash -x script.sh       # Debug mode
```

---

## Quick Tips ⚡

1. **Always quote variables**: `"$var"` to handle spaces
2. **Use `[[ ]]` for conditions**: More powerful than `[ ]`
3. **Check exit status**: `$?` (0 = success, non-zero = error)
4. **Debug**: `bash -x script.sh` shows execution trace
5. **Test before destructive ops**: Use `echo` first (e.g., `echo rm $file`)

---

**Good Luck on Your Exam! 🎓**

*Last Updated: November 4, 2025*
