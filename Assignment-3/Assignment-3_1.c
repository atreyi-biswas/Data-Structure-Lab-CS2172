#include <stdio.h>
#include <stdlib.h>

/*
Stage-1: Initially *avoid having a count variable* that represents the number of elements in the
queue. This is for better understanding of the difficulties.
*/

typedef struct {
    int *arr;   // queue storage
    int front;  // front index
    int rear;   // rear (back) index
    int size;   // capacity
} *queue;

/*
ASSOCIATED FUNCTIONS:

1. Queue createIntegerQueue(int queueSize) - This allocates space for the queue to hold
maximum "queueSize" number of integers and initializes that space. Its return type is
"queue". The function returns NULL if creation of the queue fails.

2. int enqueueInteger(queue q, int d) - It en-queues the data d in the queue q. It returns 1 if
the operation is successful. If the operation fails (say, when queue q is full and d cannot
be en-queued), the function returns 0.

3. int dequeueInteger(queue q, int *dp) - It de-queues from the queue q and stores the
dequeued element at address dp. It returns 1 if the operation is successful. If the
operation fails (say, when queue s is empty and dequeueInteger() is attempted), the
function returns 0.

4. int freeIntegerQueue(queue q) - It frees the space allocated for queue q. It returns 1 if the
operation is successful. If the operation fails (say, q does not refer to a valid queue), the
function returns 0.

5. int isIntegerQueueFull(queue q) - It returns 1 if the queue associated with q is full. The
function returns 0 otherwise. If q does not refer to a valid queue then too the function
returns 1.

6. int isIntegerQueueEmpty(queue s) - It returns 1 if the queue associated with q is empty.
The function returns 0 otherwise. If q does not refer to a valid queue then too the function
returns 1.
*/

queue createIntegerQueue(int queueSize) {  //Create Queue
    queue q = (queue)malloc(sizeof(*q));
    if (!q) {
        return NULL;  //does not exist
    } else {
        q->arr = (int *)malloc(queueSize * sizeof(int));
        if (!q->arr) {
            free(q);
            return NULL;
        } else {
            q->size = queueSize;
            q->front = 0;
            q->rear = 0;
            return q;
        }
    }
}

//----------------------------------------------------------------------------------//

int isIntegerQueueFull(queue q) {  // Checking if queue is full
    if (!q) {
        return 0;
    } else {
        int nextRear = q->rear + 1;
        if (nextRear == q->size) {
            nextRear = 0;
        }
        if (nextRear == q->front) {
            return 1;   // full
        } else {
            return 0;   // not full
        }
    }
}

//----------------------------------------------------------------------------------//

int isIntegerQueueEmpty(queue q) {  // Checking if queue is empty
    if (!q){
        return 1;  // invalid queue so, treat as empty
    } else {
        if (q->front == q->rear) {
            return 1;  //empty
        } else {
            return 0;  //not empty
        }
    }
}

//----------------------------------------------------------------------------------//

int enqueueInteger(queue q, int d) {  
    if (!q) {
        return 0;   //q does not exist
    } else if (isIntegerQueueFull(q)) {
        return 0;   // full
    } else {
        q->rear++;
        if (q->rear == q->size) {
            q->rear = 0;
        }
        q->arr[q->rear] = d;
        return 1;
    }
}

//----------------------------------------------------------------------------------//

int dequeueInteger(queue q, int *dp) {  // Dequeue
    if (!q) {
        return 0;
    } else if (isIntegerQueueEmpty(q)) {
        return 0;   // empty
    } else {
        q->front++;
        if (q->front == q->size) {
            q->front = 0;
        }
        *dp = q->arr[q->front];
        return 1;
    }
}

//----------------------------------------------------------------------------------//

int freeIntegerQueue(queue q) {  // Free queue
    if (!q) {
        return 0;
    } else {
        free(q->arr);
        free(q);
        return 1;
    }
}

//----------------------------------------------------------------------------------//

void displayQueue(queue q) {  // Display elements in Queue
    if (!q || isIntegerQueueEmpty(q)) {
        printf("Queue is empty\n");
    } else {
        printf("Queue: ");
        int i = q->front + 1;
        if (i == q->size) {
            i = 0;
        }
        while (1) {
        printf("%d ", q->arr[i]);
        if (i == q->rear) break;
        i++;
        if (i == q->size) i = 0;
        }
        printf("\n");
        }
}


//------------------------------------Simulation-----------------------------------//


