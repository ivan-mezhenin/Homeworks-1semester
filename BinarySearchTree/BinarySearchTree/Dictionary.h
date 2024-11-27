#pragma once

#include <stdbool.h>

#define MEMORY_ALLOCATION_ERROR -1
#define POINTER_IS_NULL -2
#define KEY_NOT_FOUND -6
#define MAX_VALUE_SIZE 100
#define _CRT_SECURE_NO_WARNINGS

typedef struct Node Node;

typedef struct Dictionary Dictionary;

//return pointer on search tree
Dictionary* createDictionary(int* errorCode);

//return tree empty or not
bool isDictionaryEmpty(Dictionary* tree);

//return key in dictionary or not
bool isKeyInDictionary(Dictionary* tree, int key, int* errorCode);

// add new node in tree
void addValueInDictionary(Dictionary* tree, int key, char* value, int* errorCode);

//return value by key
char* getValue(Dictionary* tree, int key, int* errorCode);

//delete value by key
void deleteValue(Dictionary* tree, int key, int* errorCode);

//destroy tree <3
void deleteDictionary(Dictionary* tree);