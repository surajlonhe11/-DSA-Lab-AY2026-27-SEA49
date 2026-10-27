# Practical No. 5: Circular Queue Implementation Using Array for Parcel Handling System

**Course:** Data Structures and Algorithms Lab (ET-MDM-S07)
**Class:** S.Y. B.Tech. E&TC, Hope Foundation's International Institute of Information Technology, Pune

---

## Problem Statement

Design and implement a circular queue using a static array to simulate a parcel handling system at a post office. Parcels arrive and are queued in a First-In-First-Out (FIFO) manner. The system should support operations such as adding a parcel to the queue, deleting a parcel once processed, and displaying the current queue status.

## Objectives

- To understand the concept of circular queues and their advantages over linear queues.
- To implement queue operations using a static array.
- To simulate a real-world scenario where resources are managed efficiently using FIFO logic.
- To develop skills in managing front and rear pointers in circular data structures.

## Algorithm / Approach

**Initialization**

```c
#define SIZE 5
int queue[SIZE];
int front = -1, rear = -1;   // front == -1 means the queue is empty
```

**1. Add parcel (Enqueue)**
1. Check if the queue is full: `front == (rear + 1) % SIZE`. If full, report it and stop.
2. If the queue is empty, set `front = rear = 0`.
3. Otherwise set `rear = (rear + 1) % SIZE`.
4. Insert the parcel ID at `queue[rear]`.

**2. Delete parcel (Dequeue)**
1. Check if the queue is empty: `front == -1`. If empty, report it and stop.
2. Read the parcel at `queue[front]`.
3. If only one element is present (`front == rear`), set `front = rear = -1`.
4. Otherwise set `front = (front + 1) % SIZE`.

**3. Display queue**
1. If the queue is empty, print "Queue is empty".
2. Otherwise start at `front` and move forward using `i = (i + 1) % SIZE` until `rear` is reached, printing each parcel.

**Why circular?** In a linear queue, slots freed at the front are never reused, so the queue reports "full" even when there is space. The modulo operator `% SIZE` wraps `rear` back to index 0, so freed slots are reused.

## Data Structure / Concept Used

- **Circular queue** using a static array (FIFO)
- **Front and rear pointers** managed with modulo arithmetic
- **Full and empty conditions** for a circular queue
- **Wrap-around** using the `%` operator
- **Menu-driven program** using `do-while` and `switch`

## Test Cases

| # | Operation | Input / State | Expected result |
|---|-----------|---------------|-----------------|
| 1 | Add | Empty queue, parcel 101 | Added, `front = 0`, `rear = 0` |
| 2 | Add | Parcels 102 to 105 after 101 | Added, `rear` moves to 4, queue is full |
| 3 | Add | Queue full, parcel 106 | "Queue is full! Cannot add parcel 106." |
| 4 | Delete | Queue holds 101 to 105 | Parcel 101 processed, `front = 1` |
| 5 | Add (wrap-around) | After 2 deletions, parcel 107 | Stored at index 0, `rear = 0` |
| 6 | Delete | Empty queue | "Queue is empty! No parcel to process." |
| 7 | Delete | Queue with exactly one parcel | Removed, `front = rear = -1` |
| 8 | Display | Empty queue | "Queue is empty." |
| 9 | Display | Queue where `rear` is before `front` | Parcels listed in correct FIFO order |
| 10 | Menu | Invalid choice | "Invalid choice, try again." |

## Sample Input and Output

**Input sequence** (queue size is 5):

```
Add 101, 102, 103, 104, 105   -> queue is full
Add 106                       -> rejected, queue is full
Delete, Delete                -> parcels 101 and 102 processed
Add 107, 108                  -> placed in the freed slots (wrap-around)
Display
```

**Pointer positions after each step:**

| Step | Operation | front | rear |
|------|-----------|-------|------|
| 1 | Add 101 | 0 | 0 |
| 2 | Add 102 | 0 | 1 |
| 3 | Add 103 | 0 | 2 |
| 4 | Add 104 | 0 | 3 |
| 5 | Add 105 | 0 | 4 (full) |
| 6 | Add 106 | 0 | 4 (rejected) |
| 7 | Delete (101) | 1 | 4 |
| 8 | Delete (102) | 2 | 4 |
| 9 | Add 107 | 2 | 0 (wrapped) |
| 10 | Add 108 | 2 | 1 (full again) |

**Output of Display:**

```
Parcels in queue (front -> rear):
  [index 2] Parcel 103  <- front
  [index 3] Parcel 104
  [index 4] Parcel 105
  [index 0] Parcel 107
  [index 1] Parcel 108  <- rear
front = 2, rear = 1
```

Parcels 107 and 108 sit at indexes 0 and 1, but they are still behind 103, 104 and 105 in FIFO order.

## Time Complexity

| Operation | Time complexity |
|-----------|-----------------|
| Add parcel (Enqueue) | O(1) |
| Delete parcel (Dequeue) | O(1) |
| Display queue | O(n), where n is the number of parcels in the queue |

## Space Complexity

The queue uses a fixed array of `SIZE` elements plus two pointers, so the space is **O(n)** for a capacity of `n` (here `SIZE = 5`). No extra space is needed per operation, which is **O(1)**.

## How to Compile and Run

```bash
gcc circular_queue.c -o circular_queue
./circular_queue
```

## Conclusion

The parcel handling system was implemented using a circular queue on a static array. Add and delete both took constant time, and the modulo operator allowed `rear` to wrap around to the start of the array, so slots freed by processed parcels were reused instead of wasted. Marking an empty queue with `front = -1` lets all 5 slots hold parcels at the same time. The practical showed how front and rear pointers are managed, how full and empty states are detected, and why a circular queue makes better use of memory than a linear queue.