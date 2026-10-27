# Practical No. 2: Student Result Database Management Using Array of Structures

**Course:** Data Structures and Algorithms Lab (ET-MDM-S07)
**Class:** S.Y. B.Tech. E&TC, Hope Foundation's International Institute of Information Technology, Pune

---

## Problem Statement

Design and implement a student result management system using an array of structures. The system should allow users to add new student records, update existing ones, search for specific students, and sort records based on performance metrics such as total marks or average. The database should store details like roll number, name, program, course, subject marks, total, and average.

## Objectives

- To understand the use of arrays and structures in C.
- To implement basic database operations such as insert, update, search, display, and sort.
- To develop logical thinking for managing structured data.
- To simulate a real-world student result management system.

## Algorithm / Approach

**Structure and storage**

```c
typedef struct {
    int rollNo;
    char name[50];
    char program[20];
    char course[20];
    float marks[5];
    float total;
    float average;
} Student;

Student s[100];   // array of structures
int count = 0;    // number of records stored
```

**1. Insert records**
1. Read `n`, the number of records to add (checked against the capacity of 100).
2. For each record, accept roll number (rejected if it already exists), name, program, course and 5 subject marks (each validated to be 0 to 100).
3. Calculate `total` = sum of the 5 marks and `average` = `total / 5`.
4. Store the record in `s[count]` and increment `count`.

**2. Display all records**
1. For `i = 0` to `count - 1`, print every field of `s[i]` in a table.

**3. Search (linear search)**
1. Input a roll number or a name.
2. Compare it with each record from `i = 0` to `count - 1` (`==` for roll number, `strcmp` for name).
3. Return the position on a match, or `-1` if not found.

**4. Sort (bubble sort, descending by total or average)**
1. Repeat for `i = 1` to `count - 1`:
   - For `j = 0` to `count - i - 1`, swap `s[j]` and `s[j+1]` if `s[j]` has the lower total (or average).
   - Display the comparisons made in this pass.
   - Stop early if a pass makes no swaps.
2. Display the total number of passes and the sorted records.

**5. Modify record**
1. Input the roll number and find the record using the search above.
2. Update the chosen field (name, program, course or marks).
3. Recalculate `total` and `average`.

**6. Append record**
1. Accept new student details, calculate total and average, store at `s[count]` and increment `count`.

## Data Structure / Concept Used

- **Structure (`struct`)** with `typedef`, grouping mixed-type data (int, char arrays, floats) for one student
- **Array of structures** to store up to 100 student records
- **Passing structures by pointer** (`Student *st`) to calculate totals and read marks
- **Linear search** and **bubble sort** applied to structure members
- **Menu-driven program** using `do-while` and `switch`

## Test Cases

| # | Operation | Input | Expected result |
|---|-----------|-------|-----------------|
| 1 | Insert | 3 valid students | 3 records added |
| 2 | Insert | Roll number that already exists | "Roll number already exists", asks again |
| 3 | Insert | Marks of -5 or 105 | "Invalid marks", asks again |
| 4 | Display | No records yet | "No records to display" |
| 5 | Search by roll | Existing roll number | Record found with its position |
| 6 | Search by name | Existing name | Record found with its position |
| 7 | Search | Roll number or name not present | "Record not found" |
| 8 | Sort by total | 3 or more records | Highest total first, passes and comparisons shown |
| 9 | Sort by average | 3 or more records | Highest average first |
| 10 | Sort | Fewer than 2 records | "Not enough records to sort" |
| 11 | Modify | Change marks of an existing roll number | Total and average recalculated |
| 12 | Modify | Roll number not present | "Record not found" |
| 13 | Append | Database already holds 100 records | "Database is full" |
| 14 | Menu | Invalid choice (e.g. 9) | "Invalid choice, try again" |

## Sample Input and Output

**Input** (Insert records, n = 3):

| Roll | Name | Program | Course | Marks |
|------|------|---------|--------|-------|
| 101 | Aarav Sharma | BTech | ENTC | 78 85 90 72 88 |
| 102 | Neha Patil | BTech | ENTC | 92 88 95 90 85 |
| 103 | Rahul Joshi | BTech | ENTC | 65 70 58 72 60 |

**Output of Display all records:**

```
Roll   Name                 Program    Course         M1     M2     M3     M4     M5    Total  Average
---------------------------------------------------------------------------------------------------
101    Aarav Sharma         BTech      ENTC         78.0   85.0   90.0   72.0   88.0   413.00    82.60
102    Neha Patil           BTech      ENTC         92.0   88.0   95.0   90.0   85.0   450.00    90.00
103    Rahul Joshi          BTech      ENTC         65.0   70.0   58.0   72.0   60.0   325.00    65.00
```

**Search by roll number 102:**

```
Record found at position 1.
```

**Sort by total (descending):**

```
Pass 1: 2 comparison(s)
Pass 2: 1 comparison(s)
Total number of passes: 2

Sorted records (highest total first):
102    Neha Patil           BTech      ENTC         92.0   88.0   95.0   90.0   85.0   450.00    90.00
101    Aarav Sharma         BTech      ENTC         78.0   85.0   90.0   72.0   88.0   413.00    82.60
103    Rahul Joshi          BTech      ENTC         65.0   70.0   58.0   72.0   60.0   325.00    65.00
```

(The position printed by search is the array index, which starts at 0.)

## Time Complexity

Let `n` be the number of stored records.

| Operation | Time complexity |
|-----------|-----------------|
| Insert / Append (one record) | O(n), because the duplicate roll number check is a linear search |
| Display all | O(n) |
| Search (linear) | O(n) |
| Sort (bubble sort) | O(n²) worst and average case, O(n) best case (already sorted, using the early exit) |
| Modify | O(n) for the search, then O(1) to update |

## Space Complexity

- The database is a fixed array of 100 `Student` structures, so storage grows with the number of records: **O(n)**.
- Sorting swaps records using one temporary `Student` variable, so it needs **O(1)** extra space.

## How to Compile and Run

```bash
gcc student.c -o student
./student
```

## Conclusion

The student result database was implemented using an array of structures, with insert, display, search, sort, modify and append operations working through a menu-driven interface. The practical showed how a structure groups mixed data types into one record and how an array of structures stores many such records. Linear search and bubble sort were applied to structure members, and the pass and comparison counts showed how the sort works. Input checks for duplicate roll numbers and invalid marks made the database more reliable. The same record-handling logic is used in later practicals.