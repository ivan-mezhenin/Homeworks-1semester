#pragma once

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
    int length;
} List;

// return list
List* createList(int* errorCode);

// add element in list
void addElement(List* list, int value, int* errorCode);

// clear memory of list
void deleteList(List* list);