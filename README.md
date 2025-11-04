# Operating System Lab

This repository contains implementations of various operating system concepts in C++.

## 📁 Directory Structure

### Process/
Programs demonstrating process management concepts:
- `ProcessCreation.cpp` - Basic process creation using fork()
- `MultipleChild.cpp` - Creating multiple child processes
- `ProcessTermination.cpp` - Process termination scenarios
- `ZombieProcess.cpp` - Zombie process demonstration
- `OrphanProcess.cpp` - Orphan process demonstration

### Thread/
Multi-threading examples and implementations:
- `threadCreate.cpp` - Basic thread creation
- `sumOfArray.cpp` - Array sum using single thread
- `sumOfArray2.cpp` - Array sum with thread and reference wrapper
- `sumOfArrayMultithread.cpp` - Parallel array sum with multiple threads
- `sumOfArrayStructure.cpp` - Thread with structure parameter
- `multipleThread.cpp` - Multiple thread coordination
- `multiThreadUsingClass.cpp` - Thread using class-based design
- `sort.cpp` - Parallel sorting
- `minMax.cpp` - Finding min/max in parallel
- `ProducerConsumer.cpp` - Producer-consumer problem

### Synchronization/
Thread synchronization mechanisms:
- `semaphore.cpp` - Semaphore implementation for critical section protection

### try/
Experimental and practice code:
- Various test implementations for learning concepts

## 🛠️ Compilation

This project is configured to use **Homebrew GCC (g++-15)** with C++17 standard.

### Build and Run (VS Code)
- Press `Ctrl+Option+N` or click the ▶️ Run button
- Or press `Cmd+Shift+B` for build task

### Manual Compilation
```bash
# For thread programs (most files)
/opt/homebrew/bin/g++-15 -std=c++17 -pthread <filename>.cpp -o /tmp/<filename> && /tmp/<filename>

# For process programs (fork-based)
/opt/homebrew/bin/g++-15 -std=c++17 <filename>.cpp -o /tmp/<filename> && /tmp/<filename>
```

## 💡 Key Concepts Demonstrated

### Process Management
- Fork() system call
- Parent-child process relationships
- Process states (zombie, orphan)
- Process termination and wait()

### Multi-threading
- C++ `std::thread` vs POSIX `pthread`
- Thread creation and joining
- Lambda functions for thread creation
- Passing arguments to threads
- Reference wrappers with `std::ref()`

### Synchronization
- Semaphores (`sem_t`, `sem_wait`, `sem_post`)
- Critical sections
- Race condition prevention
- Thread-safe I/O using `printf`

## 🔧 Common Issues & Solutions

### Template Deduction Error (macOS)
**Problem:** `no matching constructor for initialization of 'thread'`

**Solution:** Use lambda functions:
```cpp
// Instead of:
thread t1(function, arg1, arg2, ref(result));

// Use:
thread t1([&]() { function(arg1, arg2, result); });
```

### Mixed Output in Multi-threaded Programs
**Problem:** Output from multiple threads gets garbled

**Solutions:**
1. Use `printf` instead of `cout` (more atomic)
2. Protect `cout` with mutex
3. Include all output inside semaphore/mutex protection

## 📝 Notes

- Executables are compiled to `/tmp/` directory to keep workspace clean
- Semaphore warnings on macOS are expected (deprecated but functional for learning)
- Always use `-pthread` flag when compiling threaded programs

## 👤 Author

Ishtiak Rahman

## 📅 Last Updated

November 2025
