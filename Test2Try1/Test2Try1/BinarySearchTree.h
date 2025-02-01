#pragma once

#define MEMORY_ALLOCATION_ERROR -1
#define POINTER_IS_NULL -2
#define ELEMENT_NOT_EXIST -3

typedef struct Node Node;

typedef struct BinarySearchTree BinarySearchTree;

//return tree
BinarySearchTree* createTree(int* errorCode);

//add value in tree
void addValueInTree(BinarySearchTree* tree, int value, int* errorCode);

//remove memory of tree
void deleteTree(BinarySearchTree* tree);

//function sorts array using binary search tree
void sortArray(int* array, int lenght, int* errorCode);