# Practical No. 9: Graph Traversal for Campus Navigation Using BFS and DFS

**Course:** Data Structures and Algorithms Lab (ET-MDM-S07)
**Class:** S.Y. B.Tech. E&TC, Hope Foundation's International Institute of Information Technology, Pune

---

## Problem Statement

Design a navigation system for a campus consisting of multiple buildings. The system should explore possible paths between buildings using graph traversal techniques. Represent the campus as a graph using an adjacency matrix and implement Breadth-First Search (BFS) and Depth-First Search (DFS) to explore building connectivity.

## Objectives

- To understand graph representation using adjacency matrices.
- To implement BFS and DFS traversal algorithms.
- To simulate real-world navigation systems using graph theory.
- To develop skills in exploring and analyzing connectivity between nodes.

## Algorithm / Approach

**Graph representation**

```c
#define MAX 20
int adj[MAX][MAX];          // adj[i][j] = 1 means a direct path between building i and j
char names[MAX][30];        // building names
int n;                      // number of buildings
int visited[MAX];
```

Each building is a vertex and each path is an edge. Paths work in both directions (undirected graph), so `adj[u][v]` and `adj[v][u]` are both set to 1.

**1. Create the graph**
1. Input the number of buildings `n` and create an `n x n` adjacency matrix filled with 0.
2. Input the building names.
3. Input the number of connections, then each connection as a pair of building numbers.
4. Set `adj[u][v] = adj[v][u] = 1` for each valid connection. Paths to the same building or outside the range are ignored.

**2. Breadth-First Search (BFS)** (uses a queue)
1. Initialize the `visited[]` array to 0 and create an empty queue.
2. Mark the starting building as visited and enqueue it.
3. While the queue is not empty:
   - Dequeue a building and print it.
   - For each adjacent building that is not visited, mark it visited and enqueue it.

**3. Depth-First Search (DFS)** (recursive, so the call stack acts as the stack)
1. Initialize the `visited[]` array to 0.
2. Call `DFS(start)`.
3. `DFS(node)`: mark the node visited and print it, then for each adjacent node that is not visited, call `DFS(adjacent node)`.

**4. Connectivity check (extra)**
1. Repeatedly start a quiet DFS from every building not yet visited.
2. The number of starts needed is the number of separate groups of connected buildings. One group means the whole campus is connected.

## Data Structure / Concept Used

- **Graph** represented with an **adjacency matrix** (2D array)
- **Queue** (FIFO) used by BFS
- **Stack** (LIFO) used by DFS, through recursion
- **Visited array** to avoid visiting a building twice
- **Menu-driven program** using `do-while` and `switch`

## Test Cases

| # | Operation | Input / State | Expected result |
|---|-----------|---------------|-----------------|
| 1 | Create graph | 7 buildings, 7 valid paths | Matrix is symmetric |
| 2 | Create graph | A path from a building to itself (0 0) | "Invalid path, ignored." |
| 3 | Create graph | A path with a building number out of range | "Invalid path, ignored." |
| 4 | BFS | Start at MainGate | Nearest buildings first, level by level |
| 5 | DFS | Start at MainGate | Goes deep along one path before backtracking |
| 6 | BFS / DFS | Start inside a disconnected part | Reaches fewer buildings than the total |
| 7 | BFS / DFS | Starting building number out of range | "Invalid building number." |
| 8 | Traversal | Graph not created yet | "Create the graph first (option 1)." |
| 9 | Connectivity | Every building reachable | "The campus is fully connected" |
| 10 | Connectivity | Some building has no path | Reports the number of separate groups |
| 11 | Menu | Invalid choice | "Invalid choice, try again." |

## Sample Input and Output

**Campus used** (7 buildings, 7 paths):

| No. | Building |
|-----|----------|
| 0 | MainGate |
| 1 | Library |
| 2 | AdminBlock |
| 3 | Canteen |
| 4 | LabBlock |
| 5 | Hostel |
| 6 | SportsComplex |

Paths: 0-1, 0-2, 1-3, 1-4, 2-4, 3-5, 4-5. SportsComplex has no path.

```
MainGate ---- Library ---- Canteen
    |            |            |
AdminBlock ---- LabBlock ---- Hostel        SportsComplex (not connected)
```

(LabBlock is joined to both Library and AdminBlock and to Hostel. Canteen is joined to Library and Hostel.)

**Adjacency matrix:**

```
      0  1  2  3  4  5  6
  0   0  1  1  0  0  0  0
  1   1  0  0  1  1  0  0
  2   1  0  0  0  1  0  0
  3   0  1  0  0  0  1  0
  4   0  1  1  0  0  1  0
  5   0  0  0  1  1  0  0
  6   0  0  0  0  0  0  0
```

**BFS from MainGate:**

```
BFS from MainGate: MainGate Library AdminBlock Canteen LabBlock Hostel
Buildings reached: 6 of 7
```

**DFS from MainGate:**

```
DFS from MainGate: MainGate Library Canteen Hostel LabBlock AdminBlock
Buildings reached: 6 of 7
```

**BFS from Hostel:**

```
BFS from Hostel: Hostel Canteen LabBlock Library AdminBlock MainGate
Buildings reached: 6 of 7
```

**Connectivity check:**

```
The campus is NOT fully connected: it has 2 separate groups of buildings.
```

BFS visits MainGate's neighbours (Library, AdminBlock) first and then goes outward, while DFS follows Library to Canteen to Hostel to LabBlock before coming back to AdminBlock. Neither reaches SportsComplex because no path leads to it.

## Time Complexity

Let `V` be the number of buildings.

| Algorithm | Time complexity |
|-----------|-----------------|
| BFS | O(V²) with an adjacency matrix, because finding the neighbours of each building scans a full row of `V` entries |
| DFS | O(V²) with an adjacency matrix, for the same reason |
| Connectivity check | O(V²) |

With an adjacency list, both would take O(V + E).

## Space Complexity

- The adjacency matrix needs **O(V²)** space, which suits dense graphs and fixed-size campuses.
- BFS uses a queue and a visited array, so it needs **O(V)** extra space.
- DFS uses a visited array and the recursion stack, so it needs **O(V)** extra space.

## How to Compile and Run

```bash
gcc campus_graph.c -o campus_graph
./campus_graph
```

## Conclusion

The campus was modelled as an undirected graph stored in an adjacency matrix, and both BFS and DFS were implemented to explore it. BFS uses a queue and visits buildings in order of distance from the start, so it finds the nearest buildings first. DFS goes as deep as possible along one path before backtracking, using the recursion stack. Both reached the same set of buildings from a given start but in different orders, and neither could reach a building with no path to it. The connectivity check showed how traversal can be used to find out whether a campus is fully connected. The practical gave good practice with graph representation, queues, recursion and the visited array.