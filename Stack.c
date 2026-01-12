#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *items;
    int maxSize;
    int topIndex;
} Stack;

Stack* newStack(int n) {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    if (!s) {
        printf("Memory error!\n");
        exit(1);
    }
    s->maxSize = n;
    s->items = (int*)malloc(n * sizeof(int));
    s->topIndex = -1;
    return s;
}

void destroyStack(Stack* s) {
    if (s) {
        if (s->items) free(s->items);
        free(s);
    }
}

int isFull(Stack* s) {
    return s->topIndex == (s->maxSize - 1);
}

int isEmpty(Stack* s) {
    return s->topIndex == -1;
}

void dumpStack(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack EMPTY.\n");
        return;
    }
    printf("Stack (top -> bottom): ");
    for (int i = s->topIndex; i >= 0; i--) {
        printf("%d ", s->items[i]);
    }
    printf("\n");
}

void showSize(Stack* s) {
    printf("Size: %d of %d\n", s->topIndex + 1, s->maxSize);
}

void pushItem(Stack* s, int value, int verbose) {
    if (isFull(s)) {
        if (verbose) printf("Stack FULL, can't push %d\n", value);
        return;
    }
    s->topIndex++;
    s->items[s->topIndex] = value;
    if (verbose) {
        printf("Pushed %d\n", value);
        dumpStack(s);
    }
}

void popItem(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack EMPTY, nothing to pop.\n");
        return;
    }
    int removed = s->items[s->topIndex--];
    printf("Popped %d\n", removed);
    dumpStack(s);
}

void peekItem(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack EMPTY, no peek available.\n");
    } else {
        printf("Top: %d\n", s->items[s->topIndex]);
    }
}

void reverseStack(Stack* s) {
    if (isEmpty(s)) {
        printf("Nothing to reverse, stack empty.\n");
        return;
    }
    for (int i = 0, j = s->topIndex; i < j; i++, j--) {
        int tmp = s->items[i];
        s->items[i] = s->items[j];
        s->items[j] = tmp;
    }
    printf("Stack reversed.\n");
    dumpStack(s);
}

int main() {
    int n;
    printf("Enter stack size: ");
    scanf("%d", &n);

    Stack* myStack = newStack(n);

    int init;
    printf("How many initial items? ");
    scanf("%d", &init);

    if (init > n) {
        printf("Too many, trimming to %d\n", n);
        init = n;
    }

    printf("Enter %d numbers:\n", init);
    for (int i = 0; i < init; i++) {
        int x;
        scanf("%d", &x);
        pushItem(myStack, x, 0);
    }

    printf("\nInitial stack:\n");
    dumpStack(myStack);
    showSize(myStack);

    int choice;
    char cont[10];

    do {
        printf("\n--- MENU ---\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Count\n");
        printf("5. Print\n");
        printf("6. Reverse\n");
        printf("7. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int val;
                if (!isFull(myStack)) {
                    printf("Enter value: ");
                    scanf("%d", &val);
                    pushItem(myStack, val, 1);
                } else {
                    printf("Stack FULL!\n");
                }
                break;
            }
            case 2:
                popItem(myStack);
                break;
            case 3:
                peekItem(myStack);
                break;
            case 4:
                showSize(myStack);
                break;
            case 5:
                dumpStack(myStack);
                break;
            case 6:
                reverseStack(myStack);
                break;
            case 7:
                printf("Exiting...\n");
                destroyStack(myStack);
                return 0;
            default:
                printf("Invalid choice.\n");
        }

        printf("Continue? (yes/no): ");
        scanf("%s", cont);

    } while (strcmp(cont, "yes") == 0 || strcmp(cont, "YES") == 0 || strcmp(cont, "Yes") == 0);

    printf("Program ended.\n");
    destroyStack(myStack);
    return 0;
}

