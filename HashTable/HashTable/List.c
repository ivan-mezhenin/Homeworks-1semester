#include "List.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct ListElement {
    char* value;
    struct ListElement* next;
}ListElement;

typedef struct List {
    ListElement* head;
} List;

List* createList(int* errorCode) {
    List* list = calloc(1, sizeof(List));
    if (list == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }

    return list;
}

bool isListEmpty(List* list, int* errorCode) {
    if (list == NULL) {
        *errorCode = POINTER_IS_NULL;
        return false;
    }

    return list->head == NULL;
}

void printList(List* list, int* errorCode) {
    if (list == NULL) {
        *errorCode = POINTER_IS_NULL;
        return;
    }

    if (isListEmpty(list, errorCode)) {
        printf("List is empty\n");
        return;
    }

    ListElement* current = list->head;
    while (current != NULL) {
        printf("%s ", current->value);
        current = current->next;
    }
    printf("\n");
}


void addElement(List* list, char* value, int* errorCode) {
    if (list == NULL) {
        *errorCode = POINTER_IS_NULL;
        return;
    }

    ListElement* newElement = calloc(1, sizeof(ListElement));
    if (newElement == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return;
    }

    newElement->value = malloc(strlen(value) + 1);
    if (newElement->value == NULL) {
        free(newElement);
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return;
    }

    strcpy(newElement->value, value);

    if (isListEmpty(list, errorCode)) {
        list->head = newElement;
        return;
    }

    ListElement* current = list->head;
    
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newElement;
}