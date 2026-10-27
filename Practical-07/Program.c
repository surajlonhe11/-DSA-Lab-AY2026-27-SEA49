#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LEN 200

/* Each node stores one line of text */
typedef struct Node {
    char text[LINE_LEN];
    struct Node *next;
} Node;

Node *head = NULL;

/* ---------- helpers ---------- */

Node *createNode(char text[]) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (n == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strcpy(n->text, text);
    n->next = NULL;
    return n;
}

int countLines(void) {
    int c = 0;
    Node *cur = head;
    while (cur != NULL) {
        c++;
        cur = cur->next;
    }
    return c;
}

void readLine(char buf[]) {
    scanf(" %199[^\n]", buf);
}

/* ---------- insertion ---------- */

void insertFront(char text[]) {
    Node *n = createNode(text);
    n->next = head;
    head = n;
    printf("Line inserted at the front.\n");
}

void insertEnd(char text[]) {
    Node *n = createNode(text);
    Node *cur;

    if (head == NULL) {
        head = n;
    } else {
        cur = head;
        while (cur->next != NULL)
            cur = cur->next;
        cur->next = n;
    }
    printf("Line inserted at the end.\n");
}

/* Insert so that the new line becomes line number 'pos' (1-based) */
void insertAtPosition(char text[], int pos) {
    Node *n, *cur;
    int i;
    int total = countLines();

    if (pos < 1 || pos > total + 1) {
        printf("Invalid position. Valid range is 1 to %d.\n", total + 1);
        return;
    }
    if (pos == 1) {
        insertFront(text);
        return;
    }

    n = createNode(text);
    cur = head;
    for (i = 1; i < pos - 1; i++)       /* go to node (pos - 1) */
        cur = cur->next;
    n->next = cur->next;
    cur->next = n;
    printf("Line inserted at position %d.\n", pos);
}

/* ---------- deletion ---------- */

void deleteFront(void) {
    Node *temp;
    if (head == NULL) {
        printf("The text is empty. Nothing to delete.\n");
        return;
    }
    temp = head;
    head = head->next;
    printf("Deleted line: %s\n", temp->text);
    free(temp);
}

void deleteEnd(void) {
    Node *cur, *temp;

    if (head == NULL) {
        printf("The text is empty. Nothing to delete.\n");
        return;
    }
    if (head->next == NULL) {           /* only one node */
        printf("Deleted line: %s\n", head->text);
        free(head);
        head = NULL;
        return;
    }
    cur = head;
    while (cur->next->next != NULL)     /* go to second-last node */
        cur = cur->next;
    temp = cur->next;
    cur->next = NULL;
    printf("Deleted line: %s\n", temp->text);
    free(temp);
}

void deleteAtPosition(int pos) {
    Node *cur, *temp;
    int i;
    int total = countLines();

    if (head == NULL) {
        printf("The text is empty. Nothing to delete.\n");
        return;
    }
    if (pos < 1 || pos > total) {
        printf("Invalid position. Valid range is 1 to %d.\n", total);
        return;
    }
    if (pos == 1) {
        deleteFront();
        return;
    }

    cur = head;
    for (i = 1; i < pos - 1; i++)       /* go to node (pos - 1) */
        cur = cur->next;
    temp = cur->next;
    cur->next = temp->next;
    printf("Deleted line: %s\n", temp->text);
    free(temp);
}

/* ---------- display ---------- */

void display(void) {
    Node *cur = head;
    int i = 1;

    if (head == NULL) {
        printf("\nThe text is empty.\n");
        return;
    }
    printf("\n----- Text (normal order) -----\n");
    while (cur != NULL) {
        printf("%2d: %s\n", i++, cur->text);
        cur = cur->next;
    }
    printf("-------------------------------\n");
}

/* Recursive helper: print the rest of the list first, then this node */
void printReverse(Node *node, int number) {
    if (node == NULL)
        return;
    printReverse(node->next, number + 1);
    printf("%2d: %s\n", number, node->text);
}

void displayReverse(void) {
    if (head == NULL) {
        printf("\nThe text is empty.\n");
        return;
    }
    printf("\n----- Text (reverse order) -----\n");
    printReverse(head, 1);
    printf("--------------------------------\n");
    printf("(Line numbers shown are the original positions.)\n");
}

/* ---------- reverse the list itself ---------- */

void reverseList(void) {
    Node *prev = NULL, *current = head, *next = NULL;

    if (head == NULL) {
        printf("The text is empty. Nothing to reverse.\n");
        return;
    }
    while (current != NULL) {
        next = current->next;      /* store next */
        current->next = prev;      /* reverse the link */
        prev = current;            /* move prev forward */
        current = next;            /* move current forward */
    }
    head = prev;
    printf("The list has been reversed.\n");
}

/* ---------- free all memory ---------- */

void freeAll(void) {
    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

/* ---------- main ---------- */

int main() {
    int choice, pos;
    char buf[LINE_LEN];

    do {
        printf("\n===== DYNAMIC TEXT EDITOR (Singly Linked List) =====\n");
        printf(" 1. Insert line at front\n");
        printf(" 2. Insert line at end\n");
        printf(" 3. Insert line at position\n");
        printf(" 4. Delete line from front\n");
        printf(" 5. Delete line from end\n");
        printf(" 6. Delete line at position\n");
        printf(" 7. Display text\n");
        printf(" 8. Display text in reverse order\n");
        printf(" 9. Reverse the list\n");
        printf("10. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter line: ");
                readLine(buf);
                insertFront(buf);
                break;
            case 2:
                printf("Enter line: ");
                readLine(buf);
                insertEnd(buf);
                break;
            case 3:
                printf("Enter position (1 to %d): ", countLines() + 1);
                scanf("%d", &pos);
                printf("Enter line: ");
                readLine(buf);
                insertAtPosition(buf, pos);
                break;
            case 4:
                deleteFront();
                break;
            case 5:
                deleteEnd();
                break;
            case 6:
                printf("Enter position to delete: ");
                scanf("%d", &pos);
                deleteAtPosition(pos);
                break;
            case 7:
                display();
                break;
            case 8:
                displayReverse();
                break;
            case 9:
                reverseList();
                break;
            case 10:
                freeAll();
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice, try again.\n");
        }
    } while (choice != 10);

    return 0;
}