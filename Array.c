#include <stdio.h>
#include <stdlib.h>

#define LIMIT 100

void showArray(int a[], int len) {
    if (len == 0) {
        printf("Array is EMPTY.\n");
        return;
    }
    printf("Array: ");
    for (int i = 0; i < len; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main() {
    int a[LIMIT];
    int n, filled;
    char again;

    printf("Enter size of array (max %d): ", LIMIT);
    scanf("%d", &filled);
    if (filled > LIMIT) filled = LIMIT;

    printf("Enter %d values:\n", filled);
    for (n = 0; n < filled; n++) {
        scanf("%d", &a[n]);
    }

    printf("\nInitial array:\n");
    showArray(a, filled);

    n = filled;

    int choice;
    do {
        printf("\n=== MENU ===\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Update\n");
        printf("5. Display\n");
        printf("6. Max/Min\n");
        printf("7. Reverse\n");
        printf("8. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                if (n >= LIMIT) {
                    printf("Array full!\n");
                    break;
                }
                showArray(a, n);
                int val, pos;
                printf("Enter value: ");
                scanf("%d", &val);
                printf("Enter position (0-%d, or -1 for end): ", n);
                scanf("%d", &pos);
                if (pos == -1) pos = n;
                if (pos < 0 || pos > n) {
                    printf("Invalid pos.\n");
                    break;
                }
                for (int i = n; i > pos; i--) {
                    a[i] = a[i - 1];
                }
                a[pos] = val;
                n++;
                printf("Inserted.\n");
                showArray(a, n);
                break;
            }
            case 2: {
                if (n == 0) {
                    printf("Array empty.\n");
                    break;
                }
                showArray(a, n);
                int pos;
                printf("Enter position (0-%d, or -1 for end): ", n - 1);
                scanf("%d", &pos);
                if (pos == -1) pos = n - 1;
                if (pos < 0 || pos >= n) {
                    printf("Invalid pos.\n");
                    break;
                }
                for (int i = pos; i < n - 1; i++) {
                    a[i] = a[i + 1];
                }
                n--;
                printf("Deleted.\n");
                showArray(a, n);
                break;
            }
            case 3: {
                if (n == 0) {
                    printf("Array empty.\n");
                    break;
                }
                int key, found = 0;
                printf("Enter value to search: ");
                scanf("%d", &key);
                for (int i = 0; i < n; i++) {
                    if (a[i] == key) {
                        printf("Found at %d\n", i);
                        found = 1;
                        break;
                    }
                }
                if (!found) printf("Not found.\n");
                break;
            }
            case 4: {
                if (n == 0) {
                    printf("Array empty.\n");
                    break;
                }
                showArray(a, n);
                int pos, newVal;
                printf("Enter position (0-%d): ", n - 1);
                scanf("%d", &pos);
                if (pos < 0 || pos >= n) {
                    printf("Invalid pos.\n");
                    break;
                }
                printf("Enter new value: ");
                scanf("%d", &newVal);
                a[pos] = newVal;
                printf("Updated.\n");
                showArray(a, n);
                break;
            }
            case 5:
                showArray(a, n);
                break;
            case 6: {
                if (n == 0) {
                    printf("Array empty.\n");
                    break;
                }
                int maxV = a[0], minV = a[0];
                for (int i = 1; i < n; i++) {
                    if (a[i] > maxV) maxV = a[i];
                    if (a[i] < minV) minV = a[i];
                }
                printf("Max: %d, Min: %d\n", maxV, minV);
                break;
            }
            case 7: {
                if (n == 0) {
                    printf("Array empty.\n");
                    break;
                }
                for (int i = 0, j = n - 1; i < j; i++, j--) {
                    int tmp = a[i];
                    a[i] = a[j];
                    a[j] = tmp;
                }
                printf("Reversed.\n");
                showArray(a, n);
                break;
            }
            case 8:
                printf("Exit.\n");
                return 0;
            default:
                printf("Invalid choice.\n");
        }

        do {
            printf("Continue? (Y/N): ");
            scanf(" %c", &again);
            if (again == 'Y' || again == 'y' || again == 'N' || again == 'n') break;
            else printf("Enter only Y or N.\n");
        } while (1);

        if (again == 'N' || again == 'n') {
            printf("Exit.\n");
            break;
        }

    } while (1);

    return 0;
}
