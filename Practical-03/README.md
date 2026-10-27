# Practical No. 3: Searching Contact Names Using Sequential Search and Binary Search

**Course:** Data Structures and Algorithms Lab (ET-MDM-S07)
**Class:** S.Y. B.Tech. E&TC, Hope Foundation's International Institute of Information Technology, Pune

---

## Problem Statement

You are building a contact manager application. A user wants to search for a specific contact name either by scanning the contacts one by one or by using a faster lookup method when the contact list is sorted. Write a program to locate a specific contact name using both Sequential Search and Binary Search techniques. Compare the results obtained using the two searching methods.

## Objectives

- To understand the concept of searching in data structures.
- To implement Sequential Search and Binary Search techniques.
- To compare the working and efficiency of different searching algorithms.
- To understand the importance of sorted data for Binary Search.
- To apply searching techniques to a real-world contact management application.
- To develop algorithmic thinking and problem-solving skills.

## Algorithm / Approach

**Storage**

```c
typedef struct {
    char name[50];
    char phone[15];
} Contact;

Contact contacts[100];   // array of contacts
int n = 0;               // number of contacts stored
int isSorted = 0;        // 1 when the list is in alphabetical order
```

**1. Sequential (linear) search**
1. Start from the first contact.
2. Compare the current contact name with the search name using `strcmp`.
3. If they are equal, return the position.
4. Otherwise move to the next contact.
5. Repeat until the contact is found or the end of the list is reached.
6. If not found, display an appropriate message.

**2. Binary search**
1. Make sure the contacts are in alphabetical order (the program sorts them first if they are not).
2. Set `low = 0` and `high = n - 1`.
3. Calculate `mid = (low + high) / 2`.
4. Compare the middle contact name with the search name.
5. If equal, return the position.
6. If the search name comes before the middle name, set `high = mid - 1`.
7. If it comes after, set `low = mid + 1`.
8. Repeat steps 3 to 7 until the contact is found or `low > high`.
9. If not found, display an appropriate message.

**3. Sorting and comparison**
- Contacts are sorted alphabetically with bubble sort, which stops early if a pass makes no swaps.
- Both searches count the comparisons they make. The compare option runs both searches on the same name and shows which one needed fewer comparisons.
- The `isSorted` flag becomes 0 whenever new contacts are added, so binary search never runs on unsorted data.

## Data Structure / Concept Used

- **Array of structures** to store contact names and phone numbers
- **Sequential (linear) search** for sorted or unsorted data
- **Binary search** (divide and conquer) for sorted data
- **Bubble sort** to arrange contacts alphabetically
- **String comparison** with `strcmp`
- **Menu-driven program** using `do-while` and `switch`

## Test Cases

The contact list used for the search cases is: Amit, Karan, Neha, Rahul, Sneha (sorted order).

| # | Operation | Input | Expected result |
|---|-----------|-------|-----------------|
| 1 | Sequential search | "Neha" | Found, 3 comparisons |
| 2 | Sequential search | "Zoya" (not in list) | Not found, 5 comparisons |
| 3 | Binary search | "Neha" (middle element) | Found, 1 comparison |
| 4 | Binary search | "Zoya" (not in list) | Not found, 3 comparisons |
| 5 | Binary search | Added in unsorted order | List is sorted automatically first |
| 6 | Compare both | "Sneha" | Same position, binary needs 2 fewer comparisons |
| 7 | Compare both | "Karan" | Sequential needs 1 fewer comparison |
| 8 | Search | List is empty | "No contacts available" |
| 9 | Search | "neha" (lowercase) | Not found, because matching is case-sensitive |
| 10 | Add contacts | More than the capacity of 100 | "Cannot add" message |
| 11 | Menu | Invalid choice | "Invalid choice, try again" |

## Sample Input and Output

**Input** (Add contacts, 5 contacts):

| Name | Phone |
|------|-------|
| Rahul | 9123456780 |
| Amit | 9876501234 |
| Neha | 9988776655 |
| Sneha | 9876543210 |
| Karan | 9012345678 |

**Display contacts (before sorting):**

```
No.   Name                           Phone
--------------------------------------------------
1     Rahul                          9123456780
2     Amit                           9876501234
3     Neha                           9988776655
4     Sneha                          9876543210
5     Karan                          9012345678

List is currently NOT sorted.
```

**Compare both searches for "Sneha":**

```
Binary search needs a sorted list. Sorting contacts first...

===== COMPARISON =====
Sequential search: found at position 5 - Sneha (9876543210), 5 comparison(s).
Binary search    : found at position 5 - Sneha (9876543210), 3 comparison(s).
Binary search used 2 fewer comparison(s).
```

**Compare both searches for "Karan":**

```
===== COMPARISON =====
Sequential search: found at position 2 - Karan (9012345678), 2 comparison(s).
Binary search    : found at position 2 - Karan (9012345678), 3 comparison(s).
Sequential search used 1 fewer comparison(s) here.
```

**Compare both searches for "Zoya" (not in the list):**

```
===== COMPARISON =====
Sequential search: contact NOT found (5 comparison(s)).
Binary search    : contact NOT found (3 comparison(s)).
Binary search used 2 fewer comparison(s).
```

Positions are reported in the sorted list (Amit, Karan, Neha, Rahul, Sneha). With only 5 contacts the difference is small, and sequential search can even win when the name is near the front. The gap in favour of binary search grows quickly as the list gets larger.

## Time Complexity

| Algorithm | Best case | Average / Worst case |
|-----------|-----------|----------------------|
| Sequential search | O(1) | O(n) |
| Binary search | O(1) | O(log n) |
| Bubble sort (needed before binary search) | O(n) | O(n²) |

Binary search is only faster overall when the list is already sorted or is searched many times after one sort.

## Space Complexity

- Both searches (iterative) use only a few integer variables: **O(1)**.
- Storing the contacts needs an array that grows with the number of contacts: **O(n)**.
- Sorting swaps contacts using one temporary variable, which is **O(1)** extra space.

## How to Compile and Run

```bash
gcc contacts.c -o contacts
./contacts
```

## Conclusion

Both Sequential Search and Binary Search were implemented and compared on the same contact list. Sequential search works on any list but may check every contact, giving O(n) time. Binary search needs sorted data but halves the search range at each step, giving O(log n) time. The comparison counts showed that binary search is much more efficient for larger lists, while for very small lists or names near the start, the difference is small. The practical also showed why sorted data matters, since the program sorts the contacts before every binary search.