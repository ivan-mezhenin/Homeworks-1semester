#pragma once

#include <stdbool.h>

#define _CRT_SECURE_NO_WARNINGS
#define POINTER_IS_NULL -17
#define MEMORY_ALLOCATION_ERROR -141
#define KEY_NOT_FOUND 242

typedef struct Node Node;

typedef struct AVLTree AVLTree;

AVLTree* createAVLTree(int* errorCode);

//return tree empty or not
bool isAVLTreeEmpty(AVLTree* tree);

//return key in tree or not
bool isKeyInAVLTree(AVLTree* tree, const char *key, int* errorCode);

// add new node in tree
void addValueInAVLTree(AVLTree* tree, const char* key, const char* value, int* errorCode);

//return value by key
const char* getValue(AVLTree* tree, const char* key, int* errorCode);

//delete value by key
void deleteValue(AVLTree* tree, const char* key, int* errorCode);

//destroy tree <3
void deleteAVLTree(AVLTree* tree);