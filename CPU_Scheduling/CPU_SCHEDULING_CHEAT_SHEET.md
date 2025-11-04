# 📝 CPU Scheduling Algorithms - Exam Cheat Sheet

Quick reference for CPU scheduling algorithms with formulas, examples, and comparisons.

---

## 📋 Table of Contents

- [Key Terms & Formulas](#key-terms--formulas)
- [FCFS (First Come First Serve)](#fcfs-first-come-first-serve)
- [SJF (Shortest Job First)](#sjf-shortest-job-first)
- [Priority Scheduling](#priority-scheduling)
- [Round Robin](#round-robin)
- [Comparison Table](#comparison-table)
- [Gantt Chart Examples](#gantt-chart-examples)
- [Problem-Solving Steps](#problem-solving-steps)

---

## Key Terms & Formulas

### Important Definitions

| Term | Definition | Formula |
|------|------------|---------|
| **Arrival Time (AT)** | Time when process enters ready queue | Given |
| **Burst Time (BT)** | CPU time required by process | Given |
| **Completion Time (CT)** | Time when process finishes execution | Calculated |
| **Turnaround Time (TAT)** | Total time from arrival to completion | **TAT = CT - AT** |
| **Waiting Time (WT)** | Time spent waiting in ready queue | **WT = TAT - BT** |
| **Response Time (RT)** | Time from arrival to first execution | **RT = First_Run - AT** |

### Key Formulas

```
TAT = CT - AT = WT + BT
WT = TAT - BT = CT - AT - BT
RT = First_Execution_Time - AT

Average TAT = Sum of all TAT / Number of processes
Average WT = Sum of all WT / Number of processes
CPU Utilization = (Total Busy Time / Total Time) × 100%
Throughput = Number of Processes / Total Time
```

### Performance Metrics

| Metric | Formula | Goal |
|--------|---------|------|
| **Average Waiting Time** | `Σ WT / n` | Minimize |
| **Average Turnaround Time** | `Σ TAT / n` | Minimize |
| **CPU Utilization** | `(Busy Time / Total Time) × 100%` | Maximize |
| **Throughput** | `Processes Completed / Time Unit` | Maximize |
| **Response Time** | `First Run - Arrival` | Minimize |

---

## FCFS (First Come First Serve)

### Algorithm
- **Non-preemptive**
- Processes executed in order of arrival
- Simple queue (FIFO - First In First Out)

### Characteristics

| Feature | Value |
|---------|-------|
| **Type** | Non-preemptive |
| **Selection Criteria** | Arrival time |
| **Starvation** | No |
| **Convoy Effect** | Yes (small processes wait for big ones) |
| **Implementation** | Simple (Queue) |
| **Average WT** | Can be high |

### Steps
1. Sort processes by arrival time
2. Execute in order (no interruption)
3. Calculate CT, TAT, WT for each

### Calculation Pattern

```
For each process i (in arrival order):
    if (current_time < AT[i]):
        current_time = AT[i]     // CPU idle
    
    CT[i] = current_time + BT[i]
    TAT[i] = CT[i] - AT[i]
    WT[i] = TAT[i] - BT[i]
    
    current_time = CT[i]
```

### Example

| Process | AT | BT |
|---------|----|----|
| P1 | 0 | 4 |
| P2 | 1 | 3 |
| P3 | 2 | 1 |

**Execution Order:** P1 → P2 → P3

**Calculations:**
```
P1: CT=4,  TAT=4-0=4,  WT=4-4=0
P2: CT=7,  TAT=7-1=6,  WT=6-3=3
P3: CT=8,  TAT=8-2=6,  WT=6-1=5

Avg WT = (0+3+5)/3 = 2.67
Avg TAT = (4+6+6)/3 = 5.33
```

**Gantt Chart:**
```
| P1    | P2   | P3 |
0       4      7   8
```

### Advantages & Disadvantages

| Advantages ✅ | Disadvantages ❌ |
|--------------|------------------|
| Simple to implement | High average waiting time |
| No starvation | Convoy effect |
| Fair (FIFO) | Not optimal for interactive systems |
| | Poor for time-sharing systems |

---

## SJF (Shortest Job First)

### Algorithm
- **Non-preemptive** (standard SJF)
- **Preemptive** (SRTF - Shortest Remaining Time First)
- Execute process with smallest burst time first

### Characteristics

| Feature | Non-Preemptive SJF | Preemptive (SRTF) |
|---------|-------------------|-------------------|
| **Type** | Non-preemptive | Preemptive |
| **Selection** | Shortest burst time | Shortest remaining time |
| **Starvation** | Possible (long processes) | Possible |
| **Context Switch** | Less | More |
| **Average WT** | Optimal (minimum) | Even better |
| **Implementation** | Moderate | Complex |

### Steps (Non-Preemptive)
1. Sort processes by burst time
2. Execute shortest job first
3. Calculate metrics

### Calculation Pattern

```
Sort processes by BT (ascending)

For each process i:
    WT[i] = Sum of BT of all previous processes
    TAT[i] = WT[i] + BT[i]
```

### Example (Non-Preemptive)

| Process | BT |
|---------|----|
| P1 | 6 |
| P2 | 2 |
| P3 | 8 |
| P4 | 3 |

**After sorting by BT:** P2(2) → P4(3) → P1(6) → P3(8)

**Calculations:**
```
P2: WT=0,     TAT=0+2=2
P4: WT=2,     TAT=2+3=5
P1: WT=2+3=5, TAT=5+6=11
P3: WT=2+3+6=11, TAT=11+8=19

Avg WT = (0+2+5+11)/4 = 4.5
Avg TAT = (2+5+11+19)/4 = 9.25
```

**Gantt Chart:**
```
| P2 | P4  | P1      | P3        |
0    2    5        11          19
```

### SRTF (Preemptive SJF)

**Algorithm:** At each time unit, execute process with shortest remaining time.

**Example:**

| Process | AT | BT |
|---------|----|----|
| P1 | 0 | 7 |
| P2 | 2 | 4 |
| P3 | 4 | 1 |
| P4 | 5 | 4 |

**Execution:**
- 0-2: P1 (remaining: 5)
- 2-4: P2 (remaining: 2) [P2 < P1]
- 4-5: P3 (remaining: 0) [P3 < P2 < P1]
- 5-7: P2 (remaining: 0) [P2 < P4 < P1]
- 7-11: P4 (remaining: 0)
- 11-16: P1 (remaining: 0)

### Advantages & Disadvantages

| Advantages ✅ | Disadvantages ❌ |
|--------------|------------------|
| Minimum average waiting time | Starvation of long processes |
| Optimal for batch systems | Requires knowing burst time (prediction) |
| Good throughput | Preemptive version has overhead |
| | Not practical (BT unknown in reality) |

---

## Priority Scheduling

### Algorithm
- **Non-preemptive** or **Preemptive**
- Execute process with highest priority
- Lower number = Higher priority (typically)

### Characteristics

| Feature | Non-Preemptive | Preemptive |
|---------|---------------|------------|
| **Type** | Non-preemptive | Preemptive |
| **Selection** | Highest priority | Highest priority |
| **Starvation** | Yes (low priority) | Yes |
| **Solution to Starvation** | Aging | Aging |
| **Context Switch** | Less | More |

### Priority Assignment

| Type | Description | Example |
|------|-------------|---------|
| **Static** | Fixed at creation | System processes = 0, User = 1 |
| **Dynamic** | Changes over time | Aging (priority increases with wait time) |
| **Internal** | OS decides | I/O bound vs CPU bound |
| **External** | User/admin sets | Payment, importance |

### Steps
1. Sort processes by priority (lower number = higher priority)
2. Execute highest priority first
3. Calculate metrics

### Calculation Pattern

```
Sort by priority (ascending if lower = higher)

For each process i:
    WT[i] = Sum of BT of higher priority processes
    TAT[i] = WT[i] + BT[i]
```

### Example

| Process | BT | Priority |
|---------|----|---------:|
| P1 | 10 | 3 |
| P2 | 1 | 1 |
| P3 | 2 | 4 |
| P4 | 1 | 5 |
| P5 | 5 | 2 |

**After sorting by Priority:** P2(1) → P5(2) → P1(3) → P3(4) → P4(5)

**Calculations:**
```
P2: WT=0,           TAT=0+1=1
P5: WT=1,           TAT=1+5=6
P1: WT=1+5=6,       TAT=6+10=16
P3: WT=1+5+10=16,   TAT=16+2=18
P4: WT=1+5+10+2=18, TAT=18+1=19

Avg WT = (0+1+6+16+18)/5 = 8.2
Avg TAT = (1+6+16+18+19)/5 = 12
```

**Gantt Chart:**
```
| P2 | P5     | P1          | P3 | P4 |
0    1        6            16   18  19
```

### Aging Solution

**Problem:** Low-priority processes may starve

**Solution:** Increase priority as waiting time increases

```
New_Priority = Old_Priority - (Waiting_Time / Aging_Factor)
```

### Advantages & Disadvantages

| Advantages ✅ | Disadvantages ❌ |
|--------------|------------------|
| Important tasks executed first | Starvation of low-priority |
| Flexible (dynamic priorities) | Complex implementation |
| Good for real-time systems | Requires priority assignment |
| | Aging overhead |

---

## Round Robin

### Algorithm
- **Preemptive**
- Each process gets fixed time quantum (time slice)
- Cyclic execution (circular queue)
- If not finished, goes to back of queue

### Characteristics

| Feature | Value |
|---------|-------|
| **Type** | Preemptive |
| **Time Quantum** | Fixed (e.g., 2ms, 4ms) |
| **Starvation** | No (fair sharing) |
| **Context Switch** | High |
| **Response Time** | Good |
| **Best For** | Time-sharing systems |

### Time Quantum Selection

| Quantum Size | Effect |
|--------------|--------|
| **Too Large** | Behaves like FCFS, poor response time |
| **Too Small** | Too many context switches, overhead |
| **Optimal** | 80% of processes finish within 1 quantum |
| **Typical** | 10-100 milliseconds |

### Steps
1. Set time quantum (TQ)
2. Execute each process for TQ (or remaining BT if less)
3. If not finished, move to back of queue
4. Repeat until all done

### Calculation Pattern

```
remaining_BT[] = BT[]  // Copy burst times
current_time = 0
queue = [all processes]

while (queue not empty):
    process = queue.front()
    
    if (remaining_BT[process] <= TQ):
        current_time += remaining_BT[process]
        CT[process] = current_time
        remaining_BT[process] = 0
    else:
        current_time += TQ
        remaining_BT[process] -= TQ
        queue.push_back(process)  // Add to end
        
TAT = CT - AT
WT = TAT - BT
```

### Example

| Process | AT | BT |
|---------|----|----|
| P1 | 0 | 5 |
| P2 | 1 | 3 |
| P3 | 2 | 1 |
| P4 | 3 | 2 |

**Time Quantum = 2**

**Execution Timeline:**
```
Time 0-2:  P1 runs (remaining: 3)
Time 2-4:  P2 runs (remaining: 1)
Time 4-5:  P3 runs (remaining: 0) ✓ Done
Time 5-7:  P4 runs (remaining: 0) ✓ Done
Time 7-9:  P1 runs (remaining: 1)
Time 9-10: P2 runs (remaining: 0) ✓ Done
Time 10-11: P1 runs (remaining: 0) ✓ Done
```

**Calculations:**
```
P1: CT=11, TAT=11-0=11, WT=11-5=6
P2: CT=10, TAT=10-1=9,  WT=9-3=6
P3: CT=5,  TAT=5-2=3,   WT=3-1=2
P4: CT=7,  TAT=7-3=4,   WT=4-2=2

Avg WT = (6+6+2+2)/4 = 4
Avg TAT = (11+9+3+4)/4 = 6.75
```

**Gantt Chart:**
```
| P1 | P2 | P3| P4 | P1 |P2|P1|
0    2    4   5   7    9 10 11
```

### Advantages & Disadvantages

| Advantages ✅ | Disadvantages ❌ |
|--------------|------------------|
| Fair time sharing | High context switch overhead |
| No starvation | Average waiting time can be high |
| Good response time | Performance depends on TQ |
| Best for interactive systems | Not optimal for batch jobs |
| Equal CPU share | Longer average TAT than SJF |

---

## Comparison Table

### Algorithm Comparison

| Algorithm | Type | Selection Criteria | Starvation | Avg WT | Context Switch | Use Case |
|-----------|------|-------------------|------------|--------|----------------|----------|
| **FCFS** | Non-preemptive | Arrival time | No | High | Low | Batch systems |
| **SJF** | Non-preemptive | Shortest burst | Yes | Optimal (min) | Low | Batch, known BT |
| **SRTF** | Preemptive | Shortest remaining | Yes | Better than SJF | High | Unknown |
| **Priority** | Both | Priority value | Yes | Varies | Varies | Real-time, importance |
| **Round Robin** | Preemptive | Time quantum | No | Moderate | High | Time-sharing, interactive |

### When to Use

| Scenario | Best Algorithm | Reason |
|----------|----------------|--------|
| **Batch processing** | FCFS or SJF | Simple, no user interaction |
| **Minimize average WT** | SJF or SRTF | Optimal |
| **Time-sharing system** | Round Robin | Fair, good response time |
| **Real-time system** | Priority | Critical tasks first |
| **Interactive system** | Round Robin | Good response time |
| **Mixed workload** | Multilevel Queue | Different algorithms for different types |

### Performance Summary

| Metric | FCFS | SJF | SRTF | Priority | Round Robin |
|--------|------|-----|------|----------|-------------|
| **Avg WT** | High | Min | Better | Varies | Moderate |
| **Avg TAT** | High | Min | Better | Varies | Moderate |
| **Response Time** | Poor | Poor | Good | Varies | Good |
| **Throughput** | Low | High | High | Varies | Moderate |
| **Context Switch** | Lowest | Low | High | Varies | Highest |
| **Starvation** | No | Yes | Yes | Yes | No |
| **Fairness** | Yes | No | No | No | Yes |

---

## Gantt Chart Examples

### How to Draw Gantt Chart

1. **Timeline**: Horizontal axis = time
2. **Processes**: Blocks showing which process runs when
3. **Labels**: Process name and time intervals

### Example 1: FCFS

**Processes:** P1(0,4), P2(1,3), P3(2,1)

```
| P1      | P2     | P3 |
0         4        7   8

Legend: Process(AT, BT)
```

### Example 2: Round Robin (TQ=2)

**Processes:** P1(0,5), P2(1,3)

```
| P1 | P2 | P1 | P2| P1|
0    2    4    6  7  8

P1 runs: 0-2, 4-6, 7-8 (total 5)
P2 runs: 2-4, 6-7 (total 3)
```

### Example 3: Priority

**Processes:** P1(BT=4,P=2), P2(BT=3,P=1), P3(BT=1,P=3)

```
| P2     | P1      | P3 |
0        3         7   8

Execution order by priority: P2(1) → P1(2) → P3(3)
```

---

## Problem-Solving Steps

### Step-by-Step Approach

**1. Identify Algorithm**
- Read problem carefully
- Note: preemptive vs non-preemptive

**2. Create Table**
```
Process | AT | BT | Priority | CT | TAT | WT
```

**3. Sort if Needed**
- FCFS: Sort by AT
- SJF: Sort by BT
- Priority: Sort by Priority

**4. Calculate Completion Times**
- Use algorithm rules
- Draw Gantt chart if helpful

**5. Calculate TAT and WT**
```
TAT = CT - AT
WT = TAT - BT
```

**6. Calculate Averages**
```
Avg TAT = Sum of TAT / n
Avg WT = Sum of WT / n
```

### Quick Formulas (Memorize!)

```
TAT = CT - AT
WT = TAT - BT = CT - AT - BT
RT = First_Run_Time - AT

For FCFS (no arrival gaps):
  WT[i] = WT[i-1] + BT[i-1]
  
For SJF (no arrival times):
  WT[i] = Sum of BT of all processes before i
  
For Round Robin:
  Track remaining_BT for each process
  Update after each TQ
```

---

## Common Exam Questions

### Type 1: Calculate Metrics

**Given:** Process table with AT, BT
**Find:** CT, TAT, WT, Avg TAT, Avg WT

**Answer Pattern:**
1. Apply algorithm
2. Fill table
3. Calculate averages

### Type 2: Gantt Chart

**Given:** Processes and algorithm
**Draw:** Gantt chart showing execution

### Type 3: Compare Algorithms

**Question:** Which is better for [scenario]?

**Answer:** Consider:
- Starvation
- Avg WT
- Context switches
- Use case

### Type 4: True/False

- SJF has minimum avg WT ✓
- FCFS can have convoy effect ✓
- Round Robin has starvation ✗
- Priority can cause starvation ✓

---

## Exam Tips 💡

1. **Formula Sheet:**
   ```
   TAT = CT - AT
   WT = TAT - BT
   ```

2. **Algorithm Selection:**
   - Minimum WT → SJF/SRTF
   - Fair + Interactive → Round Robin
   - Important tasks → Priority
   - Simple batch → FCFS

3. **Common Mistakes:**
   - Forgetting to sort (FCFS by AT, SJF by BT)
   - Wrong TAT formula (CT - AT, not CT - BT)
   - Forgetting CPU idle time in FCFS
   - Wrong time quantum application in RR

4. **Quick Checks:**
   - WT ≥ 0 (always)
   - TAT ≥ BT (always)
   - Sum of BT = Total execution time (no gaps)

5. **Gantt Chart Tips:**
   - Start at time 0
   - No overlapping
   - Mark all transitions
   - Label clearly

---

**Good Luck on Your Exam! 🎓**

*Last Updated: November 4, 2025*
