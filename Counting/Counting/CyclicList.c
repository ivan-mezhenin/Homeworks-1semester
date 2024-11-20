#include "CyclicList.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct CyclicListElement {
    int value;
    struct CyclicListElement* next;
} CyclicListElement;

typedef struct CyclicList {
    CyclicListElement* head;
} CyclicList;

CyclicList* createCyclicList(int* errorCode) {
    CyclicList* list = calloc(1, sizeof(CyclicList));
    if (list == NULL) {
        *errorCode = MEMORY_ERROR;
        return NULL;
    }
    return list;
}

bool isCyclicListEmpty(CyclicList* list, int *errorCode) {
    if (list == NULL) {
        *errorCode = LIST_POINTER_IS_NULL;
        return false;
    }

    return list->head == NULL;
}


void addElementInCyclicList(CyclicList* list, const int value, int* errorCode) {
    if (list == NULL) {
        *errorCode = LIST_POINTER_IS_NULL;
        return;
    }

    CyclicListElement* newElement = calloc(1, sizeof(CyclicListElement));
    if (newElement == NULL) {
        *errorCode = MEMORY_ERROR;
        return;
    }

    newElement->value = value;

    if (isCyclicListEmpty(list, errorCode)) {
        newElement->next = newElement;
        list->head = newElement;
        return;
    }
    if (*errorCode != 0) {
        return;
    }

    CyclicListElement* lastElement = list->head;
    while (lastElement->next != list->head) {
        lastElement = lastElement->next;
    }

    lastElement->next = newElement;
    newElement->next = list->head;
}

void printCyclicList(CyclicList* cyclicList, int *errorCode){
    if (cyclicList == NULL)
    {
        *errorCode = LIST_POINTER_IS_NULL;
        return;
    }

    CyclicListElement* current = cyclicList->head;
    printf("%d ", current->value);
    current = current->next;
    while (current != cyclicList->head)
    {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
    return;
}

CyclicListElement* getElementInCyclicList(CyclicList* list, const int index, int* errorCode) {
    if (list == NULL) {
        *errorCode = LIST_POINTER_IS_NULL;
        return NULL;
    }

    CyclicListElement* currentElement = list->head;

    for (int i = 0; i < index - 1; ++i) {
        currentElement = currentElement->next;
    }

    return currentElement;
}

void deleteElementInCyclicList(CyclicList* list, CyclicListElement** element, int step, int* errorCode) {
    if (list == NULL || *element == NULL || element == NULL) {
        *errorCode = LIST_POINTER_IS_NULL;
        return;
    }

    if (step == 1) {
        CyclicListElement* deletedElement = (*element)->next;
        (*element)->next = deletedElement->next;
        if (deletedElement == list->head) {
            list->head = (*element)->next;
        }
        (*element) = (*element)->next;  
        free(deletedElement);
        return;
    }

    for (int i = 0; i < step - 2; ++i) {
        (*element) = (*element)->next;
    }
    CyclicListElement* currentElement = (*element)->next;
    (*element)->next = currentElement->next;
    if (currentElement == list->head) {
        list->head = (*element)->next;
    }
    (*element) = (*element)->next;
    free(currentElement);
}

CyclicListElement* getNextElement(CyclicList* list, CyclicListElement* element, int* errorCode) {
    if (list == NULL || element == NULL) {
        *errorCode = LIST_POINTER_IS_NULL;
        return NULL;
    }

    return element->next;
}

CyclicListElement* getHeadOfCyclicList(CyclicList* list, int* errorCode) {
    if (list == NULL) {
        *errorCode = LIST_POINTER_IS_NULL;
        return NULL;
    }

    return list->head;
}

int getElementsValue(CyclicList* list, CyclicListElement* element, int* errorCode) {
    if (list == NULL || element == NULL) {
        *errorCode = LIST_POINTER_IS_NULL;
        return LIST_POINTER_IS_NULL;
    }

    return element->value;
}

void deleteCyclicList(CyclicList* list, int *errorCode) {
    if (list == NULL) {
        *errorCode = LIST_POINTER_IS_NULL;
        return;
    }

    CyclicListElement* current = list->head;
    while (list->head != current->next) {
        CyclicListElement* deletedElement = current;
        current = current->next;
        free(deletedElement);
    }
    free(current);
    free(list);
}