# 📌 Data Structure Lab – Assignment 3 (CS 2172) – Queue  

## 📜 Overview  
This assignment focuses on implementing an **integer queue** using the **circular queue** concept in C.  
The task is divided into **two stages** for better understanding:  

- **Stage 1:** Without using a `count` variable.  
- **Stage 2:** With a `count` variable for easier management.  

It also includes a **simulation** problem where elements are processed and re-queued or dropped based on a fixed or random decrement value.  

---

## 🏗️ Functional Requirements  

| Function | Description |
|----------|-------------|
| `queue createIntegerQueue(int queueSize)` | Allocates and initializes space for the queue to hold a maximum of `queueSize` integers. Returns `queue` type or `NULL` if failed. |
| `int enqueueInteger(queue q, int d)` | Enqueues integer `d` into `q`. Returns `1` if successful, `0` if full. |
| `int dequeueInteger(queue q, int *dp)` | Dequeues an element from `q` and stores it at address `dp`. Returns `1` if successful, `0` if empty. |
| `int freeIntegerQueue(queue q)` | Frees allocated space for `q`. Returns `1` if successful, `0` if failed. |
| `int isIntegerQueueFull(queue q)` | Returns `1` if the queue is full or invalid, otherwise `0`. |
| `int isIntegerQueueEmpty(queue q)` | Returns `1` if the queue is empty or invalid, otherwise `0`. |

---

## 🔄 Simulation Steps  

1. **Initialize Queue** – Create `myQueue` of size `N`.  
2. **Fill Queue** – Read positive integers until the queue is full.  
3. **Service Process** –  
   - Dequeue element (`qElement`)  
   - Subtract `rValue` (first fixed = `3`, then random between `1–9`)  
   - If result is positive → Enqueue back  
   - Else → Discard  
4. **Repeat** until queue is empty.  

---

## 📂 Files in Repository  

| File | Description |
|------|-------------|
| `assignment3_queue.c` | Full C implementation with queue ADT and simulation. |

---

## ⚙️ Compilation & Execution  
```bash
gcc assignment3_queue.c -o assignment3_queue
./assignment3_queue
```

---

## 🎯 Learning Outcomes  
- Mastery of **circular queue operations**.  
- Hands-on experience with **memory allocation & deallocation**.  
- Understanding **simulation processing** using queues.  
- Random number generation in C for dynamic operations.  

