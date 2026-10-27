#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    char name[50];
    char phone[15];
} Contact;

Contact contacts[MAX];
int n = 0;
int isSorted = 0;   /* 1 when the list is in alphabetical order */

/* ---------- helpers ---------- */

void addContacts(void) {
    int k, i;
    printf("How many contacts to add? ");
    scanf("%d", &k);

    if (k <= 0 || n + k > MAX) {
        printf("Cannot add %d contacts (capacity %d, currently %d).\n", k, MAX, n);
        return;
    }
    for (i = 0; i < k; i++) {
        printf("\n--- Contact %d of %d ---\n", i + 1, k);
        printf("Enter name: ");
        scanf(" %49[^\n]", contacts[n].name);
        printf("Enter phone: ");
        scanf(" %14s", contacts[n].phone);
        n++;
    }
    isSorted = 0;   /* new entries may break the order */
    printf("\n%d contact(s) added.\n", k);
}

void displayContacts(void) {
    int i;
    if (n == 0) {
        printf("\nNo contacts available.\n");
        return;
    }
    printf("\n%-5s %-30s %-15s\n", "No.", "Name", "Phone");
    printf("--------------------------------------------------\n");
    for (i = 0; i < n; i++)
        printf("%-5d %-30s %-15s\n", i + 1, contacts[i].name, contacts[i].phone);
    printf("\nList is currently %s.\n", isSorted ? "SORTED" : "NOT sorted");
}

/* Bubble sort contacts alphabetically (needed for binary search) */
void sortContacts(void) {
    int i, j, swapped;
    Contact temp;

    for (i = 0; i < n - 1; i++) {
        swapped = 0;
        for (j = 0; j < n - i - 1; j++) {
            if (strcmp(contacts[j].name, contacts[j + 1].name) > 0) {
                temp = contacts[j];
                contacts[j] = contacts[j + 1];
                contacts[j + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped)
            break;
    }
    isSorted = 1;
}

/* ---------- searching ---------- */

/* Sequential search: returns index or -1, comparisons stored in *comp */
int sequentialSearch(char key[], int *comp) {
    int i;
    *comp = 0;
    for (i = 0; i < n; i++) {
        (*comp)++;
        if (strcmp(contacts[i].name, key) == 0)
            return i;
    }
    return -1;
}

/* Binary search: list must be sorted. Returns index or -1 */
int binarySearch(char key[], int *comp) {
    int low = 0, high = n - 1, mid, result;
    *comp = 0;

    while (low <= high) {
        mid = (low + high) / 2;
        (*comp)++;
        result = strcmp(key, contacts[mid].name);

        if (result == 0)
            return mid;
        else if (result < 0)
            high = mid - 1;    /* search left half */
        else
            low = mid + 1;     /* search right half */
    }
    return -1;
}

/* Makes sure the list is sorted before a binary search */
int prepareForBinary(void) {
    if (!isSorted) {
        printf("Binary search needs a sorted list. Sorting contacts first...\n");
        sortContacts();
    }
    return 1;
}

void reportResult(char method[], int pos, int comp) {
    if (pos == -1)
        printf("%s: contact NOT found (%d comparison(s)).\n", method, comp);
    else
        printf("%s: found at position %d - %s (%s), %d comparison(s).\n",
               method, pos + 1, contacts[pos].name, contacts[pos].phone, comp);
}

void doSequential(void) {
    char key[50];
    int pos, comp;

    if (n == 0) { printf("No contacts available.\n"); return; }
    printf("Enter name to search: ");
    scanf(" %49[^\n]", key);

    pos = sequentialSearch(key, &comp);
    reportResult("Sequential search", pos, comp);
}

void doBinary(void) {
    char key[50];
    int pos, comp;

    if (n == 0) { printf("No contacts available.\n"); return; }
    prepareForBinary();
    printf("Enter name to search: ");
    scanf(" %49[^\n]", key);

    pos = binarySearch(key, &comp);
    reportResult("Binary search", pos, comp);
}

/* Run both searches on the same key and compare */
void compareSearches(void) {
    char key[50];
    int posSeq, posBin, compSeq, compBin;

    if (n == 0) { printf("No contacts available.\n"); return; }
    prepareForBinary();
    printf("Enter name to search: ");
    scanf(" %49[^\n]", key);

    posSeq = sequentialSearch(key, &compSeq);
    posBin = binarySearch(key, &compBin);

    printf("\n===== COMPARISON =====\n");
    reportResult("Sequential search", posSeq, compSeq);
    reportResult("Binary search    ", posBin, compBin);

    if (compSeq > compBin)
        printf("Binary search used %d fewer comparison(s).\n", compSeq - compBin);
    else if (compSeq < compBin)
        printf("Sequential search used %d fewer comparison(s) here.\n", compBin - compSeq);
    else
        printf("Both methods used the same number of comparisons.\n");
}

/* ---------- main ---------- */

int main() {
    int choice;

    do {
        printf("\n===== CONTACT MANAGER =====\n");
        printf("1. Add contacts\n");
        printf("2. Display contacts\n");
        printf("3. Sort contacts alphabetically\n");
        printf("4. Sequential search\n");
        printf("5. Binary search\n");
        printf("6. Compare both searches\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addContacts();      break;
            case 2: displayContacts();  break;
            case 3:
                if (n == 0) printf("No contacts to sort.\n");
                else { sortContacts(); printf("Contacts sorted.\n"); }
                break;
            case 4: doSequential();     break;
            case 5: doBinary();         break;
            case 6: compareSearches();  break;
            case 7: printf("Exiting...\n"); break;
            default: printf("Invalid choice, try again.\n");
        }
    } while (choice != 7);

    return 0;
}