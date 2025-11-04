# 📝 Multi-Threading in C++ - Exam Cheat Sheet

Quick reference for C++ `std::thread`, POSIX threads, and parallel programming concepts.

---

## 📋 Table of Contents

- [Thread Basics](#thread-basics)
- [Thread Creation Patterns](#thread-creation-patterns)
- [Passing Arguments](#passing-arguments)
- [Thread vs Process](#thread-vs-process)
- [Common Patterns](#common-patterns)
- [Thread Functions (pthread vs std::thread)](#thread-functions-pthread-vs-stdthread)
- [Synchronization Quick Reference](#synchronization-quick-reference)

---

## Thread Basics

### What is a Thread?

| Concept | Description |
|---------|-------------|
| **Thread** | Lightweight process; shares memory with parent |
| **Process** | Independent execution unit with own memory |
| **Concurrency** | Multiple threads making progress (not necessarily simultaneous) |
| **Parallelism** | Multiple threads executing simultaneously (multi-core) |
| **Main Thread** | Thread that starts when program runs |
| **Child Thread** | Thread created by main or another thread |

### Thread States

| State | Description |
|-------|-------------|
| **New** | Thread created but not started |
| **Runnable** | Ready to run, waiting for CPU |
| **Running** | Executing on CPU |
| **Blocked** | Waiting for resource (I/O, lock, etc.) |
| **Terminated** | Finished execution |

---

## Thread Creation Patterns

### 1. Basic Thread Creation

```cpp
#include <thread>
using namespace std;

void my_function() {
    // Thread work
}

int main() {
    thread t1(my_function);    // Create thread
    t1.join();                 // Wait for completion
    return 0;
}
```

### 2. Thread with Lambda

```cpp
thread t1([] {
    // Thread work
});
t1.join();
```

### 3. Thread with Parameters

```cpp
void func(int x, string s) {
    // Work with x and s
}

thread t1(func, 10, "hello");
t1.join();
```

### 4. Thread with Reference Parameter

```cpp
void func(int& result) {
    result = 42;
}

int value = 0;
thread t1(func, ref(value));  // Use std::ref()
t1.join();
cout << value;  // 42
```

### 5. Thread with Class Method

```cpp
class MyClass {
public:
    void method() { /* work */ }
};

MyClass obj;
thread t1(&MyClass::method, &obj);  // Pass method and object
t1.join();
```

### 6. Multiple Threads

```cpp
void worker(int id) {
    cout << "Thread " << id << endl;
}

int main() {
    thread threads[5];
    for (int i = 0; i < 5; i++) {
        threads[i] = thread(worker, i);
    }
    for (int i = 0; i < 5; i++) {
        threads[i].join();
    }
}
```

---

## Passing Arguments

### Argument Passing Rules

| Type | How to Pass | Example |
|------|-------------|---------|
| **By Value** | Direct parameter | `thread t1(func, x)` |
| **By Reference** | `std::ref()` | `thread t1(func, ref(x))` |
| **By Pointer** | Address | `thread t1(func, &x)` |
| **Array** | Array name (decays to pointer) | `thread t1(func, arr, size)` |
| **String Literal** | Direct | `thread t1(func, "text")` |
| **Lambda Capture** | `[&]` or `[=]` | `thread t1([&]() { ... })` |

### Examples

```cpp
// 1. By Value
void func1(int x) { x++; }
int a = 5;
thread t1(func1, a);        // 'a' copied, original unchanged
t1.join();

// 2. By Reference (std::ref)
void func2(int& x) { x++; }
int b = 5;
thread t2(func2, ref(b));   // 'b' modified
t2.join();
cout << b;  // 6

// 3. By Pointer
void func3(int* x) { (*x)++; }
int c = 5;
thread t3(func3, &c);       // 'c' modified via pointer
t3.join();
cout << c;  // 6

// 4. Multiple Parameters
void func4(int x, double y, string s) { }
thread t4(func4, 10, 3.14, "hello");
t4.join();

// 5. Array Parameter
void func5(int arr[], int size) { }
int numbers[5] = {1,2,3,4,5};
thread t5(func5, numbers, 5);
t5.join();

// 6. Lambda with Capture
int x = 10;
thread t6([&x]() {          // Capture by reference
    x++;
});
t6.join();
cout << x;  // 11
```

---

## Thread vs Process

| Feature | Thread | Process |
|---------|--------|---------|
| **Memory** | Shared with parent | Separate memory space |
| **Creation Cost** | Lightweight (faster) | Heavyweight (slower) |
| **Communication** | Direct (shared memory) | IPC (pipes, sockets, etc.) |
| **Context Switch** | Faster | Slower |
| **Independence** | Not independent | Independent |
| **Isolation** | No isolation | Isolated |
| **Creation Function** | `std::thread` or `pthread_create` | `fork()` |
| **Use Case** | Parallel tasks in same program | Independent programs |

---

## Common Patterns

### Pattern 1: Parallel Array Sum (Divide & Conquer)

```cpp
void partial_sum(int arr[], int start, int end, int& result) {
    result = 0;
    for (int i = start; i < end; i++) {
        result += arr[i];
    }
}

int main() {
    int arr[100];
    int sum1 = 0, sum2 = 0;
    
    thread t1(partial_sum, arr, 0, 50, ref(sum1));
    thread t2(partial_sum, arr, 50, 100, ref(sum2));
    
    t1.join();
    t2.join();
    
    int total = sum1 + sum2;
}
```

### Pattern 2: Using Structure for Thread Data

```cpp
struct ThreadData {
    int* array;
    int start, end;
    int result;
};

void compute(ThreadData* data) {
    data->result = 0;
    for (int i = data->start; i < data->end; i++) {
        data->result += data->array[i];
    }
}

int main() {
    int arr[100];
    ThreadData data1 = {arr, 0, 50, 0};
    ThreadData data2 = {arr, 50, 100, 0};
    
    thread t1(compute, &data1);
    thread t2(compute, &data2);
    
    t1.join();
    t2.join();
    
    int total = data1.result + data2.result;
}
```

### Pattern 3: Thread Pool (Fixed Number of Workers)

```cpp
void worker(int id) {
    cout << "Worker " << id << " processing\n";
}

int main() {
    const int NUM_THREADS = 4;
    thread workers[NUM_THREADS];
    
    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        workers[i] = thread(worker, i);
    }
    
    // Wait for all
    for (int i = 0; i < NUM_THREADS; i++) {
        workers[i].join();
    }
}
```

### Pattern 4: Producer-Consumer

```cpp
#include <queue>
#include <mutex>
#include <condition_variable>

queue<int> buffer;
mutex mtx;
condition_variable cv;

void producer() {
    for (int i = 0; i < 10; i++) {
        unique_lock<mutex> lock(mtx);
        buffer.push(i);
        cv.notify_one();
    }
}

void consumer() {
    for (int i = 0; i < 10; i++) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, []{ return !buffer.empty(); });
        int item = buffer.front();
        buffer.pop();
        lock.unlock();
        // Process item
    }
}
```

### Pattern 5: Barrier Synchronization (Wait for All)

```cpp
#include <barrier>  // C++20

barrier sync_point(3);  // 3 threads

void worker(int id) {
    // Phase 1 work
    cout << "Thread " << id << " phase 1\n";
    
    sync_point.arrive_and_wait();  // Wait for all
    
    // Phase 2 work
    cout << "Thread " << id << " phase 2\n";
}
```

---

## Thread Functions (pthread vs std::thread)

### C++ `std::thread` (Recommended)

| Operation | Syntax | Description |
|-----------|--------|-------------|
| **Include** | `#include <thread>` | Header file |
| **Create** | `thread t(func, args...)` | Create and start thread |
| **Join** | `t.join()` | Wait for thread to finish |
| **Detach** | `t.detach()` | Let thread run independently |
| **Get ID** | `t.get_id()` | Get thread identifier |
| **Joinable** | `t.joinable()` | Check if can be joined |
| **Hardware Concurrency** | `thread::hardware_concurrency()` | Number of CPU cores |
| **Sleep** | `this_thread::sleep_for(1s)` | Sleep current thread |
| **Yield** | `this_thread::yield()` | Give up CPU to other threads |

### POSIX Threads (`pthread`)

| Operation | Syntax | Description |
|-----------|--------|-------------|
| **Include** | `#include <pthread.h>` | Header file |
| **Create** | `pthread_create(&t, NULL, func, arg)` | Create thread |
| **Join** | `pthread_join(t, NULL)` | Wait for completion |
| **Exit** | `pthread_exit(NULL)` | Terminate thread |
| **Self** | `pthread_self()` | Get current thread ID |
| **Detach** | `pthread_detach(t)` | Detach thread |

### Comparison Example

```cpp
// C++ std::thread
#include <thread>

void work() { /* ... */ }

int main() {
    thread t(work);
    t.join();
}
```

```c
// POSIX pthread
#include <pthread.h>

void* work(void* arg) { 
    /* ... */
    return NULL;
}

int main() {
    pthread_t t;
    pthread_create(&t, NULL, work, NULL);
    pthread_join(t, NULL);
}
```

---

## Synchronization Quick Reference

### Mutex (C++)

```cpp
#include <mutex>

mutex mtx;

void critical_section() {
    mtx.lock();
    // Critical section
    mtx.unlock();
}

// Better: RAII style
void critical_section_safe() {
    lock_guard<mutex> lock(mtx);
    // Critical section
}  // Auto unlock
```

### Semaphore (POSIX)

```cpp
#include <semaphore.h>

sem_t sem;

void init() {
    sem_init(&sem, 0, 1);  // Binary semaphore
}

void critical_section() {
    sem_wait(&sem);
    // Critical section
    sem_post(&sem);
}
```

### Condition Variable (C++)

```cpp
#include <condition_variable>

mutex mtx;
condition_variable cv;
bool ready = false;

// Wait
void waiter() {
    unique_lock<mutex> lock(mtx);
    cv.wait(lock, []{ return ready; });
    // Proceed when ready
}

// Signal
void signaler() {
    {
        lock_guard<mutex> lock(mtx);
        ready = true;
    }
    cv.notify_one();
}
```

---

## Thread Safety Issues

### Race Condition

**Problem:**
```cpp
int counter = 0;  // Shared

void increment() {
    for (int i = 0; i < 1000; i++) {
        counter++;  // NOT thread-safe!
    }
}

// Result: counter < 2000 (some increments lost)
```

**Solution:**
```cpp
mutex mtx;
int counter = 0;

void increment() {
    for (int i = 0; i < 1000; i++) {
        lock_guard<mutex> lock(mtx);
        counter++;  // Thread-safe
    }
}

// Result: counter = 2000 (correct)
```

### Data Race

**Problem:**
```cpp
int data = 0;

void writer() { data = 42; }
void reader() { cout << data; }

// No synchronization = undefined behavior!
```

**Solution:**
```cpp
mutex mtx;
int data = 0;

void writer() {
    lock_guard<mutex> lock(mtx);
    data = 42;
}

void reader() {
    lock_guard<mutex> lock(mtx);
    cout << data;
}
```

---

## Common Thread Operations

| Operation | Code | Purpose |
|-----------|------|---------|
| **Create & Start** | `thread t(func)` | Launch thread |
| **Wait for Completion** | `t.join()` | Block until thread finishes |
| **Run Independently** | `t.detach()` | Thread runs on its own |
| **Check Joinable** | `if (t.joinable())` | Can we join? |
| **Get Thread Count** | `thread::hardware_concurrency()` | CPU cores available |
| **Sleep** | `this_thread::sleep_for(chrono::seconds(1))` | Pause thread |
| **Yield CPU** | `this_thread::yield()` | Let other threads run |
| **Get Current ID** | `this_thread::get_id()` | ID of calling thread |

---

## Lambda Capture Modes

| Capture | Syntax | Meaning | Example |
|---------|--------|---------|---------|
| **By Reference** | `[&]` | All by reference | `thread t([&]() { x++; })` |
| **By Value** | `[=]` | All by value (copy) | `thread t([=]() { cout << x; })` |
| **Specific Ref** | `[&x]` | Only `x` by reference | `thread t([&x]() { x++; })` |
| **Specific Value** | `[x]` | Only `x` by value | `thread t([x]() { cout << x; })` |
| **Mixed** | `[&, x]` | All ref except `x` | `thread t([&, x]() { y++; })` |
| **Nothing** | `[]` | No capture | `thread t([]() { cout << 5; })` |

---

## Performance Considerations

| Factor | Guideline |
|--------|-----------|
| **Number of Threads** | ≈ Number of CPU cores for CPU-bound tasks |
| **Thread Overhead** | Creating thread costs ~1-10 microseconds |
| **Context Switch** | Expensive; minimize lock contention |
| **False Sharing** | Avoid adjacent data modified by different threads |
| **Lock Granularity** | Fine-grained = more parallelism, more overhead |
| **Thread Pool** | Reuse threads instead of creating/destroying |

---

## Common Mistakes ⚠️

| Mistake | Problem | Solution |
|---------|---------|----------|
| **Forgetting join/detach** | Program terminates, thread killed | Always `join()` or `detach()` |
| **Joining detached thread** | Exception thrown | Check `joinable()` first |
| **Passing temporary by ref** | Undefined behavior | Use `ref()` with caution |
| **Not using `std::ref()`** | Value copied instead of referenced | Wrap with `ref()` |
| **Shared data without sync** | Race condition | Use mutex/semaphore |
| **Deadlock** | Two threads wait for each other | Lock in consistent order |
| **Using `cout` from multiple threads** | Garbled output | Use mutex or `printf` |

---

## Compilation Flags

```bash
# Compile with pthread support
g++ -std=c++17 -pthread file.cpp -o program

# macOS with Homebrew GCC
/opt/homebrew/bin/g++-15 -std=c++17 -pthread file.cpp -o program
```

---

## Quick Code Templates

### Template 1: Single Thread with Arguments

```cpp
#include <iostream>
#include <thread>
using namespace std;

void worker(int id, string name) {
    cout << "Thread " << id << ": " << name << endl;
}

int main() {
    thread t1(worker, 1, "Worker1");
    t1.join();
    return 0;
}
```

### Template 2: Multiple Threads

```cpp
#include <iostream>
#include <thread>
#include <vector>
using namespace std;

void task(int id) {
    cout << "Task " << id << endl;
}

int main() {
    vector<thread> threads;
    
    for (int i = 0; i < 5; i++) {
        threads.push_back(thread(task, i));
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    return 0;
}
```

### Template 3: Thread with Shared Data (Protected)

```cpp
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex mtx;
int shared_counter = 0;

void increment() {
    for (int i = 0; i < 1000; i++) {
        lock_guard<mutex> lock(mtx);
        shared_counter++;
    }
}

int main() {
    thread t1(increment);
    thread t2(increment);
    
    t1.join();
    t2.join();
    
    cout << "Counter: " << shared_counter << endl;  // 2000
    return 0;
}
```

---

## Exam Tips 💡

1. **Always remember `join()` or `detach()`** - Forgetting causes termination!

2. **Use `std::ref()` for references** - Direct parameter copies by default

3. **Lambda is easiest on macOS** - Avoids template deduction issues

4. **Thread-safe output** - Use `printf` or protect `cout` with mutex

5. **Common exam patterns:**
   - Parallel array processing
   - Producer-consumer
   - Thread synchronization order
   - Race condition identification

6. **Key differences to know:**
   - Thread vs Process
   - `pthread` vs `std::thread`
   - `join()` vs `detach()`
   - Pass by value vs reference

---

**Good Luck on Your Exam! 🎓**

*Last Updated: November 4, 2025*
