#include "Stack.h"
#include "Queue.h"

#include "stdlib.h";

#define MEMORY_ALLOCATION_ERROR -1
#define POINTER_IS_NULL -2

typedef struct Queue {
    IntStack* stack1;
    IntStack* stack2;
} Queue;

Queue* createQueue(int* errorCode) {
    Queue* queue = calloc(1, sizeof(Queue));
    if (queue == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }

    queue->stack1 = createIntStack(errorCode);
    if (*errorCode != 0) {
        free(queue);
        return NULL;
    }

    queue->stack2 = createIntStack(errorCode);
    if (*errorCode != 0) {
        free(queue->stack1);
        free(queue);
        return NULL;
    }

    return queue;
}

void enqueue(Queue* queue, int value, int* errorCode) {
    pushInt(queue->stack1, value, errorCode);
    if (*errorCode != 0) {
        return;
    }
}

int dequeue(Queue* queue, int* errorCode) {
    if (!isStackEmpty(queue->stack2)) {
        int popedElement = popInt(queue->stack2, errorCode);
        if (*errorCode != 0) {
            return *errorCode;
        }

        return popedElement;
    }

    while (!isStackEmpty(queue->stack1)) {
        pushInt(queue->stack2, popInt(queue->stack1, errorCode), errorCode);
        if (*errorCode != 0) {
            return *errorCode;
        }
    }

    int popedElement = popInt(queue->stack2, errorCode);
    if (*errorCode != 0) {
        return *errorCode;
    }

    return popedElement;
}