#pragma once

typedef struct IntStackElement IntStackElement;

typedef struct IntStack IntStack;

// to create stack, returns pointer to new stack
IntStack* createIntStack(int* errorCode);

// to push a new element to the stack
void pushInt(IntStack* stack, int value, int* errorCode);

// to delete element in the head of stack 
int popInt(IntStack* stack, int* errorCode);

// to delete stack and free memory
void deleteIntStack(IntStack* stack);

// to print stack's elements
void printIntStack(IntStack* stack);

// to return value in the head of stack
int topIntStack(IntStack* stack, int* errorCode);

// return length of stack
int getStackLength(IntStack* stack);