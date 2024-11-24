#pragma once

#include <stdbool.h>

#define _CRT_SECURE_NO_WARNINGS
#define MEMORY_ALLOCATION_ERROR -1
#define POINTER_IS_NULL -2

typedef struct SortedListElement SortedListElement;

typedef struct SortedList SortedList;

//return pointer of sorted list
SortedList* createSortedList(int* errorCode);

//check sorted list empty or not
bool isSortedListEmpty(SortedList* list, int* errorCode);

//add new element in sorted list
void addElementInSortedList(SortedList* list, const int value, int* errorCode);

//print all elements of sorted list
void printSortedList(SortedList* list, int* errorCode);

//delete element from sorted list
void deleteSortedListElement(SortedList* list, const int value, int* errorCode);

//delete sorted list 
void deleteSortedList(SortedList* list, int* errorCode);

//checking list sorted or not
bool isListSorted(SortedList* list, int* errorCode);