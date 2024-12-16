#include "intStack.h"

#include <stdio.h>
#include <stdlib.h>

#define INVALID_OPERATION_WITH_EMPTY_STACK 1
#define MEMORY_ALLOCATION_ERROR -1
#define POINTER_IS_NULL -2

typedef struct IntStackElement {
    int value;
    struct IntStackElement* next;
} IntStackElement;

typedef struct IntStack {
    IntStackElement* head;
    int length;
} IntStack;

IntStack* createIntStack(int *errorCode) {
    IntStack* stack = (IntStack*)malloc(sizeof(IntStack));
    if (stack == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }

    stack->length = 0;
    stack->head = NULL;
    return stack;
}

void pushInt(IntStack* stack, int value, int *errorCode) {
    if (stack == NULL) {
        *errorCode = POINTER_IS_NULL;
        return;
    }

    IntStackElement* element = malloc(sizeof(IntStackElement));
    if (element == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return;
    }

    element->value = value;
    element->next = stack->head;
    stack->head = element;
    ++stack->length;
}

int popInt(IntStack* stack, int *errorCode) {
    if (stack->head == NULL) {
        *errorCode = INVALID_OPERATION_WITH_EMPTY_STACK;
        return INVALID_OPERATION_WITH_EMPTY_STACK;
    }

    IntStackElement* tmp = stack->head;
    int popedElement = tmp->value;
    stack->head = stack->head->next;
    --stack->length;

    free(tmp);
    return popedElement;
}

void deleteIntStack(IntStack* stack) {
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
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

int topIntStack(IntStack* stack, int *errorCode) {
    if (stack->head == NULL) {
        *errorCode = INVALID_OPERATION_WITH_EMPTY_STACK;
        return INVALID_OPERATION_WITH_EMPTY_STACK;
    }

    return stack->head->value;
}

int getStackLength(IntStack* stack) {
    return stack->length;
}