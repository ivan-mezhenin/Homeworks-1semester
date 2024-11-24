#include "SortedList.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct SortedListElement {
    int value;
    struct SortedListElement* next;
} SortedListElement;

typedef struct SortedList {
    SortedListElement* head;
} SortedList;

SortedList* createSortedList(int *errorCode) {
    SortedList* list = calloc(1, sizeof(list));
    if (list == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }

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

    if (isSortedListEmpty(list, *errorCode)) {
        SortedListElement* newElement = calloc(1, sizeof(SortedListElement));
        if (newElement == NULL) {
            *errorCode = MEMORY_ALLOCATION_ERROR;
            return;
        }
        list->head = newElement;
        newElement->value = value;
        newElement->next = NULL;
        return;
    }
    if (*errorCode != 0) {
        return;
    }

    SortedListElement* newElement = calloc(1, sizeof(SortedListElement));
    if (newElement == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return;
    }
    newElement->value = value;

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
        printf("List is empty\n");
        return;
    }
    if (*errorCode != 0) {
        return;
    }

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

bool isListSorted(SortedList* list, int* errorCode) {
    if (list == NULL) {
        *errorCode = POINTER_IS_NULL;
        return;
    }

    SortedListElement* current = list->head;
    while (current->next != NULL) {
        if (current->value > current->next->value) {
            return false;
        }
        current = current->next;
    }

    return true;
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

    while (!isSortedListEmpty(list, errorCode)) {
        SortedListElement* deletedElement = list->head;
        list->head = list->head->next;
        free(deletedElement);
    }

    free(list);
}