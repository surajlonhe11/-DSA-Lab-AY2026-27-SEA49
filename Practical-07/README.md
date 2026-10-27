# Practical No. 7: Dynamic Text Editor Using Singly Linked List

**Course:** Data Structures and Algorithms Lab (ET-MDM-S07)
**Class:** S.Y. B.Tech. E&TC, Hope Foundation's International Institute of Information Technology, Pune

---

## Problem Statement

Design and implement a text editor that stores lines of text dynamically using a singly linked list. The system should support insertion and deletion of lines at any position, display the text in normal and reverse order, and allow reversing the entire list.

## Objectives

- To understand the structure and operations of singly linked lists.
- To implement dynamic storage and manipulation of text lines.
- To simulate a real-world application where data is frequently inserted, deleted, and reordered.
- To develop proficiency in pointer manipulation and linked list traversal.

## Algorithm / Approach

**Node structure**

```c
typedef struct Node {
    char text[200];       // one line of text
    struct Node *next;    // link to the next line
} Node;

Node *head = NULL;        // empty list
```

**1. Insert at front**
1. Create a new node.
2. Point the new node to `head`.
3. Update `head` to the new node.

**2. Insert at end**
1. Create a new node with `next = NULL`.
2. If the list is empty, make it the head.
3. Otherwise traverse to the last node and point it to the new node.

**3. Insert at position**
1. Check that `1 <= pos <= (number of lines + 1)`.
2. If `pos == 1`, insert at the front.
3. Otherwise traverse to node `pos - 1`.
4. Point the new node to `current->next`, then point `current->next` to the new node.

**4. Delete from front**
1. Store `head` in `temp`.
2. Update `head` to `head->next`.
3. Free `temp`.

**5. Delete from end**
1. If there is only one node, free it and set `head = NULL`.
2. Otherwise traverse to the second-last node.
3. Set its `next` to `NULL` and free the last node.

**6. Delete at position**
1. Check that `1 <= pos <= number of lines`.
2. If `pos == 1`, delete from the front.
3. Otherwise traverse to node `pos - 1`, store `current->next` in `temp`, set `current->next = temp->next` and free `temp`.

**7. Display**
1. Traverse from `head` to `NULL`, printing each line with its number.

**8. Display in reverse (recursion)**
1. Call the function on the next node first.
2. Print the current node after the recursive call returns, so the last line prints first.
3. The list itself is not changed.

**9. Reverse the list**
1. Initialize three pointers: `prev = NULL`, `current = head`, `next`.
2. While `current != NULL`: store `next = current->next`, reverse the link with `current->next = prev`, then move `prev = current` and `current = next`.
3. Update `head = prev`.

## Data Structure / Concept Used

- **Singly linked list** with dynamic memory allocation (`malloc` and `free`)
- **Pointer manipulation** and linked list traversal
- **Recursion** for displaying the list in reverse order
- **Iterative pointer reversal** with `prev`, `current` and `next`
- **Menu-driven program** using `do-while` and `switch`

## Test Cases

| # | Operation | Input / State | Expected result |
|---|-----------|---------------|-----------------|
| 1 | Insert at end | Empty list | The line becomes the head |
| 2 | Insert at front | List with lines | New line becomes line 1 |
| 3 | Insert at position | Position 3 in a list of 3 lines | New line becomes line 3, later lines shift down |
| 4 | Insert at position | Position larger than lines + 1 | "Invalid position" with the valid range |
| 5 | Delete from front | List with lines | First line removed |
| 6 | Delete from end | List with one line | Line removed, list becomes empty |
| 7 | Delete from end | List with several lines | Last line removed |
| 8 | Delete at position | Valid middle position | That line removed, the rest keep their order |
| 9 | Delete at position | Position outside the range | "Invalid position" with the valid range |
| 10 | Delete (any) | Empty list | "The text is empty. Nothing to delete." |
| 11 | Display | Empty list | "The text is empty." |
| 12 | Display in reverse | List with lines | Lines printed last to first, list unchanged |
| 13 | Reverse list | List with lines | Order of lines reversed permanently |
| 14 | Reverse list | Empty list | "Nothing to reverse" |
| 15 | Menu | Invalid choice | "Invalid choice, try again." |

## Sample Input and Output

**Input sequence:**

```
Insert at end:      Hello world
Insert at end:      This is line two
Insert at front:    First line
Insert at position: 3, "Inserted in middle"
Display
Display in reverse
Reverse the list
Display
Delete at position 2
Delete from end
Delete from front
Display
Delete at position 9
Delete from end
Delete from end
```

**Output of the inserts:**

```
Line inserted at the end.
Line inserted at the end.
Line inserted at the front.
Line inserted at position 3.
```

**Display (normal order):**

```
----- Text (normal order) -----
 1: First line
 2: Hello world
 3: Inserted in middle
 4: This is line two
-------------------------------
```

**Display in reverse order (list unchanged):**

```
----- Text (reverse order) -----
 4: This is line two
 3: Inserted in middle
 2: Hello world
 1: First line
--------------------------------
(Line numbers shown are the original positions.)
```

**After "Reverse the list", display:**

```
The list has been reversed.

----- Text (normal order) -----
 1: This is line two
 2: Inserted in middle
 3: Hello world
 4: First line
-------------------------------
```

**Deletions:**

```
Deleted line: Inserted in middle      (delete at position 2)
Deleted line: First line              (delete from end)
Deleted line: This is line two        (delete from front)

----- Text (normal order) -----
 1: Hello world
-------------------------------

Invalid position. Valid range is 1 to 1.     (delete at position 9)
Deleted line: Hello world                    (delete from end)
The text is empty. Nothing to delete.        (delete from end again)
```

The reverse display and the list reversal produce the same order on screen, but the reverse display leaves the list as it was, while the reversal changes the links permanently.

## Time Complexity

Let `n` be the number of lines in the list.

| Operation | Time complexity |
|-----------|-----------------|
| Insert / Delete at front | O(1) |
| Insert / Delete at end | O(n), because the list must be traversed |
| Insert / Delete at position | O(n) |
| Display | O(n) |
| Display in reverse (recursion) | O(n) |
| Reverse the list | O(n) |

## Space Complexity

- The list uses one node per line, so storage is **O(n)** and grows only as lines are added, unlike a fixed array.
- Reversing the list uses only three pointers, so it needs **O(1)** extra space.
- Displaying in reverse uses recursion, which needs **O(n)** space on the call stack.

## How to Compile and Run

```bash
gcc text_editor.c -o text_editor
./text_editor
```

## Conclusion

The text editor was implemented with a singly linked list, so lines are stored dynamically and the size of the text is not fixed in advance. Lines could be inserted and deleted at the front, the end and any position by changing pointers, with no shifting of data as an array would need. The text was displayed in normal order by traversal and in reverse order using recursion, and the whole list was reversed by flipping its links with three pointers. The practical gave good practice in pointer handling, dynamic memory with `malloc` and `free`, and checking for empty lists and invalid positions.