#include <stdio.h>

#define SIZE 32   /* enough for a 32-bit integer */

int stack[SIZE];
int top = -1;

/* ---------- stack operations ---------- */

int isEmpty(void) {
    return top == -1;
}

int isFull(void) {
    return top == SIZE - 1;
}

void push(int value) {
    if (isFull()) {
        printf("Stack overflow!\n");
        return;
    }
    stack[++top] = value;
}

int pop(void) {
    if (isEmpty()) {
        printf("Stack underflow!\n");
        return -1;
    }
    return stack[top--];
}

/* Show the current contents of the stack (bottom to top) */
void displayStack(void) {
    int i;
    if (isEmpty()) {
        printf("Stack is empty.\n");
        return;
    }
    printf("Stack (bottom -> top): ");
    for (i = 0; i <= top; i++)
        printf("%d ", stack[i]);
    printf("\n");
}

/* ---------- conversion ---------- */

void decimalToBinary(int num) {
    int quotient = num, remainder;

    if (num == 0) {
        printf("Binary equivalent: 0\n");
        return;
    }

    printf("\nStep-by-step conversion:\n");
    printf("%-10s %-10s %-10s\n", "Number", "Quotient", "Remainder");
    printf("-------------------------------\n");

    /* Divide by 2 repeatedly and push each remainder */
    while (quotient > 0) {
        remainder = quotient % 2;
        printf("%-10d %-10d %-10d\n", quotient, quotient / 2, remainder);
        push(remainder);
        quotient = quotient / 2;
    }

    printf("\n");
    displayStack();

    /* Pop all remainders: LIFO order gives the correct binary number */
    printf("Binary equivalent of %d: ", num);
    while (!isEmpty())
        printf("%d", pop());
    printf("\n");
}

/* ---------- main ---------- */

int main() {
    int num;
    char again;

    do {
        printf("\nEnter a decimal number: ");
        scanf("%d", &num);

        if (num < 0) {
            printf("Please enter a non-negative number.\n");
        } else {
            top = -1;   /* start with an empty stack */
            decimalToBinary(num);
        }

        printf("\nConvert another number? (y/n): ");
        scanf(" %c", &again);
    } while (again == 'y' || again == 'Y');

    printf("Exiting...\n");
    return 0;
}