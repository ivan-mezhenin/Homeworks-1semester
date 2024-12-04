#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define MEMORY_ALLOCATION_ERROR -1
#define POINTER_IS_NULL -2
#define MAX_DATA_SIZE 100

typedef struct ListElement ListElement;

typedef struct List List;

List* createList(int* errorCode);

void addElement(List* list, char* value, int* errorCode);