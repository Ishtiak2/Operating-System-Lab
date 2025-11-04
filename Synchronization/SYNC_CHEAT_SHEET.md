# 📝 Synchronization Concepts - Exam Cheat Sheet

Quick reference for process/thread synchronization, critical sections, and concurrency problems.

---

## 📋 Table of Contents

- [Core Concepts](#core-concepts)
- [Semaphore](#semaphore)
- [Mutex](#mutex)
- [Producer-Consumer Problem](#producer-consumer-problem)
- [Reader-Writer Problem](#reader-writer-problem)
- [Deadlock](#deadlock)
- [Comparison Table](#comparison-table)

---

## Core Concepts

| Term | Definition | Example |
|------|------------|---------|
| **Critical Section** | Code segment that accesses shared resources | Updating shared variable, file I/O |
| **Race Condition** | Multiple threads access shared data simultaneously causing incorrect results | Two threads incrementing same counter |
| **Mutual Exclusion** | Only one thread can execute critical section at a time | Lock mechanism |
| **Synchronization** | Coordination of multiple threads/processes to ensure correct execution order | Wait/signal mechanisms |
| **Atomic Operation** | Operation that completes without interruption | `sem_wait()`, `mutex.lock()` |
| **Busy Waiting** | Thread repeatedly checks condition in a loop (wastes CPU) | `while(!flag);` |

---

## Semaphore

### Definition
Integer variable used for signaling between threads. Two atomic operations: **wait** (P/down) and **signal** (V/up).

### Types

| Type | Value | Usage |
|------|-------|-------|
| **Binary Semaphore** | 0 or 1 | Mutex (mutual exclusion) |
| **Counting Semaphore** | 0 to N | Resource counting (e.g., buffer slots) |

### POSIX Semaphore Operations

| Operation | Syntax | Description |
|-----------|--------|-------------|
| **Initialize** | `sem_init(&sem, 0, value)` | Create semaphore with initial value |
| **Wait (P/down)** | `sem_wait(&sem)` | Decrement, block if 0 |
| **Signal (V/up)** | `sem_post(&sem)` | Increment, wake waiting thread |
| **Destroy** | `sem_destroy(&sem)` | Clean up semaphore |
| **Try Wait** | `sem_trywait(&sem)` | Non-blocking wait |
| **Get Value** | `sem_getvalue(&sem, &val)` | Get current value |

### Basic Pattern

```cpp
#include <semaphore.h>

sem_t sem;

void thread_func() {
    sem_wait(&sem);      // Enter critical section
    // ... critical section code ...
    sem_post(&sem);      // Exit critical section
}

int main() {
    sem_init(&sem, 0, 1); // Initialize to 1 (binary)
    // create threads...
    sem_destroy(&sem);    // Cleanup
}
```

### Example: Critical Section Protection

```cpp
sem_t sem;
int shared = 0;

void increment() {
    sem_wait(&sem);      // Lock
    shared++;            // Critical section
    sem_post(&sem);      // Unlock
}

int main() {
    sem_init(&sem, 0, 1);  // Binary semaphore
    // create threads that call increment()
    sem_destroy(&sem);
}
```

**Key Points:**
- `sem_init(&sem, 0, 1)` → Binary semaphore (mutex)
- `sem_init(&sem, 0, N)` → Counting semaphore (N resources)
- Always pair `sem_wait()` with `sem_post()`
- Use `0` as second parameter for thread synchronization

---

## Mutex

### Definition
**Mut**ual **Ex**clusion lock. Only one thread can hold the lock at a time.

### C++ Mutex Operations

| Operation | Syntax | Description |
|-----------|--------|-------------|
| **Lock** | `mtx.lock()` | Acquire lock (blocks if locked) |
| **Unlock** | `mtx.unlock()` | Release lock |
| **Try Lock** | `mtx.try_lock()` | Non-blocking lock attempt |
| **Lock Guard** | `lock_guard<mutex> lg(mtx)` | RAII-style automatic unlock |
| **Unique Lock** | `unique_lock<mutex> ul(mtx)` | More flexible lock management |

### Basic Pattern

```cpp
#include <mutex>

mutex mtx;
int shared = 0;

void thread_func() {
    mtx.lock();          // Acquire lock
    shared++;            // Critical section
    mtx.unlock();        // Release lock
}
```

### RAII Pattern (Recommended)

```cpp
void thread_func() {
    lock_guard<mutex> lock(mtx);  // Automatically unlocks
    shared++;                      // Critical section
}  // Lock released here automatically
```

**Key Points:**
- **Always unlock** what you lock (or use RAII)
- Mutex = Binary semaphore (but different implementation)
- `lock_guard` is safer (auto-unlocks on exception)
- Only the thread that locked can unlock

---

## Producer-Consumer Problem

### Problem Statement
- **Producer** creates items and puts in buffer
- **Consumer** takes items from buffer
- Buffer has **limited size**
- Need synchronization to avoid overflow/underflow

### Solution Components

| Component | Type | Initial Value | Purpose |
|-----------|------|---------------|---------|
| `mutex` | Binary Semaphore | 1 | Protect buffer access |
| `empty` | Counting Semaphore | N (buffer size) | Count empty slots |
| `full` | Counting Semaphore | 0 | Count filled slots |

### Pseudocode

```cpp
// Shared resources
int buffer[N];
int in = 0, out = 0;
sem_t mutex, empty, full;

// Initialize
sem_init(&mutex, 0, 1);    // Binary semaphore
sem_init(&empty, 0, N);    // N empty slots
sem_init(&full, 0, 0);     // 0 filled slots

// Producer
void producer() {
    while(true) {
        // Produce item
        item = produce_item();
        
        sem_wait(&empty);      // Wait for empty slot
        sem_wait(&mutex);      // Lock buffer
        
        buffer[in] = item;     // Add to buffer
        in = (in + 1) % N;
        
        sem_post(&mutex);      // Unlock buffer
        sem_post(&full);       // Signal filled slot
    }
}

// Consumer
void consumer() {
    while(true) {
        sem_wait(&full);       // Wait for filled slot
        sem_wait(&mutex);      // Lock buffer
        
        item = buffer[out];    // Remove from buffer
        out = (out + 1) % N;
        
        sem_post(&mutex);      // Unlock buffer
        sem_post(&empty);      // Signal empty slot
        
        consume_item(item);
    }
}
```

### Critical Order
1. **Producer**: `empty → mutex → ... → mutex → full`
2. **Consumer**: `full → mutex → ... → mutex → empty`

**Why this order?**
- Prevents deadlock (both waiting for each other)
- Resource counting before locking

---

## Reader-Writer Problem

### Problem Statement
- Multiple **readers** can read simultaneously
- Only one **writer** can write at a time
- Readers and writers cannot access simultaneously

### Solution Components

| Variable | Purpose |
|----------|---------|
| `read_count` | Number of active readers |
| `mutex` | Protects `read_count` |
| `wrt` | Protects writing |

### Pseudocode (Readers Preference)

```cpp
int read_count = 0;
sem_t mutex, wrt;

// Initialize
sem_init(&mutex, 0, 1);    // Protect read_count
sem_init(&wrt, 0, 1);      // Protect writing

// Reader
void reader() {
    sem_wait(&mutex);          // Lock read_count
    read_count++;
    if (read_count == 1)       // First reader
        sem_wait(&wrt);        // Block writers
    sem_post(&mutex);          // Unlock read_count
    
    // --- READING ---
    
    sem_wait(&mutex);          // Lock read_count
    read_count--;
    if (read_count == 0)       // Last reader
        sem_post(&wrt);        // Allow writers
    sem_post(&mutex);          // Unlock read_count
}

// Writer
void writer() {
    sem_wait(&wrt);            // Exclusive access
    
    // --- WRITING ---
    
    sem_post(&wrt);            // Release access
}
```

### Variants

| Variant | Priority | Starvation Risk |
|---------|----------|-----------------|
| **Readers Preference** | Readers first | Writers may starve |
| **Writers Preference** | Writers first | Readers may starve |
| **Fair/Balanced** | FIFO queue | No starvation |

**Key Points:**
- First reader locks `wrt`, last reader unlocks it
- Writers always wait for exclusive access
- Multiple readers can read simultaneously

---

## Deadlock

### Definition
Set of processes where each is waiting for a resource held by another, creating a circular wait.

### Four Necessary Conditions (Coffman Conditions)

| Condition | Description | Example |
|-----------|-------------|---------|
| **Mutual Exclusion** | Resources cannot be shared | Printer, mutex |
| **Hold and Wait** | Process holds resource while waiting for another | Thread holds lock A, waits for lock B |
| **No Preemption** | Resources cannot be forcibly taken | Cannot steal a locked mutex |
| **Circular Wait** | Circular chain of waiting processes | P1→P2→P3→P1 |

**All four must be present for deadlock!**

### Deadlock Example

```cpp
mutex mtx1, mtx2;

// Thread 1
void thread1() {
    mtx1.lock();      // Lock resource 1
    sleep(1);         // Delay
    mtx2.lock();      // Wait for resource 2 (DEADLOCK!)
    // ... work ...
    mtx2.unlock();
    mtx1.unlock();
}

// Thread 2
void thread2() {
    mtx2.lock();      // Lock resource 2
    sleep(1);         // Delay
    mtx1.lock();      // Wait for resource 1 (DEADLOCK!)
    // ... work ...
    mtx1.unlock();
    mtx2.unlock();
}
```

**What happens:**
- Thread 1 locks `mtx1`, Thread 2 locks `mtx2`
- Thread 1 waits for `mtx2` (held by T2)
- Thread 2 waits for `mtx1` (held by T1)
- **Circular wait = Deadlock!**

### Prevention Strategies

| Strategy | Method | Trade-off |
|----------|--------|-----------|
| **Prevent Mutual Exclusion** | Make resources shareable | Not always possible |
| **Prevent Hold & Wait** | Request all resources at once | Resource underutilization |
| **Allow Preemption** | Force resource release | Complex implementation |
| **Prevent Circular Wait** | Order resources, always lock in same order | Requires discipline |

### Solution: Resource Ordering

```cpp
// CORRECT: Both threads lock in same order
void thread1() {
    mtx1.lock();      // Lock in order: mtx1 first
    mtx2.lock();      // Then mtx2
    // ... work ...
    mtx2.unlock();
    mtx1.unlock();
}

void thread2() {
    mtx1.lock();      // Same order: mtx1 first
    mtx2.lock();      // Then mtx2
    // ... work ...
    mtx2.unlock();
    mtx1.unlock();
}
```

### Deadlock Handling Approaches

| Approach | Description | When to Use |
|----------|-------------|-------------|
| **Prevention** | Design system to prevent conditions | Critical systems |
| **Avoidance** | Dynamically check if request leads to deadlock (Banker's Algorithm) | Resource-intensive apps |
| **Detection & Recovery** | Let it happen, detect and recover | Rare deadlocks |
| **Ignore** | Ostrich algorithm (do nothing) | Low-risk systems |

---

## Comparison Table

### Semaphore vs Mutex

| Feature | Semaphore | Mutex |
|---------|-----------|-------|
| **Type** | Integer (0 to N) | Binary (locked/unlocked) |
| **Ownership** | No owner | Owned by locking thread |
| **Unlock** | Any thread can signal | Only owner can unlock |
| **Use Case** | Signaling, counting resources | Mutual exclusion |
| **Value** | Can be > 1 | Only 0 or 1 |
| **Example** | Buffer slots, thread barriers | Critical section protection |

### Binary Semaphore vs Mutex

| Aspect | Binary Semaphore | Mutex |
|--------|------------------|-------|
| **Functionally** | Similar | Similar |
| **Ownership** | None | Thread-owned |
| **Recursion** | Not supported | Can be recursive |
| **Priority Inversion** | Possible | Can prevent (priority inheritance) |
| **Performance** | Slightly slower | Optimized for mutual exclusion |

---

## Key Formulas & Patterns

### Producer-Consumer Invariants

```
empty + full = N (buffer size)
0 ≤ empty ≤ N
0 ≤ full ≤ N
```

### Reader-Writer Invariants

```
If writing == 1, then read_count == 0
If read_count > 0, then writing == 0
```

### Semaphore Invariant

```
sem_value = initial_value - (# of waits - # of posts)
```

---

## Common Mistakes ⚠️

| Mistake | Problem | Fix |
|---------|---------|-----|
| Forgetting to unlock | Deadlock | Use RAII (`lock_guard`) |
| Wrong semaphore order | Deadlock | Follow consistent order |
| Not initializing semaphore | Undefined behavior | Always `sem_init()` |
| Using same mutex for different purposes | Confusion | Use separate mutexes |
| Busy waiting | CPU waste | Use proper wait mechanisms |
| Not checking return values | Silent failures | Check `sem_wait()` return |

---

## Quick Patterns

### Critical Section (Semaphore)
```cpp
sem_wait(&sem);
// critical section
sem_post(&sem);
```

### Critical Section (Mutex)
```cpp
mtx.lock();
// critical section
mtx.unlock();
```

### Critical Section (RAII)
```cpp
{
    lock_guard<mutex> lock(mtx);
    // critical section
}  // auto unlock
```

### Barrier Synchronization
```cpp
// Wait for all threads to reach this point
sem_wait(&barrier);
if (++count == N) {
    for (int i = 0; i < N; i++)
        sem_post(&barrier);
}
```

### Signal Before Wait (Initialization)
```cpp
sem_init(&sem, 0, 0);  // Start at 0
// Thread 1
do_work();
sem_post(&sem);        // Signal completion
// Thread 2
sem_wait(&sem);        // Wait for signal
continue_work();
```

---

## Exam Tips 💡

1. **Semaphore value interpretation:**
   - Positive: Available resources
   - Zero: No resources, but no waiting
   - Negative: Number of waiting threads (theoretical)

2. **Order matters:**
   - Producer: `empty → mutex → mutex → full`
   - Consumer: `full → mutex → mutex → empty`

3. **Always pair:**
   - `sem_wait()` ↔ `sem_post()`
   - `lock()` ↔ `unlock()`
   - Initialize ↔ Destroy

4. **Prevent deadlock:**
   - Lock resources in consistent order
   - Use timeout mechanisms
   - Avoid nested locks when possible

5. **Common exam questions:**
   - Identify race conditions
   - Order of semaphore operations
   - Deadlock conditions (all 4 must exist!)
   - Producer-Consumer buffer states

---

**Good Luck on Your Exam! 🎓**

*Last Updated: November 4, 2025*
