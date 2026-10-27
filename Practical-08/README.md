# Practical No. 8: Binary Search Tree Operations for Online Directory System

**Course:** Data Structures and Algorithms Lab (ET-MDM-S07)
**Class:** S.Y. B.Tech. E&TC, Hope Foundation's International Institute of Information Technology, Pune

---

## Problem Statement

Design and implement a Binary Search Tree (BST) to manage an online directory system where names are stored in sorted order. The system should support fast searching and allow recursive traversals: inorder, preorder, and postorder. Implement a search function to locate a specific name in the directory.

## Objectives

- To understand the structure and properties of Binary Search Trees.
- To implement recursive tree traversals for data organization and retrieval.
- To simulate a real-world application where sorted data and fast search are essential.
- To develop skills in recursive programming and tree-based data structures.

## Algorithm / Approach

**Node structure**

```c
typedef struct Node {
    char name[50];
    struct Node *left;     // names alphabetically smaller
    struct Node *right;    // names alphabetically larger
} Node;

Node *root = NULL;         // empty tree
```

Names are compared with `strcmp`. In every node, the left subtree holds smaller names and the right subtree holds larger names.

**1. Insert node (recursive)**
1. If the current position is empty, create the root or a new node there.
2. Otherwise compare the new name with the current node:
   - If it is smaller, go left.
   - If it is larger, go right.
   - If it is equal, the name already exists, so it is not added.
3. Insert at the first empty (`NULL`) position reached.

**2. Search name**
1. Start at the root.
2. While the node is not `NULL`:
   - If the name equals the node's name, it is found.
   - If it is smaller, move to the left child.
   - If it is larger, move to the right child.
3. If `NULL` is reached, the name is not found.

**3. Inorder traversal** (gives names in sorted order)
1. Traverse the left subtree.
2. Visit the current node.
3. Traverse the right subtree.

**4. Preorder traversal**
1. Visit the current node.
2. Traverse the left subtree.
3. Traverse the right subtree.

**5. Postorder traversal**
1. Traverse the left subtree.
2. Traverse the right subtree.
3. Visit the current node.

**Extra functions:** the program can also draw the tree sideways, count the nodes, find the height, and free all nodes (postorder) before exit.

## Data Structure / Concept Used

- **Binary Search Tree** with dynamic memory allocation (`malloc` and `free`)
- **Recursion** for insertion and for all three depth-first traversals
- **Iterative search** that follows the BST ordering rule
- **String comparison** with `strcmp` to order names
- **Menu-driven program** using `do-while` and `switch`

## Test Cases

| # | Operation | Input / State | Expected result |
|---|-----------|---------------|-----------------|
| 1 | Insert | First name into an empty tree | It becomes the root |
| 2 | Insert | 7 names (Mohan, Deepak, Rahul, Amit, Gita, Sneha, Zoya) | All added, 7 nodes, height 4 |
| 3 | Insert | A name that already exists | "already exists, not added" |
| 4 | Search | Name in the tree (Gita) | FOUND with the number of nodes visited |
| 5 | Search | Name at the deepest level (Zoya) | FOUND, most nodes visited |
| 6 | Search | Name not in the tree (Karan) | NOT found |
| 7 | Search | Empty tree | "The directory is empty." |
| 8 | Inorder | Any tree | Names in alphabetical order |
| 9 | Preorder / Postorder | Same tree | Root first / root last |
| 10 | Traversals and structure | Empty tree | "The directory is empty." |
| 11 | Insert | Names entered already sorted | Tree leans to one side, height equals node count |
| 12 | Menu | Invalid choice | "Invalid choice, try again." |

## Sample Input and Output

**Input:** add 7 names in this order: Mohan, Deepak, Rahul, Amit, Gita, Sneha, Zoya, then try to add Amit again.

**Insertion messages:**

```
'Mohan' added.
'Deepak' added.
'Rahul' added.
'Amit' added.
'Gita' added.
'Sneha' added.
'Zoya' added.

'Amit' already exists, not added.
```

**Searches:**

```
'Gita' FOUND (3 node(s) visited).
'Zoya' FOUND (4 node(s) visited).
'Karan' NOT found (3 node(s) visited).
```

**Traversals:**

```
Inorder   (sorted) : Amit  Deepak  Gita  Mohan  Rahul  Sneha  Zoya
Preorder           : Mohan  Deepak  Amit  Gita  Rahul  Sneha  Zoya
Postorder          : Amit  Gita  Deepak  Zoya  Sneha  Rahul  Mohan
```

**Tree structure** (root at the left, right subtree on top):

```
                  Zoya
            Sneha
      Rahul
Mohan
            Gita
      Deepak
            Amit

Nodes: 7, Height: 4
```

The same tree drawn as usual:

```
            Mohan
           /     \
      Deepak     Rahul
      /    \         \
   Amit    Gita      Sneha
                         \
                          Zoya
```

The shape of the tree depends on the order of insertion. Mohan was entered first, so it is the root.

## Time Complexity

Let `n` be the number of names and `h` the height of the tree.

| Operation | Balanced tree (h ≈ log n) | Worst case (skewed tree, h = n) |
|-----------|---------------------------|----------------------------------|
| Insert | O(log n) | O(n) |
| Search | O(log n) | O(n) |
| Inorder / Preorder / Postorder | O(n) | O(n) |

The worst case happens when names are inserted in already sorted order, because the tree then becomes a chain like a linked list. Every traversal visits each node exactly once, so it takes O(n) in all cases.

## Space Complexity

- The tree stores one node per name, so storage is **O(n)**.
- Recursive insertion and traversals use the call stack, which needs **O(h)** space: O(log n) for a balanced tree and O(n) for a skewed one.
- Iterative search uses **O(1)** extra space.

## How to Compile and Run

```bash
gcc bst_directory.c -o bst_directory
./bst_directory
```

## Conclusion

The online directory was implemented as a Binary Search Tree that keeps names in sorted order. Insertion and search followed the left-smaller, right-larger rule, so each comparison discards a whole subtree and the search is fast when the tree is balanced. The three recursive traversals were implemented, and the inorder traversal printed the names in alphabetical order, showing how a BST gives sorted output without a separate sort. The practical also showed that the tree's height, and so its speed, depends on the order of insertion, with a sorted input producing the slowest tree. It built useful skills in recursion, pointers and tree structures.