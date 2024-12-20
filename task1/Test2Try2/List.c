#include "List.h"

#include "stdlib.h"

#define MEMORY_ALLOCATION_ERROR -1
#define POINTER_IS_NULL -2

List* createList(int* errorCode) {
    List* list = calloc(1, sizeof(List));
    if (list == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }

    list->length = 0;
    return list;
}

void addElement(List* list, int value, int* errorCode) {
    if (list == NULL) {
        *errorCode = POINTER_IS_NULL;
        return;
    }

    ++list->length;

    Node* newNode = calloc(1, sizeof(Node));
    if (newNode == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return;
    }

    newNode->value = value;

    if (list->head == NULL) {
        list->head = newNode;
        return;
    }

    Node* current = list->head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = newNode;
}

void deleteList(List* list) {
    if (list->head == NULL) {
        return;
    }

    Node* current = list->head;
    Node* next = NULL;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    list = NULL;
}