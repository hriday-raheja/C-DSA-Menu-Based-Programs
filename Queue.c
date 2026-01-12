#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple array-based queue
// Note to self: might switch to circular queue later if I need efficiency
typedef struct {
    int *data;
    int maxSize;
    int count;
} Queue;

// Allocates memory for queue
Queue* makeQueue(int n) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (!q) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    q->maxSize = n;
    q->count = 0;
    q->data = (int*)malloc(n * sizeof(int));
    return q;
}

// free up memory
void destroyQueue(Queue* q) {
    if (q) {
        if (q->data) free(q->data);
        free(q);
    }
}

// check if full
int full(Queue* q) {
    return q->count >= q->maxSize;
}

// check if empty
int empty(Queue* q) {
    return q->count == 0;
}

// just prints all elements
void showQueue(Queue* q) {
    if (empty(q)) {
        printf("Queue is EMPTY.\n");
        return;
    }

    printf("Queue: ");
    for (int i = 0; i < q->count; i++) {
        printf("%d ", q->data[i]);
    }
    printf("\n");
}

// print size info
void sizeInfo(Queue* q) {
    printf("Current count: %d (capacity %d)\n", q->count, q->maxSize);
}

// push into queue (default at end if pos == -1)
void enqueue(Queue* q, int value, int pos, int verbose) {
    if (full(q)) {
        if (verbose) printf("Queue FULL, can't insert %d\n", value);
        return;
    }

    if (pos == -1 || pos > q->count) {
        pos = q->count; // just go to end
    }

    // shift elements to right if needed
    for (int i = q->count; i > pos; i--) {
        q->data[i] = q->data[i - 1];
    }

    q->data[pos] = value;
    q->count++;

    if (verbose) {
        printf("Inserted %d at index %d\n", value, pos);
        showQueue(q);
    }
}

// pop from queue (default from end if pos == -1)
void dequeue(Queue* q, int pos) {
    if (empty(q)) {
        printf("Queue is EMPTY, can't pop.\n");
        return;
    }

    if (pos == -1 || pos >= q->count) pos = q->count - 1;

    int val = q->data[pos];
    for (int i = pos; i < q->count - 1; i++) {
        q->data[i] = q->data[i + 1];
    }
    q->count--;

    printf("Removed %d from position %d\n", val, pos);
    showQueue(q);
}

// check first element
void peekFront(Queue* q) {
    if (empty(q)) {
        printf("Queue empty, nothing to peek.\n");
    } else {
        printf("Front element: %d\n", q->data[0]);
    }
}

int main() {
    int n;
    printf("Enter queue size: ");
    scanf("%d", &n);

    Queue* myQ = makeQueue(n);

    int initNum;
    printf("How many initial elements? ");
    scanf("%d", &initNum);

    if (initNum > n) {
        printf("Too many! Setting to max (%d)\n", n);
        initNum = n;
    }

    printf("Enter %d number(s):\n", initNum);
    for (int i = 0; i < initNum; i++) {
        int val;
        scanf("%d", &val);
        enqueue(myQ, val, -1, 0);
    }

    printf("\nInitial Queue:\n");
    showQueue(myQ);
    sizeInfo(myQ);

    int choice;
    char again[5];

    do {
        printf("\n--- MENU ---\n");
        printf("1. Push\n2. Pop\n3. Peek\n4. Count\n5. Print\n6. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                if (!full(myQ)) {
                    int val, pos;
                    printf("Enter value: ");
                    scanf("%d", &val);
                    printf("Enter index (-1 for end): ");
                    scanf("%d", &pos);
                    enqueue(myQ, val, pos, 1);
                } else {
                    printf("Queue FULL, can't push.\n");
                }
                break;
            }
            case 2: {
                if (!empty(myQ)) {
                    int pos;
                    printf("Enter index to pop (-1 for end): ");
                    scanf("%d", &pos);
                    dequeue(myQ, pos);
                } else {
                    printf("Queue EMPTY, can't pop.\n");
                }
                break;
            }
            case 3:
                peekFront(myQ);
                break;
            case 4:
                sizeInfo(myQ);
                break;
            case 5:
                showQueue(myQ);
                break;
            case 6:
                printf("Exiting...\n");
                destroyQueue(myQ);
                return 0;
            default:
                printf("Invalid option.\n");
        }

        printf("Continue? (Y/N): ");
        scanf("%s", again);

    } while (strcmp(again, "Y") == 0 || strcmp(again, "y") == 0);

    printf("Program finished.\n");
    destroyQueue(myQ);
    return 0;
}
