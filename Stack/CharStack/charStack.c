#include <stdio.h>
#include <stdlib.h>

#define STACK_IS_EMPTY 1

#include "charStack.h"

typedef struct CharStackElement {
    int value;
    struct CharStackElement* next;
} CharStackElement;

typedef struct CharStack {
    CharStackElement* head;
} CharStack;

CharStack* createCharStack() {
    CharStack* stack = (CharStack*)malloc(sizeof(CharStack));
    stack->head = NULL;
    return stack;
}

void pushChar(CharStack* stack, int value) {
    CharStackElement* element = malloc(sizeof(CharStackElement));

    if (element == NULL) {
        printf("memory allocation error for stack element\n");
    }
    else {
        element->value = value;
        element->next = stack->head;
        stack->head = element;
    }
}

int popChar(CharStack* stack) {
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
    free(stack);
}

void printCharStack(CharStack* stack) {
    CharStackElement* current = stack->head;

    puts("Stack: ");
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    puts("\n");
}