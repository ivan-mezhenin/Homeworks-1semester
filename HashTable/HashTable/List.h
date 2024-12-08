#pragma once

#include <stdbool.h>

#define _CRT_SECURE_NO_WARNINGS
#define MEMORY_ALLOCATION_ERROR -1
#define POINTER_IS_NULL -2
#define MAX_DATA_SIZE 100

typedef struct ListElement {
    char* word;
    int frequency;
    struct ListElement* next;
} ListElement;

ListElement* createListElement(char* word, int* errorCode);

void printList(ListElement** head, int* errorCode);

void addElement(ListElement** head, char* word, int* errorCode, bool* wordIsUnique);

void deleteList(ListElement* head);

int getFrequency(ListElement* node);