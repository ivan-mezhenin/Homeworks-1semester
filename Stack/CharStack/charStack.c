#include "charStack.h"

#include <stdio.h>
#include <stdlib.h>

#define STACK_IS_EMPTY 1
#define MEMORY_ERROR 2

typedef struct CharStackElement {
    char value;
    struct CharStackElement* next;
} CharStackElement;

typedef struct CharStack {
    CharStackElement* head;
} CharStack;

CharStack* createCharStack(void) {
    CharStack* stack = (CharStack*)malloc(sizeof(CharStack));

    if (stack == NULL) {
        printf("Memory allocation error for stack\n");
        return NULL;
    }

    stack->head = NULL;
    return stack;
}

void pushChar(CharStack* stack, char value) {
    CharStackElement* element = malloc(sizeof(CharStackElement));

    if (element == NULL) {
        printf("memory allocation error for stack element\n");
        return MEMORY_ERROR;
    }

    element->value = value;
    element->next = stack->head;
    stack->head = element;
}

char popChar(CharStack* stack) {
    if (stack->head == NULL) {
        printf("Extracting an element from an empty stack\n");
        return STACK_IS_EMPTY;
    }

    CharStackElement* tmp = stack->head;
    int popedElement = tmp->value;
    stack->head = stack->head->next;
    free(tmp);
    return popedElement;
}

void destroyCharStack(CharStack* stack) {
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

char topCharStack(CharStack* stack) {
    if (stack->head == NULL) {
        return '\0';
    }
    return stack->head->value;
}