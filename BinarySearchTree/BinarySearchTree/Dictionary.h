#pragma once

#include <stdbool.h>

#define MEMORY_ALLOCATION_ERROR -1
#define POINTER_IS_NULL -2
#define _CRT_SECURE_NO_WARNINGS

typedef struct Node Node;

typedef struct Dictionary Dictionary;

Dictionary* createSearchTree(int* errorCode);

typedef enum Position Position;

bool isTreeEmpty(Dictionary* tree);

Node* createNode(Node* parent, const int key, const char* value, int* errorCode);

void addChild(Node* parent, const int key, const char* value, Position position, int* errorCode);

void insertValueInDictionary(Node* node, const int key, const char* value, int* errorCode);
void addValueInDictionary(Dictionary* tree, const int key, const char* value, int* errorCode);

char* get(Node* node, const int key, int* errorCode);

char* getValue(Dictionary* tree, const int key, int* errorCode);

bool findKeyInDictionary(Node* node, const int key, int* errorCode);

bool isKeyInDictionary(Dictionary* tree, const int key, int* errorCode);