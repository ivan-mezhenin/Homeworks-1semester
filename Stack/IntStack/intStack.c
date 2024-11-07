#include <stdio.h>
#include <stdlib.h>

#define STACK_IS_EMPTY 1

#include "intStack.h"

typedef struct IntStackElement {
    int value;
    struct IntStackElement* next;
} IntStackElement;

typedef struct IntStack {
    IntStackElement* head;
} IntStack;

IntStack* createIntStack() {
    IntStack* stack = (IntStack*)malloc(sizeof(IntStack));
    stack->head = NULL;
    return stack;
}

void pushInt(IntStack* stack, int value) {
    IntStackElement* element = malloc(sizeof(IntStackElement));

    if (element == NULL) {
        printf("memory allocation error for stack element\n");
    }
    else {
        element->value = value;
        element->next = stack->head;
        stack->head = element;
    }
}

int popInt(IntStack* stack) {
    if (stack->head == NULL) {
        printf("Extracting an element from an empty stack\n");
        return STACK_IS_EMPTY;
    }

    IntStackElement* tmp = stack->head;
    int popedElement = tmp->value;
    stack->head = stack->head->next;
    free(tmp);
    return popedElement;
}

void destroyIntStack(IntStack* stack) {
    free(stack);
}

void printIntStack(IntStack* stack) {
    IntStackElement* current = stack->head;

    puts("Stack: ");
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    puts("\n");
}