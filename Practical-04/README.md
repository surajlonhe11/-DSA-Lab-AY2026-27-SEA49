# Practical No. 4: Decimal to Binary Conversion Using Stack

**Course:** Data Structures and Algorithms Lab (ET-MDM-S07)
**Class:** S.Y. B.Tech. E&TC, Hope Foundation's International Institute of Information Technology, Pune

---

## Problem Statement

Develop a program that converts a given decimal number into its binary equivalent using a stack data structure. The stack should be used to reverse the order of binary digits generated during the conversion process.

## Objectives

- To understand the use of stacks in algorithmic problem-solving.
- To implement decimal-to-binary conversion using LIFO (Last-In-First-Out) logic.
- To reinforce the concept of number systems and data structures.
- To simulate how intermediate results can be stored and retrieved using stacks.

## Algorithm / Approach

**Stack setup**

```c
#define SIZE 32
int stack[SIZE];
int top = -1;      // -1 means the stack is empty
```

**Stack operations**
- `push(x)`: if `top == SIZE - 1`, report overflow; otherwise increment `top` and store `x` at `stack[top]`.
- `pop()`: if `top == -1`, report underflow; otherwise return `stack[top]` and decrement `top`.
- `isEmpty()` and `isFull()` check the two limits.

**Conversion**
1. Initialize an empty stack (`top = -1`).
2. Input the decimal number.
3. If the number is 0, print `0` and stop.
4. Repeat until the number becomes 0:
   - Find the remainder: `remainder = number % 2`.
   - Push the remainder onto the stack.
   - Update the number: `number = number / 2`.
5. Pop and print each element from the stack. Because the last remainder pushed is the first one popped, the digits come out in the correct binary order.

**Why a stack?** The remainders are produced from the least significant bit to the most significant bit, which is the reverse of how binary is written. A stack reverses them automatically.

## Data Structure / Concept Used

- **Stack** implemented using an array (LIFO), with `push`, `pop`, `isEmpty` and `isFull`
- **Overflow and underflow** handling
- **Number systems:** decimal (base 10) and binary (base 2)
- **Repeated division by 2** using the `%` and `/` operators
- `while` loops and a `do-while` menu to repeat the conversion

## Test Cases

| # | Input | Expected binary output |
|---|-------|------------------------|
| 1 | 13 | 1101 |
| 2 | 10 | 1010 |
| 3 | 1 | 1 |
| 4 | 0 | 0 (handled as a special case) |
| 5 | 8 | 1000 |
| 6 | 255 | 11111111 |
| 7 | 2147483647 (largest `int`) | 31 ones (fits in the stack of size 32) |
| 8 | -5 | "Please enter a non-negative number." |
| 9 | Answer `y` at "Convert another number?" | Asks for a new number |

## Sample Input and Output

**Sample 1: input 13**

```
Enter a decimal number: 13

Step-by-step conversion:
Number     Quotient   Remainder 
-------------------------------
13         6          1         
6          3          0         
3          1          1         
1          0          1         

Stack (bottom -> top): 1 0 1 1 
Binary equivalent of 13: 1101
```

**Sample 2: input 10**

```
Enter a decimal number: 10

Step-by-step conversion:
Number     Quotient   Remainder 
-------------------------------
10         5          0         
5          2          1         
2          1          0         
1          0          1         

Stack (bottom -> top): 0 1 0 1 
Binary equivalent of 10: 1010
```

The remainders are pushed in the order 1, 0, 1, 1 and popped in the order 1, 1, 0, 1, which reverses them into the correct binary number.

## Time Complexity

- The loop runs once for every binary digit, which is about log₂(n) times for a number `n`, so the conversion takes **O(log n)** time.
- Each `push` and `pop` takes **O(1)** time.

## Space Complexity

- The stack holds one entry per binary digit, so the space needed is **O(log n)**.
- The array has a fixed size of 32, which is enough for any non-negative `int` (at most 31 binary digits).

## How to Compile and Run

```bash
gcc stack_binary.c -o stack_binary
./stack_binary
```

## Conclusion

The decimal to binary conversion was implemented using an array-based stack. Dividing by 2 gives the binary digits in reverse order, and the LIFO property of the stack reverses them back, so popping prints the correct binary number. The practical showed how push and pop work, how overflow and underflow are handled, and why a stack suits problems where the order of results must be reversed. Conversion takes O(log n) time and space, and every test case, including 0 and the largest `int`, gave the correct result.