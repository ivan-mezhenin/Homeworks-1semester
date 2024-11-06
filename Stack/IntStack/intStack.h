#pragma once

// Stack's element, stores value and pointer to the next element
typedef struct StackElement StackElement;

// Stack, stores pointer to head of stack
typedef struct Stack Stack;

// to create stack, returns pointer to new stack
Stack* createStack(void);

// to push a new element to the stack
void push(Stack* stack, int value);

// to delete element in the head of stack 
int pop(Stack* stack);

// to delete stack and free memory
void destroyStack(Stack* stack);

// to print stack's elements
void printStack(Stack* stack);
