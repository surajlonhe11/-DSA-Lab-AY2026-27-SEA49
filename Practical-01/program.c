#include <stdio.h>

int main() {
    int n, i, j, k;

    printf("Enter number of rows: ");
    scanf("%d", &n);

    /* 1. Right-angle triangle with numbers */
    printf("\n1. Right-angle triangle with numbers\n");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= i; j++) {
            printf("%d ", j);
        }
        printf("\n");
    }

    /* 2. Diamond with numbers */
    printf("\n2. Diamond with numbers\n");
    /* upper half: rows 1 to n */
    for (i = 1; i <= n; i++) {
        for (k = 1; k <= n - i; k++)
            printf(" ");
        for (j = 1; j <= i; j++)
            printf("%d ", i);
        printf("\n");
    }
    /* lower half: rows n-1 down to 1 */
    for (i = n - 1; i >= 1; i--) {
        for (k = 1; k <= n - i; k++)
            printf(" ");
        for (j = 1; j <= i; j++)
            printf("%d ", i);
        printf("\n");
    }

    /* 3. Pyramid with asterisks */
    printf("\n3. Pyramid with asterisks\n");
    for (i = 1; i <= n; i++) {
        for (k = 1; k <= n - i; k++)
            printf(" ");
        for (j = 1; j <= i; j++)
            printf("* ");
        printf("\n");
    }

    /* 4. Pyramid using alphabets */
    printf("\n4. Pyramid using alphabets\n");
    for (i = 1; i <= n; i++) {
        for (k = 1; k <= 2 * (n - i); k++)
            printf(" ");
        for (j = 0; j < i; j++)          /* A up to current letter */
            printf("%c ", 'A' + j);
        for (j = i - 2; j >= 0; j--)     /* back down to A */
            printf("%c ", 'A' + j);
        printf("\n");
    }

    return 0;
}