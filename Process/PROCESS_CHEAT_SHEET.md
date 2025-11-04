# PROCESS MANAGEMENT - EXAM CHEAT SHEET

## 1. PROCESS BASICS

| Concept | Definition | Key Points |
|---------|-----------|------------|
| **Process** | Program in execution | Has PID, state, memory, resources |
| **PID** | Process ID | Unique identifier for each process |
| **PPID** | Parent Process ID | PID of the process that created it |
| **init/systemd** | PID = 1 | Adopts orphan processes |
| **PCB** | Process Control Block | Stores process state, registers, PID, etc. |

---

## 2. PROCESS STATES

| State | Symbol | Description |
|-------|--------|-------------|
| **Running** | R | Executing on CPU |
| **Ready** | R | Ready to execute, waiting for CPU |
| **Waiting/Sleeping** | S | Waiting for I/O or event |
| **Stopped** | T | Stopped (Ctrl+Z) |
| **Zombie** | Z or `<defunct>` | Terminated but not reaped by parent |

**Check Process State:**
```bash
ps -l          # shows state in S column
ps aux         # all processes
```

---

## 3. FORK() - PROCESS CREATION

### Basic Syntax
```c
#include <unistd.h>
#include <sys/types.h>

pid_t pid = fork();
```

### Fork Return Values

| Return Value | Meaning | Who Gets It |
|--------------|---------|-------------|
| **> 0** | Child's PID | Parent process |
| **== 0** | Success | Child process |
| **< 0** | Fork failed | Parent (no child created) |

### Standard Fork Pattern
```c
pid_t pid = fork();

if (pid > 0) {
    // PARENT CODE
    printf("Parent PID: %d, Child PID: %d\n", getpid(), pid);
}
else if (pid == 0) {
    // CHILD CODE
    printf("Child PID: %d, Parent PID: %d\n", getpid(), getppid());
}
else {
    // ERROR
    perror("Fork failed!");
}
```

