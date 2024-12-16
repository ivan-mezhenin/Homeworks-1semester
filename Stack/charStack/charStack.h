#pragma once

typedef struct CharStackElement CharStackElement;

typedef struct CharStack CharStack;

// to create stack, returns pointer to new stack
CharStack* createCharStack(int* errorCode);

// to push a new element to the stack
void pushChar(CharStack* stack, char value, int* errorCode);

// to delete element in the head of stack 
char popChar(CharStack* stack, int* errorCode);

// to delete stack and free memory
void deleteCharStack(CharStack* stack);

// to print stack's elements
void printCharStack(CharStack* stack);

// to return value in the head of stack
char topCharStack(CharStack* stack, int* errorCode);

