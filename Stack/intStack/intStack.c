#include "intStack.h"

#include <stdio.h>
#include <stdlib.h>

#define STACK_IS_EMPTY 1
#define MEMORY_ERROR 2

typedef struct IntStackElement {
    int value;
    struct IntStackElement* next;
} IntStackElement;

typedef struct IntStack {
    IntStackElement* head;
} IntStack;

IntStack* createIntStack(void) {
    IntStack* stack = (IntStack*)malloc(sizeof(IntStack));

    if (stack == NULL) {
        printf("Memory allocation error for stack\n");
        return NULL;
    }

    stack->head = NULL;
    return stack;
}

void pushInt(IntStack* stack, int value) {
    IntStackElement* element = malloc(sizeof(IntStackElement));

    if (element == NULL) {
        printf("memory allocation error for stack element\n");
        return MEMORY_ERROR;
    }

    element->value = value;
    element->next = stack->head;
    stack->head = element;
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
    IntStackElement* current = stack->head;
    IntStackElement* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(stack);
}

void printIntStack(IntStack* stack) {
    IntStackElement* current = stack->head;

    puts("Stack: ");
    while (current != NULL) {
        printf("%c ", current->value);
        current = current->next;
    }
    puts("\n");
}

char topIntStack(IntStack* stack) {
    if (stack->head == NULL) {
        return '\0';
    }
    return stack->head->value;
}
