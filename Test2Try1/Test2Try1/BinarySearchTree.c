#include "BinarySearchTree.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct Node {
    int value;
    struct Node* leftChild;
    struct Node* rightChild;
} Node;

typedef struct BinarySearchTree {
    Node* root;
} BinarySearchTree;

typedef enum {
    left,
    right
} Position;

BinarySearchTree* createTree(int* errorCode) {
    BinarySearchTree* tree = calloc(1, sizeof(BinarySearchTree));
    if (tree == NULL) {
        free(tree);
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }

    return tree;
}

bool isTreeEmpty(BinarySearchTree* tree) {
    return tree->root == NULL;
}

Node* createNode(int value, int* errorCode) {
    Node* newNode = calloc(1, sizeof(Node));
    if (newNode == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }

    newNode->value = value;

    return newNode;
}

void addChild(Node* node, int value, Position position, int* errorCode) {
    Node* newNode = createNode(value, errorCode);
    if (*errorCode != 0) {
        return;
    }

    if (position == left) {
        node->leftChild = newNode;
        return;
    }

    node->rightChild = newNode;
}

void insertValueInTree(Node* node, int value, int* errorCode) {
    if (node == NULL) {
        *errorCode = POINTER_IS_NULL;
        return;
    }

    if (value == node->value) {
        return;
    }

    if (value < node->value) {
        if (node->leftChild == NULL) {
            addChild(node, value, left, errorCode);
            return;
        }

        insertValueInTree(node->leftChild, value, errorCode);
    }
    if (value > node->value) {
        if (node->rightChild == NULL) {
            addChild(node, value, right, errorCode);
            return;
        }

        insertValueInTree(node->rightChild, value, errorCode);
    }
}

void addValueInTree(BinarySearchTree* tree, int value, int* errorCode) {
    if (tree == NULL) {
        *errorCode = POINTER_IS_NULL;
        return;
    }

    if (isTreeEmpty(tree)) {
        Node* newRoot = createNode(value, errorCode);
        tree->root = newRoot;
        return;
    }

    insertValueInTree(tree->root, value, errorCode);
}

void deleteChildren(Node* node) {
    if (node != NULL) {
        deleteChildren(node->leftChild);
        deleteChildren(node->rightChild);

        free(node);
    }
}

void deleteTree(BinarySearchTree* tree) {
    if (tree != NULL) {
        deleteChildren(tree->root);
        free(tree);
    }
}

void inOrderTraversal(Node* node, int* array, int *index) {
    if (node != NULL) {
        inOrderTraversal(node->leftChild, array, index);

        array[*index] = node->value;
        ++(*index);
        
        inOrderTraversal(node->rightChild, array, index);
    }
}

void sortArray(int* array, int lenght, int* errorCode) {
    if (array == NULL) {
        *errorCode = POINTER_IS_NULL;
        return NULL;
    }

    BinarySearchTree* tree = createTree(errorCode);
    if (*errorCode != 0) {
        return NULL;
    }

    for (int i = 0; i < lenght; ++i) {
        addValueInTree(tree, array[i], errorCode);
        if (*errorCode != 0) {
            deleteTree(tree);
            return NULL;
        }
    }
    int index = 0;
    inOrderTraversal(tree->root, array, &index);
    deleteTree(tree);
}