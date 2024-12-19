#include "SortedList.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MEMORY_ALLOCATION_ERROR -1
#define POINTER_IS_NULL -2
#define INVALID_OPERATION_WITH_EMPTY_LIST -3

typedef struct SortedListElement {
    int value;
    struct SortedListElement* next;
} SortedListElement;

typedef struct SortedList {
    SortedListElement* head;
    int length;
} SortedList;

SortedList* createSortedList(int *errorCode) {
    SortedList* list = calloc(1, sizeof(SortedList));
    if (list == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }

    list->length = 0;
    list->head = NULL;

    return list;
}

bool isSortedListEmpty(SortedList* list, int* errorCode) {
    if (list == NULL) {
        *errorCode = POINTER_IS_NULL;
        return false;
    }

    return list->head == NULL;
}

void addElementInSortedList(SortedList* list, const int value, int* errorCode) {
    if (list == NULL) {
        *errorCode = POINTER_IS_NULL;
        return;
    }

    ++list->length;

    SortedListElement* newElement = calloc(1, sizeof(SortedListElement));
    if (newElement == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return;
    }

    newElement->value = value;

    if (isSortedListEmpty(list, *errorCode)) {
        list->head = newElement;
        newElement->next = NULL;
        return;
    }
    if (*errorCode != 0) {
        return;
    }

    SortedListElement* currentElement = list->head;
    if (currentElement->value >= value) {
        list->head = newElement;
        newElement->next = currentElement;
        return;
    }

    while (currentElement->next != NULL) {
        if (currentElement->next->value >= value) {
            SortedListElement* replacedElement = currentElement->next;
            currentElement->next = newElement;
            newElement->next = replacedElement;
            return;
        }

        currentElement = currentElement->next;
    }

    currentElement->next = newElement;
    return;
}

void printSortedList(SortedList* list, int* errorCode) {
    if (list == NULL) {
        *errorCode = POINTER_IS_NULL;
        return;
    }
    
    if (isSortedListEmpty(list, errorCode)) {
        printf("Sorted list is empty\n");
        return;
    }
    if (*errorCode != 0) {
        return;
    }

    SortedListElement* currentElement = list->head;
    while (currentElement != NULL) {
        printf("%d ", currentElement->value);
        currentElement = currentElement->next;
    }
    printf("\n");
}

void deleteSortedListElement(SortedList* list, const int value, int* errorCode) {
    if (list == NULL) {
        *errorCode = POINTER_IS_NULL;
        return;
    }

    if (isSortedListEmpty(list, errorCode)) {
        *errorCode = INVALID_OPERATION_WITH_EMPTY_LIST;
        return;
    }
    if (*errorCode != 0) {
        return;
    }

    --list->length;
    SortedListElement* currentElement = list->head;
    if (value == currentElement->value) {
        list->head = list->head->next;
        free(currentElement);
        return;
    }

    while (currentElement->next != NULL) {
        if (value == currentElement->next->value) {
            SortedListElement* deletedElement = currentElement->next;
            currentElement->next = deletedElement->next;
            free(deletedElement);
            return;
        }

        currentElement = currentElement->next;
    }

    printf("Value %d not in list\n", value);
}

void deleteSortedList(SortedList* list, int* errorCode) {
    if (list == NULL) {
        *errorCode = POINTER_IS_NULL;
        return;
    }

    if (isSortedListEmpty(list, errorCode)) {
        return;
    }
    if (*errorCode != 0) {
        return;
    }

    while (list->head != NULL) {
        SortedListElement* deletedElement = list->head;
        list->head = deletedElement->next;
        free(deletedElement);
    }

    free(list);
}

int getValueByIndex(SortedList* list, int index) {
    SortedListElement* current = list->head;
    
    if (index == 0) {
        return current->value;
    }

    for (int i = 0; i < index; ++i) {
        current = current->next;
    }

    return current->value;
}

int getListLength(SortedList* list) {
    return list->head == NULL ? 0 : list->length;
}