#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 50

/* Each node stores one name; left < node < right (alphabetical order) */
typedef struct Node {
    char name[NAME_LEN];
    struct Node *left;
    struct Node *right;
} Node;

Node *root = NULL;

/* ---------- helpers ---------- */

Node *createNode(char name[]) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (n == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strcpy(n->name, name);
    n->left = n->right = NULL;
    return n;
}

/* ---------- insertion (recursive) ---------- */

/* Returns the (possibly new) root of the subtree. Sets *added to 1 if inserted. */
Node *insert(Node *node, char name[], int *added) {
    int cmp;

    if (node == NULL) {                  /* found the empty spot */
        *added = 1;
        return createNode(name);
    }

    cmp = strcmp(name, node->name);
    if (cmp < 0)
        node->left = insert(node->left, name, added);
    else if (cmp > 0)
        node->right = insert(node->right, name, added);
    else
        *added = 0;                      /* duplicate: ignore */

    return node;
}

/* ---------- search (iterative) ---------- */

/* Returns 1 if found, 0 otherwise. Counts the nodes visited in *steps. */
int search(char name[], int *steps) {
    Node *cur = root;
    int cmp;

    *steps = 0;
    while (cur != NULL) {
        (*steps)++;
        cmp = strcmp(name, cur->name);
        if (cmp == 0)
            return 1;
        else if (cmp < 0)
            cur = cur->left;
        else
            cur = cur->right;
    }
    return 0;
}

/* ---------- traversals (recursive) ---------- */

void inorder(Node *node) {
    if (node == NULL)
        return;
    inorder(node->left);
    printf("%s  ", node->name);
    inorder(node->right);
}

void preorder(Node *node) {
    if (node == NULL)
        return;
    printf("%s  ", node->name);
    preorder(node->left);
    preorder(node->right);
}

void postorder(Node *node) {
    if (node == NULL)
        return;
    postorder(node->left);
    postorder(node->right);
    printf("%s  ", node->name);
}

/* ---------- extra: structure view, height, count ---------- */

/* Prints the tree sideways: right subtree on top, root on the left */
void printTree(Node *node, int level) {
    int i;
    if (node == NULL)
        return;
    printTree(node->right, level + 1);
    for (i = 0; i < level; i++)
        printf("      ");
    printf("%s\n", node->name);
    printTree(node->left, level + 1);
}

int height(Node *node) {
    int l, r;
    if (node == NULL)
        return 0;
    l = height(node->left);
    r = height(node->right);
    return 1 + (l > r ? l : r);
}

int countNodes(Node *node) {
    if (node == NULL)
        return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

/* Free every node (postorder, so children go before parents) */
void freeTree(Node *node) {
    if (node == NULL)
        return;
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

/* ---------- menu actions ---------- */

void addNames(void) {
    int k, i, added;
    char name[NAME_LEN];

    printf("How many names to add? ");
    scanf("%d", &k);
    if (k <= 0) {
        printf("Nothing to add.\n");
        return;
    }
    for (i = 0; i < k; i++) {
        printf("Enter name %d: ", i + 1);
        scanf(" %49[^\n]", name);
        root = insert(root, name, &added);
        if (added)
            printf("  '%s' added.\n", name);
        else
            printf("  '%s' already exists, not added.\n", name);
    }
}

void searchName(void) {
    char name[NAME_LEN];
    int steps;

    if (root == NULL) {
        printf("The directory is empty.\n");
        return;
    }
    printf("Enter name to search: ");
    scanf(" %49[^\n]", name);

    if (search(name, &steps))
        printf("'%s' FOUND (%d node(s) visited).\n", name, steps);
    else
        printf("'%s' NOT found (%d node(s) visited).\n", name, steps);
}

void showTraversals(void) {
    if (root == NULL) {
        printf("The directory is empty.\n");
        return;
    }
    printf("\nInorder   (sorted) : ");
    inorder(root);
    printf("\nPreorder           : ");
    preorder(root);
    printf("\nPostorder          : ");
    postorder(root);
    printf("\n");
}

void showStructure(void) {
    if (root == NULL) {
        printf("The directory is empty.\n");
        return;
    }
    printf("\nTree structure (root at left, right subtree on top):\n\n");
    printTree(root, 0);
    printf("\nNodes: %d, Height: %d\n", countNodes(root), height(root));
}

/* ---------- main ---------- */

int main() {
    int choice;

    do {
        printf("\n===== ONLINE DIRECTORY (Binary Search Tree) =====\n");
        printf("1. Add names\n");
        printf("2. Search a name\n");
        printf("3. Display traversals (inorder, preorder, postorder)\n");
        printf("4. Display tree structure\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addNames();       break;
            case 2: searchName();     break;
            case 3: showTraversals(); break;
            case 4: showStructure();  break;
            case 5:
                freeTree(root);
                root = NULL;
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice, try again.\n");
        }
    } while (choice != 5);

    return 0;
}