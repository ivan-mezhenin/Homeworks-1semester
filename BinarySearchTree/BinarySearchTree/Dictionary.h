#pragma once

#include <stdbool.h>

#define MEMORY_ALLOCATION_ERROR -1
#define POINTER_IS_NULL -2
#define _CRT_SECURE_NO_WARNINGS

typedef struct Node Node;

typedef struct Dictionary Dictionary;

//return pointer on search tree
Dictionary* createSearchTree(int* errorCode);

//return tree empty or not
bool isTreeEmpty(Dictionary* tree);

// add new node in tree
void addValueInDictionary(Dictionary* tree, const int key, const char* value, int* errorCode);

//return value by key
char* getValue(Dictionary* tree, const int key, int* errorCode);

//delete value by key
void deleteValue(Dictionary* tree, const int key, int* errorCode);

//destroy tree <3
void deleteBinaryTree(const Dictionary* const tree);