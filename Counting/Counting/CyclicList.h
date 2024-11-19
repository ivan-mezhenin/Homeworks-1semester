#pragma once

#include <stdbool.h>

#define ERROR_CREATING_LIST -1
#define LIST_POINTER_IS_NULL -2
#define ERROR_CREATING_LIST_ELEMENT -3

typedef struct CyclicListElement CyclicListElement;

typedef struct CyclicList CyclicList;

//return pointer on cyclic list
CyclicList* createCyclicLIst(int* errorCode);

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


