# Practical No. 6: Train Ticket Booking System Using Queue

**Course:** Data Structures and Algorithms Lab (ET-MDM-S07)
**Class:** S.Y. B.Tech. E&TC, Hope Foundation's International Institute of Information Technology, Pune

---

## Problem Statement

A railway reservation system needs to manage train ticket bookings efficiently. Passengers requesting tickets should be given confirmed seats if seats are available. If all seats are occupied, additional passengers should be added to a waiting list. When a confirmed passenger cancels their ticket, the first passenger from the waiting list should be shifted to confirmed status. Implement a Queue-based train ticket booking system to manage confirmed bookings and waiting passengers.

## Objectives

- To understand the concept of Queue as a linear data structure.
- To implement queue operations such as insertion and deletion.
- To apply the FIFO (First In, First Out) principle in a real-world application.
- To manage confirmed and waiting-list train ticket bookings.
- To understand how cancellation affects waiting-list passengers.
- To develop problem-solving and data management skills using queues.

## Algorithm / Approach

**Storage**

```c
#define MAX_SEATS 5
#define MAX_WAIT  5

typedef struct {
    int bookingId;
    char name[50];
    int age;
    int seatNo;       // 0 while on the waiting list
} Passenger;

Passenger confirmed[MAX_SEATS];   // confirmed bookings
int confirmedCount = 0;
int seatTaken[MAX_SEATS + 1];     // seat map, 1 = taken

Passenger waiting[MAX_WAIT];      // waiting list as a circular queue
int wFront = 0, wCount = 0;
```

**Waiting queue operations**
- `enqueueWaiting(p)`: store `p` at index `(wFront + wCount) % MAX_WAIT`, then increment `wCount`.
- `dequeueWaiting()`: take the passenger at `wFront`, set `wFront = (wFront + 1) % MAX_WAIT`, then decrement `wCount`.

**1. Book ticket**
1. If no seat is free and the waiting list is full, reject the request.
2. Accept the passenger's name and age (age validated from 1 to 120).
3. Assign the next booking ID (starting at 1001).
4. If a seat is available, allocate the lowest free seat and add the passenger to the confirmed list.
5. Otherwise add the passenger to the waiting queue (`enqueueWaiting`) and show the waiting position.
6. Display the booking status.

**2. Cancel ticket**
1. Accept the booking ID to cancel.
2. Search the confirmed list. If found:
   - Remove the booking (shift later entries left) and free its seat.
   - If the waiting queue is not empty, `dequeueWaiting` the first passenger, give them the freed seat and add them to the confirmed list.
3. If not found there, search the waiting list. If found, remove that entry and close the gap, keeping the order of the others.
4. If the ID is in neither list, display "No booking found".

**3. Display bookings**
1. Display all confirmed passengers with their seat numbers.
2. Display the waiting list from front to rear with positions.
3. Display the number of seats available and the waiting list size.

## Data Structure / Concept Used

- **Queue (FIFO)** implemented as a circular queue on an array for the waiting list
- **Array of structures** (`Passenger`) for confirmed bookings
- **Seat map** array (`seatTaken[]`) to track which seats are free
- **Modulo arithmetic** for the wrap-around of the waiting queue
- **Linear search** by booking ID
- **Menu-driven program** using `do-while` and `switch`

## Test Cases

The train has 5 seats and the waiting list holds 5 passengers.

| # | Operation | Input / State | Expected result |
|---|-----------|---------------|-----------------|
| 1 | Book | First 5 passengers | All confirmed, seats 1 to 5 |
| 2 | Book | 6th passenger (train full) | Added to waiting list, position 1 |
| 3 | Book | 7th passenger | Added to waiting list, position 2 |
| 4 | Book | Train full and waiting list full | "all seats are booked and the waiting list is full" |
| 5 | Book | Age 0 or 150 | "Invalid age, try again." |
| 6 | Cancel | Confirmed booking 1002 with waiting list present | Seat 2 freed, first waiting passenger confirmed in seat 2 |
| 7 | Cancel | Confirmed booking with empty waiting list | Seat freed, no one promoted |
| 8 | Cancel | Waiting-list booking | Removed, remaining waiting passengers keep their order |
| 9 | Cancel | Booking ID 9999 (does not exist) | "No booking found with ID 9999." |
| 10 | Display | No bookings yet | "None." for both lists |
| 11 | Menu | Invalid choice | "Invalid choice, try again." |

