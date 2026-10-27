#include <stdio.h>

#define SIZE 5

int queue[SIZE];
int front = -1, rear = -1;

/* ---------- helpers ---------- */

int isEmpty(void) {
    return front == -1;
}

int isFull(void) {
    return front == (rear + 1) % SIZE;
}

/* ---------- operations ---------- */

/* Add a parcel at the rear */
void addParcel(int id) {
    if (isFull()) {
        printf("Queue is full! Cannot add parcel %d.\n", id);
        return;
    }

    if (isEmpty())
        front = rear = 0;
    else
        rear = (rear + 1) % SIZE;

    queue[rear] = id;
    printf("Parcel %d added to the queue.\n", id);
}

/* Remove (process) the parcel at the front */
void deleteParcel(void) {
    int id;

    if (isEmpty()) {
        printf("Queue is empty! No parcel to process.\n");
        return;
    }

    id = queue[front];

    if (front == rear)          /* only one element was present */
        front = rear = -1;
    else
        front = (front + 1) % SIZE;

    printf("Parcel %d processed and removed from the queue.\n", id);
}

/* Show all parcels from front to rear */
void displayQueue(void) {
    int i;

    if (isEmpty()) {
        printf("Queue is empty.\n");
        return;
    }

    printf("\nParcels in queue (front -> rear):\n");
    i = front;
    while (1) {
        printf("  [index %d] Parcel %d", i, queue[i]);
        if (i == front) printf("  <- front");
        if (i == rear)  printf("  <- rear");
        printf("\n");

        if (i == rear)
            break;
        i = (i + 1) % SIZE;
    }

    printf("front = %d, rear = %d\n", front, rear);
}

/* ---------- main ---------- */

int main() {
    int choice, id;

    do {
        printf("\n===== PARCEL HANDLING SYSTEM =====\n");
        printf("1. Add parcel\n");
        printf("2. Delete (process) parcel\n");
        printf("3. Display queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter parcel ID: ");
                scanf("%d", &id);
                addParcel(id);
                break;
            case 2:
                deleteParcel();
                break;
            case 3:
                displayQueue();
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice, try again.\n");
        }
    } while (choice != 4);

    return 0;
}