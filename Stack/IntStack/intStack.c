#include <stdio.h>
#include <stdlib.h>

#define STACK_IS_EMPTY 1

#include "intStack.h"

typedef struct StackElement {
    int value;
    struct StackElement* next;
} StackElement;

typedef struct Stack {
    StackElement* head;
} Stack;

Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->head = NULL;
    return stack;
}

void push(Stack* stack, int value) {
    StackElement* element = malloc(sizeof(StackElement));

    if (element == NULL) {
        printf("memory allocation error for stack element\n");
    }
    else {
        element->value = value;
        element->next = stack->head;
        stack->head = element;
    }
}

int pop(Stack* stack) {
    if (stack->head == NULL) {
        printf("Extracting an element from an empty stack\n");
        return STACK_IS_EMPTY;
    }

    StackElement* tmp = stack->head;
    int popedElement = tmp->value;
    stack->head = stack->head->next;
    free(tmp);
    return popedElement;
}

void destroyStack(Stack* stack) {
    free(stack);
}

void printStack(Stack* stack) {
    StackElement* current = stack->head;

    puts("Stack: ");
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    puts("\n");
}