## Sample Input and Output

**Input sequence** (5 seats, 7 passengers):

```
Book: Aarav Sharma (21), Neha Patil (20), Rahul Joshi (22),
      Sneha Kulkarni (19), Karan Mehta (23)     -> confirmed
Book: Amit Desai (25), Pooja Rane (24)          -> waiting list
Display
Cancel 1002
Display
Cancel 9999
Cancel 1007
Display
```

**Booking results:**

```
Booking CONFIRMED. Booking ID: 1001, Seat No: 1
Booking CONFIRMED. Booking ID: 1002, Seat No: 2
Booking CONFIRMED. Booking ID: 1003, Seat No: 3
Booking CONFIRMED. Booking ID: 1004, Seat No: 4
Booking CONFIRMED. Booking ID: 1005, Seat No: 5
Train is full. Added to WAITING LIST. Booking ID: 1006, Waiting position: 1
Train is full. Added to WAITING LIST. Booking ID: 1007, Waiting position: 2
```

**Display before any cancellation:**

```
===== CONFIRMED PASSENGERS =====
BookingID  Name                      Age   Seat 
------------------------------------------------
1001       Aarav Sharma              21    1    
1002       Neha Patil                20    2    
1003       Rahul Joshi               22    3    
1004       Sneha Kulkarni            19    4    
1005       Karan Mehta               23    5    

===== WAITING LIST (front to rear) =====
Pos   BookingID  Name                      Age  
------------------------------------------------
1     1006       Amit Desai                25   
2     1007       Pooja Rane                24   

Seats available : 0 of 5
Waiting list    : 2 of 5
```

**Cancel booking 1002:**

```
Booking 1002 (Neha Patil) cancelled. Seat 2 is now free.
Waiting-list passenger Amit Desai (Booking ID 1006) is now CONFIRMED with Seat 2.
```

**Display after the cancellation:**

```
===== CONFIRMED PASSENGERS =====
BookingID  Name                      Age   Seat 
------------------------------------------------
1001       Aarav Sharma              21    1    
1003       Rahul Joshi               22    3    
1004       Sneha Kulkarni            19    4    
1005       Karan Mehta               23    5    
1006       Amit Desai                25    2    

===== WAITING LIST (front to rear) =====
Pos   BookingID  Name                      Age  
------------------------------------------------
1     1007       Pooja Rane                24   

Seats available : 0 of 5
Waiting list    : 1 of 5
```

**Cancel booking 9999, then waiting-list booking 1007:**

```
No booking found with ID 9999.

Waiting-list booking 1007 (Pooja Rane) cancelled.
```

Amit Desai, who joined the waiting list first, got the freed seat before Pooja Rane. This is the FIFO principle in action.

## Time Complexity

Let `s` be the number of seats and `w` the waiting list size.

| Operation | Time complexity |
|-----------|-----------------|
| Enqueue / Dequeue on the waiting list | O(1) |
| Book ticket | O(s), to find the lowest free seat |
| Cancel ticket | O(s + w), to search both lists and shift entries |
| Display bookings | O(s + w) |

Because `s` and `w` are fixed small limits in this program, each operation is effectively constant time.

## Space Complexity

The program uses two fixed arrays, one for confirmed bookings and one for the waiting queue, plus a seat map, so the space is **O(s + w)**. Each operation uses only a few extra variables, which is **O(1)** additional space.

## How to Compile and Run

```bash
gcc ticket_booking.c -o ticket_booking
./ticket_booking
```

## Conclusion

The train ticket booking system was implemented with a circular queue for the waiting list and an array of structures for confirmed bookings. Passengers receive a confirmed seat while seats last and join the waiting queue afterwards. When a confirmed passenger cancels, the passenger at the front of the queue is promoted, so those who waited longest are served first. The practical showed how enqueue and dequeue work in a real scenario and how the FIFO principle gives fair treatment to waiting passengers. It also showed how edge cases such as a full train, a full waiting list, an unknown booking ID and cancellation from the waiting list can be handled.