### Fork Behavior
- **Creates exact copy** of parent process
- **Both processes** execute code after fork()
- **Separate memory spaces** (changes in one don't affect other)
- **Child inherits**: open files, environment, code, data

---

## 4. KEY SYSTEM CALLS

| Function | Header | Purpose | Return Value |
|----------|--------|---------|--------------|
| `fork()` | `<unistd.h>` | Create new process | PID to parent, 0 to child, -1 on error |
| `getpid()` | `<unistd.h>` | Get own PID | Current process PID |
| `getppid()` | `<unistd.h>` | Get parent's PID | Parent process PID |
| `wait(NULL)` | `<sys/wait.h>` | Wait for any child | Child PID, -1 if no children |
| `wait(&status)` | `<sys/wait.h>` | Wait and get exit status | Child PID |
| `waitpid(pid, &status, 0)` | `<sys/wait.h>` | Wait for specific child | Child PID |
| `exit(n)` | `<stdlib.h>` | Terminate process | Doesn't return |
| `sleep(n)` | `<unistd.h>` | Pause n seconds | 0 on success |

---

## 5. WAIT() - PROCESS SYNCHRONIZATION

### Purpose
- **Parent waits** for child to terminate
- **Prevents zombies** by cleaning up child process
- **Gets exit status** of child

### Wait Variants

| Function | Usage | When to Use |
|----------|-------|-------------|
| `wait(NULL)` | Don't care about status | Just wait, no status needed |
| `wait(&status)` | Get exit status | Need to know how child exited |
| `waitpid(pid, &status, 0)` | Wait for specific child | Multiple children |

### Getting Exit Status
```c
int status;
wait(&status);

if (WIFEXITED(status)) {
    int exit_code = WEXITSTATUS(status);
    printf("Child exited with code: %d\n", exit_code);
}
```

| Macro | Purpose |
|-------|---------|
| `WIFEXITED(status)` | Check if child exited normally |
| `WEXITSTATUS(status)` | Get exit code (0-255) |
| `WIFSIGNALED(status)` | Check if child killed by signal |

---

## 6. ZOMBIE PROCESS

### Definition
**Child terminated, but parent hasn't called wait()** → Zombie

### Characteristics
| Property | Value |
|----------|-------|
| **State** | Z or `<defunct>` |
| **CPU Usage** | 0% (not running) |
| **Memory** | Only process table entry |
| **Lifetime** | Until parent calls wait() or parent dies |

### Code Pattern
```c
pid_t pid = fork();

if (pid == 0) {
    printf("Child exiting\n");
    exit(0);        // Child terminates
}
else {
    printf("Parent sleeping\n");
    sleep(10);      // Parent doesn't wait immediately → ZOMBIE
    wait(NULL);     // Now zombie is cleaned up
}
```

### How to Observe
1. Run program with parent sleeping
2. In another terminal: `ps -l` or `ps aux`
3. Look for process with state **Z** or `<defunct>`

### Prevention
- Parent **must call wait()** after child terminates
- Use `SIGCHLD` handler with `wait()` for asynchronous cleanup

---

## 7. ORPHAN PROCESS

### Definition
**Parent terminates before child** → Orphan

### What Happens
| Event | Result |
|-------|--------|
| Parent exits | Child becomes orphan |
| init/systemd adopts child | PPID becomes 1 |
| Child continues execution | No problem, just new parent |

### Code Pattern
```c
pid_t pid = fork();

if (pid == 0) {
    sleep(5);       // Child sleeps
    printf("My parent PID: %d\n", getppid()); // Will be 1
}
else {
    printf("Parent exiting\n");
    return 0;       // Parent exits → child orphaned
}
```

### Key Difference: Zombie vs Orphan

| Type | Who Died First | State | Problem? |
|------|----------------|-------|----------|
| **Zombie** | Child died | Z (defunct) | YES - wastes process table |
| **Orphan** | Parent died | Running normally | NO - adopted by init |

---

## 8. MULTIPLE CHILD PROCESSES

### Sequential Creation Pattern
```c
const int num_children = 3;

for (int i = 0; i < num_children; i++) {
    pid_t pid = fork();
    
    if (pid == 0) {
        printf("Child %d: PID=%d\n", i+1, getpid());
        return 0;    // Child MUST exit to avoid fork bomb
    }
}

// Parent waits for all children
for (int i = 0; i < num_children; i++) {
    wait(NULL);
}
```

### ⚠️ CRITICAL: Child Must Exit
- Without `return 0;` in child → **fork bomb**
- Each child would also create 3 children → exponential growth
- **Always make child exit** after its work

---

## 9. FORK TREE CALCULATIONS

### How Many Processes Created?

| Code | Formula | Total Processes |
|------|---------|-----------------|
| `fork();` | $2^1$ | 2 (1 parent + 1 child) |
| `fork(); fork();` | $2^2$ | 4 |
| `fork(); fork(); fork();` | $2^3$ | 8 |
| **n sequential forks** | $2^n$ | $2^n$ processes |

### Example: 3 Sequential Forks
```c
fork();  // 2 processes (P, C1)
fork();  // 4 processes (P, C1, C2, C3)
fork();  // 8 processes (P, C1, ..., C7)
```

**Calculation:**
- After 1st fork: 2 processes
- After 2nd fork: 2 × 2 = 4 processes
- After 3rd fork: 4 × 2 = 8 processes

### Total = $2^n$ where n = number of forks

---

## 10. EXEC() FAMILY (Brief)

### Purpose
**Replace current process with new program**

| Function | Usage |
|----------|-------|
| `execl()` | `execl("/bin/ls", "ls", "-l", NULL);` |
| `execlp()` | `execlp("ls", "ls", "-l", NULL);` (searches PATH) |
| `execv()` | Takes array: `execv("/bin/ls", args);` |
| `execvp()` | Array + PATH search |

### Key Point
- **Does NOT create new process** (unlike fork)
- **Replaces current process** code and data
- **Never returns** on success (new program runs)
- **Returns -1** on failure

### Fork + Exec Pattern
```c
pid_t pid = fork();

if (pid == 0) {
    execl("/bin/ls", "ls", "-l", NULL);  // Replace child with ls
    perror("exec failed");               // Only if exec fails
}
else {
    wait(NULL);  // Parent waits
}
```

---

## 11. COMMON EXAM PATTERNS

### Pattern 1: Parent-Child with Different Code
```c
pid_t pid = fork();

if (pid > 0) {
    printf("Parent: PID=%d\n", getpid());
    wait(NULL);
}
else if (pid == 0) {
    printf("Child: PID=%d, PPID=%d\n", getpid(), getppid());
}
```

### Pattern 2: Creating N Children
```c
for (int i = 0; i < N; i++) {
    if (fork() == 0) {
        // Child code
        exit(0);  // MUST EXIT
    }
}
// Parent waits
for (int i = 0; i < N; i++) wait(NULL);
```

### Pattern 3: Getting Child's Exit Code
```c
pid_t pid = fork();

if (pid == 0) {
    // Child work
    exit(42);  // Return 42
}
else {
    int status;
    wait(&status);
    printf("Child returned: %d\n", WEXITSTATUS(status));
}
```

---

## 12. COMMON MISTAKES & EXAM TIPS

| Mistake | Consequence | Fix |
|---------|-------------|-----|
| Child doesn't exit in loop | Fork bomb | Add `exit(0)` in child |
| Parent doesn't wait | Zombie processes | Add `wait(NULL)` |
| Using `pid` variable after fork | Confusion | Remember: parent gets child PID, child gets 0 |
| Forgetting error check | Crash on fork failure | Always check `if (pid < 0)` |
| Not including headers | Compilation error | `<unistd.h>`, `<sys/wait.h>` |

### ✅ Exam Tips
1. **Fork returns twice** - different values to parent and child
2. **Count processes**: $2^n$ for n sequential forks
3. **Zombie** = child dead, parent alive, no wait()
4. **Orphan** = parent dead, child alive → adopted by init (PID=1)
5. **Always check** fork return value: >0, ==0, <0
6. **Child must exit** when created in loop
7. **wait()** both prevents zombies AND synchronizes parent-child
8. **WEXITSTATUS()** extracts exit code from status

---

## 13. QUICK REFERENCE CODE SNIPPETS

### Basic Fork
```c
pid_t pid = fork();
if (pid > 0) { /* parent */ }
else if (pid == 0) { /* child */ }
else { /* error */ }
```

### Fork + Wait
```c
pid_t pid = fork();
if (pid == 0) {
    // child work
    exit(0);
}
wait(NULL);  // parent waits
```

### Multiple Children
```c
for (int i = 0; i < N; i++) {
    if (fork() == 0) {
        // child work
        exit(0);
    }
}
for (int i = 0; i < N; i++) wait(NULL);
```

### Get Exit Status
```c
int status;
wait(&status);
int code = WEXITSTATUS(status);
```

---

## 14. PROCESS HIERARCHY

```
init (PID=1)
  ├── shell (bash/zsh)
  │     ├── program (parent)
  │     │     ├── child 1
  │     │     └── child 2
  │     └── another program
  └── system services
```

**Key Points:**
- Every process has exactly **one parent**
- A process can have **multiple children**
- **init (PID=1)** is ancestor of all processes
- When parent dies → children adopted by init

---

## 15. COMPILATION & TESTING

### Compile
```bash
g++ -o program program.cpp
gcc -o program program.c
```

### Run & Observe
```bash
./program &              # run in background
ps -l                    # check state
ps aux | grep program    # find your process
```

### Check for Zombies
```bash
ps aux | grep Z          # find zombie processes
ps aux | grep defunct    # alternative
```

---

## 16. FORMULAS TO REMEMBER

| Concept | Formula |
|---------|---------|
| **Sequential forks** | Total processes = $2^n$ |
| **Process tree depth** | Depth = n (for n sequential forks from same parent) |
| **Max zombie processes** | Equal to number of children if parent doesn't wait |

---

## SUMMARY CHECKLIST FOR EXAM

- [ ] Know fork() return values: >0, 0, <0
- [ ] Understand zombie vs orphan difference
- [ ] Calculate $2^n$ processes for n forks
- [ ] Remember child MUST exit in loops
- [ ] Know wait() prevents zombies
- [ ] Understand WEXITSTATUS() extracts exit code
- [ ] Remember getpid() vs getppid()
- [ ] Know state symbols: R, S, Z, T
- [ ] Understand fork() creates copy, exec() replaces
- [ ] Remember orphans adopted by init (PID=1)

---

**Good Luck! 🚀**
