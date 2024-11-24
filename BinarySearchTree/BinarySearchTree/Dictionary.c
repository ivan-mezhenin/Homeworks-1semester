#include "Dictionary.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node {
    int key;
    char* value;
    struct Node* leftChild;
    struct Node* rightChild;
} Node;

typedef struct Dictionary {
    Node* root;
} Dictionary;

Dictionary* createSearchTree(int* errorCode) {
    Dictionary* tree = calloc(1, sizeof(Dictionary));
    if (tree == NULL) {
        free(tree);
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }

    return tree;
}

bool isTreeEmpty(Dictionary* tree) {
    return tree->root = NULL;
}

void insertValueInDictionary(Node* node, const int key, const char* value, int* errorCode) {
    if (node == NULL) {
        *errorCode = POINTER_IS_NULL;
        return;
    }

    if (key == node->key) {
        strcpy(node->value, value);
        return;
    }

    if (key < node->key) {
        if (node->leftChild == NULL) {
            Node* newLeftChild = calloc(1, sizeof(Node));
            if (newLeftChild == NULL) {
                *errorCode = MEMORY_ALLOCATION_ERROR;
                return;
            }

            newLeftChild->key = key;
            strcpy(newLeftChild->value, value);
            node->leftChild = newLeftChild;
            return;
        }

        insertValueInTree(node->leftChild, key, value, errorCode);
    }
    if (key > node->key) {
        if (node->rightChild == NULL) {
            Node* newRightChild = calloc(1, sizeof(Node));
            if (newRightChild == NULL) {
                *errorCode = MEMORY_ALLOCATION_ERROR;
                return;
            }

            newRightChild->key = key;
            strcpy(newRightChild->value, value);
            node->rightChild = newRightChild;
            return;
        }

        insertValueInTree(node->rightChild, key, value, errorCode);
    }
}

void addValueInDictionary(Dictionary* tree, const int key, const char* value, int* errorCode) {
    if (tree == NULL) {
        *errorCode = POINTER_IS_NULL;
        return;
    }

    if (isTreeEmpty(tree)) {
        Node* newRoot = calloc(1, sizeof(Node));
        if (newRoot == NULL) {
            *errorCode = MEMORY_ALLOCATION_ERROR;
            return;
        }
        newRoot->key = key;
        strcpy(newRoot->value, value);
        tree->root = newRoot;
        return;
    }

    insertValueInDictionary(tree->root, key, value, errorCode);
}