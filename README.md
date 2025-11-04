# 🖥️ Operating System Lab

A comprehensive collection of Operating System concepts implemented in C++ and Shell scripting.

---

## � Table of Contents

- [Process Management](#-process-management)
- [Multi-Threading](#-multi-threading)
- [Synchronization](#-synchronization)
- [CPU Scheduling](#-cpu-scheduling)
- [Shell Scripting](#-shell-scripting)
- [Compilation Guide](#-compilation-guide)
- [Common Issues](#-common-issues--solutions)

---

## 🔄 Process Management

Understanding process creation, lifecycle, and states.

| Program | Description | View Code |
|---------|-------------|-----------|
| Process Creation | Basic process creation using `fork()` | [`ProcessCreation.cpp`](Process/ProcessCreation.cpp) |
| Multiple Children | Creating and managing multiple child processes | [`MultipleChild.cpp`](Process/MultipleChild.cpp) |
| Process Termination | Different process termination scenarios | [`ProcessTermination.cpp`](Process/ProcessTermination.cpp) |
| Zombie Process | Demonstration of zombie process behavior | [`ZombieProcess.cpp`](Process/ZombieProcess.cpp) |
| Orphan Process | Understanding orphan process states | [`OrphanProcess.cpp`](Process/OrphanProcess.cpp) |

**Key Concepts:** `fork()`, `wait()`, parent-child relationships, process states

---

## 🧵 Multi-Threading

Parallel programming with C++ `std::thread`.

| Program | Description | View Code |
|---------|-------------|-----------|
| Thread Creation | Basic thread creation and joining | [`threadCreate.cpp`](Thread/threadCreate.cpp) |
| Sum of Array | Single threaded array summation | [`sumOfArray.cpp`](Thread/sumOfArray.cpp) |
| Sum with Reference | Using `std::ref()` for thread parameters | [`sumOfArray2.cpp`](Thread/sumOfArray2.cpp) |
| Parallel Sum | Multi-threaded array sum (divide & conquer) | [`sumOfArrayMultithread.cpp`](Thread/sumOfArrayMultithread.cpp) |
| Structure Parameter | Passing structures to threads | [`sumOfArrayStructure.cpp`](Thread/sumOfArrayStructure.cpp) |
| Class-Based Thread | Object-oriented thread design | [`multiThreadUsingClass.cpp`](Thread/multiThreadUsingClass.cpp) |
| Multiple Threads | Coordinating multiple concurrent threads | [`multipleThread.cpp`](Thread/multipleThread.cpp) |
| Parallel Sort | Multi-threaded sorting algorithm | [`sort.cpp`](Thread/sort.cpp) |
| Min/Max Finder | Finding minimum and maximum in parallel | [`minMax.cpp`](Thread/minMax.cpp) |
| Producer-Consumer | Classic producer-consumer problem | [`ProducerConsumer.cpp`](Thread/ProducerConsumer.cpp) |

**Key Concepts:** `std::thread`, lambda functions, `std::ref()`, parallel algorithms

---

## 🔐 Synchronization

Thread synchronization and critical section protection.

| Program | Description | View Code |
|---------|-------------|-----------|
| Semaphore | Semaphore-based critical section protection | [`semaphore.cpp`](Synchronization/semaphore.cpp) |
| Producer-Consumer | Producer-consumer with synchronization | [`ProducerConsumer.cpp`](Synchronization/ProducerConsumer.cpp) |
| Reader-Writer | Reader-writer problem solution | [`ReaderWriter.cpp`](Synchronization/ReaderWriter.cpp) |
| Deadlock | Deadlock demonstration and prevention | [`DeadLock.cpp`](Synchronization/DeadLock.cpp) |

**Key Concepts:** Semaphores (`sem_t`, `sem_wait`, `sem_post`), critical sections, race conditions, deadlock

---

## ⏰ CPU Scheduling

CPU scheduling algorithm implementations.

| Program | Description | View Code |
|---------|-------------|-----------|
| FCFS | First Come First Serve scheduling | [`FCFS.cpp`](CPU_Scheduling/FCFS.cpp) |
| SJF | Shortest Job First scheduling | [`SJF.cpp`](CPU_Scheduling/SJF.cpp) |
| Priority Scheduling | Priority-based process scheduling | [`PrioritySche.cpp`](CPU_Scheduling/PrioritySche.cpp) |
| Round Robin | Time-slice based round robin scheduling | [`RoundRobin.cpp`](CPU_Scheduling/RoundRobin.cpp) |

**Key Concepts:** Scheduling algorithms, turnaround time, waiting time, CPU utilization

---

## 🐚 Shell Scripting

Bash scripting examples and utilities.

| Script | Description | View Code |
|--------|-------------|-----------|
| Basic I/O | Input/output operations in bash | [`Basic_IO.sh`](Shell_Scripting/Basic_IO.sh) |
| Calculator | Simple arithmetic calculator | [`Basic_Calculator.sh`](Shell_Scripting/Basic_Calculator.sh) |
| Even/Odd Checker | Number parity checker | [`EvenOdd.sh`](Shell_Scripting/EvenOdd.sh) |
| Greatest of Three | Find largest among three numbers | [`GreatestOfThree.sh`](Shell_Scripting/GreatestOfThree.sh) |
| Sum Calculator | Sum of numbers from 1 to N | [`SumOfNumber.sh`](Shell_Scripting/SumOfNumber.sh) |
| Array Operations | Working with arrays in bash | [`Array.sh`](Shell_Scripting/Array.sh) |
| File Checker | Check file existence and properties | [`FileCheck.sh`](Shell_Scripting/FileCheck.sh) |
| File Counter | Count files and directories | [`CountFilesDirs.sh`](Shell_Scripting/CountFilesDirs.sh) |
| Word Counter | Count words in a file | [`WordCounter.sh`](Shell_Scripting/WordCounter.sh) |
| Find & Replace | Text find and replace utility | [`FindReplace.sh`](Shell_Scripting/FindReplace.sh) |
| Recursive Lister | List files recursively | [`RecursiveFileLister.sh`](Shell_Scripting/RecursiveFileLister.sh) |
| Backup Script | Automated backup utility | [`BackupScript.sh`](Shell_Scripting/BackupScript.sh) |

**Key Concepts:** Bash scripting, file operations, loops, conditionals, string manipulation

## 📝 Additional Notes

- ✅ All executables compile to `/tmp/` to keep workspace clean
- ✅ VS Code configured with Homebrew GCC-15 as default compiler
- ✅ Code Runner extension configured for one-click compilation
- ✅ Always use `-pthread` flag when compiling threaded programs
- ✅ Lambda functions recommended for thread creation on macOS

---

## 👤 Author

**Ishtiak Rahman**

---

## 📅 Last Updated

November 4, 2025
