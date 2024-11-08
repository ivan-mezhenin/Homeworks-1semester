#pragma once

// Stack's element, stores value and pointer to the next element
typedef struct CharStackElement CharStackElement;

// Stack, stores pointer to head of stack
typedef struct CharStack CharStack;

// to create stack, returns pointer to new stack
CharStack* createCharStack(void);

// to push a new element to the stack
void pushChar(CharStack* stack, char value);

// to delete element in the head of stack 
char popChar(CharStack* stack);

// to delete stack and free memory
void destroyCharStack(CharStack* stack);

// to print stack's elements
void printCharStack(CharStack* stack);

// to return value in the head of stack
char topCharStack(CharStack* stack);
