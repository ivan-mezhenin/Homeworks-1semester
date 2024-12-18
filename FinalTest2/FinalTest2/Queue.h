#pragma once

typedef struct Queue Queue;

// return queue
Queue* createQueue(int* errorCode);

// push value in queue
void enqueue(Queue* queue, int value, int* errorCode);

// pop value
int dequeue(Queue* queue, int* errorCode);