# Practical No. 1: Displaying Patterns Using Numbers, Alphabets and Asterisks

**Course:** Data Structures and Algorithms Lab (ET-MDM-S07)
**Class:** S.Y. B.Tech. E&TC, Hope Foundation's International Institute of Information Technology, Pune

---

## Problem Statement

Write a C program to display the following patterns:

1. Right-angle triangle with numbers
2. Diamond shape with numbers
3. Pyramid with asterisks (`*`)
4. Pyramid using alphabets

## Objectives

- To understand the use of nested loops in C programming.
- To apply control structures (`for`/`while` loops and conditionals) for problem solving.
- To develop logic for generating structured output in pattern form.
- To practice basic programming constructs used in implementing data structures.

## Algorithm / Approach

All four patterns use an outer loop for rows and inner loops for spaces and printed characters.

**1. Right-angle triangle with numbers**
1. Read the number of rows `n`.
2. For each row `i = 1 to n`, print the numbers `1` to `i`, then move to a new line.

**2. Diamond with numbers**
1. Upper half: for `i = 1 to n`, print `n - i` spaces, then the digit `i` printed `i` times.
2. Lower half: for `i = n - 1 down to 1`, print `n - i` spaces, then the digit `i` printed `i` times.

**3. Pyramid with asterisks**
1. For each row `i = 1 to n`, print `n - i` spaces, then `i` asterisks separated by spaces.

**4. Pyramid using alphabets**
1. For each row `i = 1 to n`, print `2 * (n - i)` spaces.
2. Print letters from `'A'` up to the `i`-th letter (`'A' + j`).
3. Print letters back down to `'A'`, which forms the mirrored right half.

## Data Structure / Concept Used

- Nested `for` loops (outer loop for rows, inner loops for spaces and characters)
- Integer variables as loop counters
- ASCII arithmetic (`'A' + j`) to generate alphabets
- No data structure is used; this practical builds the loop logic needed for later practicals.

## Test Cases

| # | Input (`n`) | Expected behaviour |
|---|-------------|--------------------|
| 1 | 1 | Each pattern prints a single row (`1`, `1`, `*`, `A`) |
| 2 | 2 | Small patterns; diamond has 3 rows |
| 3 | 4 | Matches the patterns given in the lab manual |
| 4 | 5 | Larger patterns; diamond has 9 rows |
| 5 | 0 or negative | No pattern rows printed, only the headings |

## Sample Input and Output

**Input:** `n = 4`

```
Enter number of rows: 4

1. Right-angle triangle with numbers
1 
1 2 
1 2 3 
1 2 3 4 

2. Diamond with numbers
   1 
  2 2 
 3 3 3 
4 4 4 4 
 3 3 3 
  2 2 
   1 

3. Pyramid with asterisks
   * 
  * * 
 * * * 
* * * * 

4. Pyramid using alphabets
      A 
    A B A 
  A B C B A 
A B C D C B A 
```

## Time Complexity

Each pattern has a nested loop, so printing one pattern takes **O(n²)** time. The four patterns run one after another, so the total time is **O(n²)**.

## Space Complexity

Only a few integer variables are used, with no arrays or extra data structures, so the space complexity is **O(1)**.

## How to Compile and Run

```bash
gcc patterns.c -o patterns
./patterns
```

## Conclusion

The program displayed all four patterns correctly using nested loops. It showed how the outer loop controls rows while the inner loops control spaces and characters. The pyramid and diamond patterns showed why spacing must be calculated carefully, and the alphabet pyramid showed how ASCII values can generate letters. These loop-control skills are the basis for the data structure implementations in later practicals.