#include <stdio.h>
#include <string.h>

#define MAX 20
#define NAME_LEN 30

int adj[MAX][MAX];              /* adjacency matrix: 1 = direct path */
char names[MAX][NAME_LEN];      /* building names */
int n = 0;                      /* number of buildings */
int visited[MAX];

/* ---------- queue for BFS ---------- */

int queue[MAX];
int qFront = 0, qRear = -1;

int qEmpty(void)        { return qFront > qRear; }
void enqueue(int v)     { queue[++qRear] = v; }
int dequeue(void)       { return queue[qFront++]; }

/* ---------- graph input ---------- */

void createGraph(void) {
    int i, j, e, u, v;

    do {
        printf("Enter number of buildings (1 to %d): ", MAX);
        scanf("%d", &n);
    } while (n < 1 || n > MAX);

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            adj[i][j] = 0;

    printf("\nEnter the names of the buildings (no spaces, e.g. Library):\n");
    for (i = 0; i < n; i++) {
        printf("  Building %d: ", i);
        scanf(" %29s", names[i]);
    }

    printf("\nEnter number of connections (paths): ");
    scanf("%d", &e);

    printf("Enter each connection as two building numbers (0 to %d).\n", n - 1);
    for (i = 0; i < e; i++) {
        printf("  Path %d: ", i + 1);
        scanf("%d %d", &u, &v);
        if (u < 0 || u >= n || v < 0 || v >= n || u == v) {
            printf("  Invalid path, ignored.\n");
            continue;
        }
        adj[u][v] = adj[v][u] = 1;      /* paths work both ways */
    }
    printf("\nCampus graph created.\n");
}

void showMatrix(void) {
    int i, j;

    if (n == 0) {
        printf("Create the graph first.\n");
        return;
    }
    printf("\nBuildings:\n");
    for (i = 0; i < n; i++)
        printf("  %d = %s\n", i, names[i]);

    printf("\nAdjacency matrix:\n    ");
    for (j = 0; j < n; j++)
        printf("%3d", j);
    printf("\n");
    for (i = 0; i < n; i++) {
        printf("%3d ", i);
        for (j = 0; j < n; j++)
            printf("%3d", adj[i][j]);
        printf("\n");
    }
}

/* ---------- BFS ---------- */

void bfs(int start) {
    int i, v, count = 0;

    for (i = 0; i < n; i++)
        visited[i] = 0;
    qFront = 0;
    qRear = -1;

    visited[start] = 1;
    enqueue(start);

    printf("\nBFS from %s: ", names[start]);
    while (!qEmpty()) {
        v = dequeue();
        printf("%s ", names[v]);
        count++;
        for (i = 0; i < n; i++) {
            if (adj[v][i] == 1 && !visited[i]) {
                visited[i] = 1;
                enqueue(i);
            }
        }
    }
    printf("\nBuildings reached: %d of %d\n", count, n);
}

/* ---------- DFS (recursive) ---------- */

void dfs(int v, int *count) {
    int i;

    visited[v] = 1;
    printf("%s ", names[v]);
    (*count)++;

    for (i = 0; i < n; i++)
        if (adj[v][i] == 1 && !visited[i])
            dfs(i, count);
}

void runDFS(int start) {
    int i, count = 0;

    for (i = 0; i < n; i++)
        visited[i] = 0;

    printf("\nDFS from %s: ", names[start]);
    dfs(start, &count);
    printf("\nBuildings reached: %d of %d\n", count, n);
}

/* ---------- connectivity check ---------- */

/* Counts how many separate groups of connected buildings exist */
void checkConnectivity(void) {
    int i, comps = 0;

    for (i = 0; i < n; i++)
        visited[i] = 0;

    /* quiet DFS using an explicit stack, one pass per separate group */
    for (i = 0; i < n; i++) {
        if (!visited[i]) {
            int stack[MAX], top = -1, v, j;
            comps++;
            stack[++top] = i;
            visited[i] = 1;
            while (top >= 0) {
                v = stack[top--];
                for (j = 0; j < n; j++) {
                    if (adj[v][j] == 1 && !visited[j]) {
                        visited[j] = 1;
                        stack[++top] = j;
                    }
                }
            }
        }
    }

    if (comps == 1)
        printf("\nThe campus is fully connected: every building can be reached from any other.\n");
    else
        printf("\nThe campus is NOT fully connected: it has %d separate groups of buildings.\n", comps);
}

/* ---------- main ---------- */

int readStart(void) {
    int s;
    printf("Enter starting building number (0 to %d): ", n - 1);
    scanf("%d", &s);
    if (s < 0 || s >= n) {
        printf("Invalid building number.\n");
        return -1;
    }
    return s;
}

int main() {
    int choice, s;

    do {
        printf("\n===== CAMPUS NAVIGATION (Graph Traversal) =====\n");
        printf("1. Create campus graph\n");
        printf("2. Display adjacency matrix\n");
        printf("3. BFS traversal\n");
        printf("4. DFS traversal\n");
        printf("5. Check campus connectivity\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice >= 3 && choice <= 5 && n == 0) {
            printf("Create the graph first (option 1).\n");
            continue;
        }

        switch (choice) {
            case 1: createGraph();  break;
            case 2: showMatrix();   break;
            case 3:
                s = readStart();
                if (s != -1) bfs(s);
                break;
            case 4:
                s = readStart();
                if (s != -1) runDFS(s);
                break;
            case 5: checkConnectivity(); break;
            case 6: printf("Exiting...\n"); break;
            default: printf("Invalid choice, try again.\n");
        }
    } while (choice != 6);

    return 0;
}