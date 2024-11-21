#pragma once

#include <stdbool.h>

#define _CRT_SECURE_NO_WARNINGS
#define MEMORY_ALLOCATION_ERROR -1
#define POINTER_IS_NULL -2

typedef struct SortedListElement SortedListElement;

typedef struct SortedList SortedList;

SortedList* createSortedList(int* errorCode);

bool isSortedListEmpty(SortedList* list, int* errorCode);

void addElementInSortedList(SortedList* list, const int value, int* errorCode);

void printSortedList(SortedList* list, int* errorCode);

void deleteSortedListElement(SortedList* list, const int value, int* errorCode);

void deleteSortedList(SortedList* list, int* errorCode);