void simulateQueueFixed(queue q, int rValue) {
    int elem;
    printf("\n--- Simulation with fixed rValue = %d ---\n", rValue);
    while (!isIntegerQueueEmpty(q)) {
        if (dequeueInteger(q, &elem)) {
            elem -= rValue;
            if (elem > 0) enqueueInteger(q, elem);
        }
        displayQueue(q);
    }
    printf("Simulation finished: Queue empty.\n");
}

//----------------------------------------------------------------------------------//

void simulateQueueRandom(queue q) {
    int elem;
    static int s = 0;  // simple manual random generator
    int rValue;
    printf("\n--- Simulation with random rValue (1-9) ---\n");

    while (!isIntegerQueueEmpty(q)) {
        if (dequeueInteger(q, &elem)) {
            s++;
            rValue = s;
            if (rValue > 9) rValue = 1;  // wrap around 1–9
            elem -= rValue;
            if (elem > 0) enqueueInteger(q, elem);
            printf("Used rValue = %d\n", rValue);
        }
        displayQueue(q);
    }
    printf("Simulation finished: Queue empty.\n");
}


//=================================================================================//
//=================================================================================//


int main() {
    int choice;
    queue q = NULL;

    do {
        printf("\n-----------------------------------");
        printf("\n========= Queue Menu ==============");
        printf("\n-----------------------------------\n");
        printf("1. Space Allocation (create)\n");
        printf("2. Add Elements (enqueue)\n");
        printf("3. Remove Elements (dequeue)\n");
        printf("4. Clear Queue (free)\n");
        printf("5. Check if Queue is Full\n");
        printf("6. Check if Queue is Empty\n");
        printf("7. Display Queue\n");
        printf("------------------------------------\n");
        printf("8. Simulate Queue (fixed rValue)\n");
        printf("9. Simulate Queue (random rValue)\n");
        printf("------------------------------------\n");
        printf("0. Exit\n");
        printf("------------------------------------\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int size;
                printf("Enter queue size: ");
                scanf("%d", &size);

                if (size <= 1) {
                    printf("Invalid size! Must be > 1.\n");
                } else {
                    if (q) {          // free old queue if already created
                        freeIntegerQueue(q);
                        q = NULL;
                    }
                    q = createIntegerQueue(size); // correct function name
                    if (!q) {
                        printf("Memory allocation failed!\n");
                    } else {
                        printf("Queue initialized with size: %d\n", size);
                    }
                }
                break;
            }
            case 2: {
                if (!q) {
                    printf("Queue not created!\n");
                } else {
                    int val;
                    printf("Enter elements to enqueue (type -1 to stop):\n");
                    while (1) {
                        if (scanf("%d", &val) != 1) {
                            printf("Input error.\n");
                            break;
                        }
                        if (val == -1) {
                            break;  // don't enqueue the sentinel
                        }
                        if (!enqueueInteger(q, val)) {   // correct function name; call ONCE
                            printf("Queue FULL! Cannot insert %d\n", val);
                            break;
                        }
                    }
                }
                break;
            }
            case 3: {
                if (!q) { printf("Queue not created!\n"); break; }
                int val;
                if (dequeueInteger(q, &val))
                    printf("Dequeued: %d\n", val);
                else
                    printf("Queue EMPTY!\n");
                break;
            }
            case 4: {
                if (!q) { 
                    printf("Queue not created!\n"); break;
                } else{
                    freeIntegerQueue(q);
                    printf("Queue cleared.\n");
                    break;
                }
            }
            case 5: {
                if (!q) { printf("Queue not created!\n"); break; }
                if (isIntegerQueueFull(q))
                    printf("Queue is FULL.\n");
                else
                    printf("Queue is NOT FULL.\n");
                break;
            }
            case 6: {
                if (!q) { printf("Queue not created!\n"); break; }
                if (isIntegerQueueEmpty(q))
                    printf("Queue is EMPTY.\n");
                else
                    printf("Queue is NOT EMPTY.\n");
                break;
            }
            case 7: {
                if (!q) { 
                    printf("Queue not created!\n"); 
                    break; 
                }
                displayQueue(q);
                break;
            }
            case 8: {
                if (!q) { printf("Queue not created!\n"); break; }
                int rVal;
                printf("Enter fixed rValue for simulation: ");
                scanf("%d", &rVal);
                simulateQueueFixed(q, rVal);
                break;
            }
            case 9: {
                if (!q) { printf("Queue not created!\n"); break; }
                simulateQueueRandom(q);
                break;
            }
            case 0:
                printf("Exiting.\n");
                if (q) {
                    free(q->arr);
                    free(q);
                }
                break;
            default:
                printf("Invalid option.\n");
        }
    } while (choice != 0);

    return 0;
}


