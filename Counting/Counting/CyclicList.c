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

CyclicList* createCyclicLIst(int* errorCode) {
    CyclicList* list = calloc(1, sizeof(CyclicList));
    if (list == NULL) {
        *errorCode = ERROR_CREATING_LIST;
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
        *errorCode = ERROR_CREATING_LIST_ELEMENT;
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
    if (list == NULL) {
        *errorCode = LIST_POINTER_IS_NULL;
        return;
    }

    if (step == 1) {
        CyclicListElement* deletedElement = (*element)->next;
        (*element)->next = deletedElement->next;
        (*element) = (*element)->next;  
        free(deletedElement);
        return;
    }

    for (int i = 0; i < step - 2; ++i) {
        (*element) = (*element)->next;
    }
    CyclicListElement* currentElement = (*element)->next;
    (*element)->next = currentElement->next;
    (*element) = (*element)->next;
    free(currentElement);
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

int main(void) {
    int errorCode = 0;
    CyclicList* list = createCyclicLIst(&errorCode);
    for (int i = 1; i <= 5; ++i) {
        addElementInCyclicList(list, i, &errorCode);
    }
    printCyclicList(list, &errorCode);

    CyclicListElement* current = getElementInCyclicList(list, 0, &errorCode);
    while (list->head != list->head->next) {
        deleteElementInCyclicList(list, &current, 3, &errorCode);
        if (errorCode != 0) {
            return 0;
        }
        printCyclicList(list, &errorCode);
    }
}