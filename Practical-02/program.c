#include <stdio.h>
#include <string.h>

#define MAX 100
#define SUBJECTS 5

typedef struct {
    int rollNo;
    char name[50];
    char program[20];
    char course[20];
    float marks[SUBJECTS];
    float total;
    float average;
} Student;

Student s[MAX];
int count = 0;

/* ---------- helpers ---------- */

void calculate(Student *st) {
    int i;
    st->total = 0;
    for (i = 0; i < SUBJECTS; i++)
        st->total += st->marks[i];
    st->average = st->total / SUBJECTS;
}

void inputMarks(Student *st) {
    int i;
    for (i = 0; i < SUBJECTS; i++) {
        do {
            printf("  Marks of subject %d (0-100): ", i + 1);
            scanf("%f", &st->marks[i]);
            if (st->marks[i] < 0 || st->marks[i] > 100)
                printf("  Invalid marks, try again.\n");
        } while (st->marks[i] < 0 || st->marks[i] > 100);
    }
}

int searchByRoll(int roll) {
    int i;
    for (i = 0; i < count; i++)
        if (s[i].rollNo == roll)
            return i;
    return -1;
}

int searchByName(char name[]) {
    int i;
    for (i = 0; i < count; i++)
        if (strcmp(s[i].name, name) == 0)
            return i;
    return -1;
}

/* Reads one complete student record into s[count] and increments count */
void acceptStudent(void) {
    Student *st = &s[count];
    int roll;

    do {
        printf("Enter roll number: ");
        scanf("%d", &roll);
        if (searchByRoll(roll) != -1)
            printf("Roll number already exists, enter a different one.\n");
    } while (searchByRoll(roll) != -1);
    st->rollNo = roll;

    printf("Enter name: ");
    scanf(" %49[^\n]", st->name);
    printf("Enter program: ");
    scanf(" %19[^\n]", st->program);
    printf("Enter course: ");
    scanf(" %19[^\n]", st->course);
    inputMarks(st);

    calculate(st);
    count++;
}

void printRecord(Student *st) {
    int i;
    printf("%-6d %-20s %-10s %-10s", st->rollNo, st->name, st->program, st->course);
    for (i = 0; i < SUBJECTS; i++)
        printf(" %6.1f", st->marks[i]);
    printf(" %8.2f %8.2f\n", st->total, st->average);
}

void printHeader(void) {
    printf("\n%-6s %-20s %-10s %-10s %6s %6s %6s %6s %6s %8s %8s\n",
           "Roll", "Name", "Program", "Course",
           "M1", "M2", "M3", "M4", "M5", "Total", "Average");
    printf("---------------------------------------------------------------"
           "-------------------------------------\n");
}

/* ---------- operations ---------- */

/* Step 2: Insert n records */
void insertRecords(void) {
    int n, i;
    printf("How many records to add? ");
    scanf("%d", &n);

    if (n <= 0 || count + n > MAX) {
        printf("Cannot add %d records (capacity %d, currently %d).\n", n, MAX, count);
        return;
    }
    for (i = 0; i < n; i++) {
        printf("\n--- Student %d of %d ---\n", i + 1, n);
        acceptStudent();
    }
    printf("\n%d record(s) added.\n", n);
}

/* Step 3: Display all records */
void displayAll(void) {
    int i;
    if (count == 0) {
        printf("\nNo records to display.\n");
        return;
    }
    printHeader();
    for (i = 0; i < count; i++)
        printRecord(&s[i]);
}

/* Step 4: Linear search by roll number or name */
void searchRecord(void) {
    int choice, roll, pos;
    char name[50];

    printf("Search by: 1. Roll No  2. Name : ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter roll number: ");
        scanf("%d", &roll);
        pos = searchByRoll(roll);
    } else if (choice == 2) {
        printf("Enter name: ");
        scanf(" %49[^\n]", name);
        pos = searchByName(name);
    } else {
        printf("Invalid choice.\n");
        return;
    }

    if (pos == -1) {
        printf("Record not found.\n");
    } else {
        printf("Record found at position %d.\n", pos);
        printHeader();
        printRecord(&s[pos]);
    }
}

/* Step 5: Bubble sort (descending) by total or average */
void sortRecords(void) {
    int choice, i, j, comparisons, totalPasses = 0, swapped;
    float a, b;
    Student temp;

    if (count < 2) {
        printf("Not enough records to sort.\n");
        return;
    }

    printf("Sort by: 1. Total  2. Average : ");
    scanf("%d", &choice);
    if (choice != 1 && choice != 2) {
        printf("Invalid choice.\n");
        return;
    }

    for (i = 1; i <= count - 1; i++) {
        comparisons = 0;
        swapped = 0;
        for (j = 0; j < count - i; j++) {
            a = (choice == 1) ? s[j].total : s[j].average;
            b = (choice == 1) ? s[j + 1].total : s[j + 1].average;
            comparisons++;
            if (a < b) {
                temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
                swapped = 1;
            }
        }
        totalPasses++;
        printf("Pass %d: %d comparison(s)\n", i, comparisons);
        if (!swapped)
            break;   /* already sorted */
    }

    printf("Total number of passes: %d\n", totalPasses);
    printf("\nSorted records (highest %s first):", choice == 1 ? "total" : "average");
    displayAll();
}

/* Step 6: Modify an existing record */
void modifyRecord(void) {
    int roll, pos, choice;

    printf("Enter roll number to modify: ");
    scanf("%d", &roll);
    pos = searchByRoll(roll);

    if (pos == -1) {
        printf("Record not found.\n");
        return;
    }

    printf("Current record:");
    printHeader();
    printRecord(&s[pos]);

    printf("\nWhat do you want to update?\n");
    printf("1. Name\n2. Program\n3. Course\n4. Marks\nChoice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter new name: ");
            scanf(" %49[^\n]", s[pos].name);
            break;
        case 2:
            printf("Enter new program: ");
            scanf(" %19[^\n]", s[pos].program);
            break;
        case 3:
            printf("Enter new course: ");
            scanf(" %19[^\n]", s[pos].course);
            break;
        case 4:
            inputMarks(&s[pos]);
            break;
        default:
            printf("Invalid choice.\n");
            return;
    }

    calculate(&s[pos]);   /* recalculate total and average */
    printf("Record updated.\n");
    printHeader();
    printRecord(&s[pos]);
}

/* Step 7: Append a single new record */
void appendRecord(void) {
    if (count >= MAX) {
        printf("Database is full.\n");
        return;
    }
    acceptStudent();
    printf("Record appended.\n");
}

/* ---------- main ---------- */

int main() {
    int choice;

    do {
        printf("\n===== STUDENT RESULT MANAGEMENT =====\n");
        printf("1. Insert records\n");
        printf("2. Display all records\n");
        printf("3. Search record\n");
        printf("4. Sort records\n");
        printf("5. Modify record\n");
        printf("6. Append record\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: insertRecords(); break;
            case 2: displayAll();    break;
            case 3: searchRecord();  break;
            case 4: sortRecords();   break;
            case 5: modifyRecord();  break;
            case 6: appendRecord();  break;
            case 7: printf("Exiting...\n"); break;
            default: printf("Invalid choice, try again.\n");
        }
    } while (choice != 7);

    return 0;
}