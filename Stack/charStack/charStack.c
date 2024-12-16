#include "charStack.h"

#include <stdio.h>
#include <stdlib.h>

#define INVALID_OPERATION_WITH_EMPTY_STACK 1
#define MEMORY_ALLOCATION_ERROR -1
#define POINTER_IS_NULL -2

typedef struct CharStackElement {
    char value;
    struct CharStackElement* next;
} CharStackElement;

typedef struct CharStack {
    CharStackElement* head;
    int length;
} CharStack;

CharStack* createCharStack(int *errorCode) {
    CharStack* stack = (CharStack*)malloc(sizeof(CharStack));
    if (stack == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }

    stack->length = 0;
    stack->head = NULL;
    return stack;
}

void pushChar(CharStack* stack, char value, int* errorCode) {
    if (stack == NULL) {
        *errorCode = POINTER_IS_NULL;
        return;
    }

    CharStackElement* element = malloc(sizeof(CharStackElement));
    if (element == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return;
    }

    element->value = value;
    element->next = stack->head;
    stack->head = element;
    ++stack->length;
}

char popChar(CharStack* stack, int* errorCode) {
    if (stack->head == NULL) {
        *errorCode = INVALID_OPERATION_WITH_EMPTY_STACK;
        return INVALID_OPERATION_WITH_EMPTY_STACK;
    }

    CharStackElement* tmp = stack->head;
    int popedElement = tmp->value;
    stack->head = stack->head->next;
    --stack->length;

    free(tmp);
    return popedElement;
}

void deleteCharStack(CharStack* stack) {
    CharStackElement* current = stack->head;
    CharStackElement* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    free(stack);
}

void printCharStack(CharStack* stack) {
    CharStackElement* current = stack->head;

    puts("Stack: ");
    while (current != NULL) {
        printf("%c ", current->value);
        current = current->next;
    }
    puts("\n");
}

char topCharStack(CharStack* stack, int* errorCode) {
    if (stack->head == NULL) {
        *errorCode = INVALID_OPERATION_WITH_EMPTY_STACK;
        return '\0';
    }

    return stack->head->value;
}