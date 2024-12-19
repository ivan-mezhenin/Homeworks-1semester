#pragma once

#include <stdbool.h>

typedef struct SortedListElement SortedListElement;

typedef struct SortedList SortedList;

// return pointer of sorted list
SortedList* createSortedList(int* errorCode);

// check sorted list empty or not
bool isSortedListEmpty(SortedList* list, int* errorCode);

// add new element in sorted list
void addElementInSortedList(SortedList* list, const int value, int* errorCode);

// print all elements of sorted list
void printSortedList(SortedList* list, int* errorCode);

// delete element from sorted list
void deleteSortedListElement(SortedList* list, const int value, int* errorCode);

// delete sorted list 
void deleteSortedList(SortedList* list, int* errorCode);

// return list element value by index
int getValueByIndex(SortedList* list, int index);

// return length of list
int getListLength(SortedList* list);