#pragma once

// Stack's element, stores value and pointer to the next element
typedef struct IntStackElement IntStackElement;

// Stack, stores pointer to head of stack
typedef struct IntStack IntStack;

// to create stack, returns pointer to new stack
IntStack* createIntStack(void);

// to push a new element to the stack
void pushInt(IntStack* stack, int value);

// to delete element in the head of stack 
int popInt(IntStack* stack);

// to delete stack and free memory
void destroyIntStack(IntStack* stack);

// to print stack's elements
void printIntStack(IntStack* stack);
