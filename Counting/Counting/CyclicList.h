#pragma once

#include <stdbool.h>

#define LIST_POINTER_IS_NULL -2
#define MEMORY_ERROR -3

typedef struct CyclicListElement CyclicListElement;

typedef struct CyclicList CyclicList;

//return pointer on cyclic list
CyclicList* createCyclicList(int* errorCode);

//checking list is empty or not
bool isCyclicListEmpty(CyclicList* list, int* errorCode);

//add new element in the end of cyclic list
void addElementInCyclicList(CyclicList* list, const int value, int* errorCode);

//print all elements of list
void printCyclicList(CyclicList* cyclicList, int* errorCode);

//return pointer on element by index
CyclicListElement* getElementInCyclicList(CyclicList* list, const int index, int* errorCode);

//delete element by index
void deleteElementInCyclicList(CyclicList* list, CyclicListElement** element, int step, int* errorCode);

//delete cyclic list
void deleteCyclicList(CyclicList* list, int* errorCode);

//return value of list element
int getElementsValue(CyclicList* list, CyclicListElement* element, int* errorCode);

//return head of cyclic list
CyclicListElement* getHeadOfCyclicList(CyclicList* list, int* errorCode);

//return next element
CyclicListElement* getNextElement(CyclicList* list, CyclicListElement* element, int* errorCode);

