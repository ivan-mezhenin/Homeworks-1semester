#include "Dictionary.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node {
    int key;
    char* value;
    struct Node* parent;
    struct Node* leftChild;
    struct Node* rightChild;
} Node;

typedef struct Dictionary {
    Node* root;
} Dictionary;

typedef enum {
    left,
    right
} Position;

Dictionary* createDictionary(int* errorCode) {
    Dictionary* tree = calloc(1, sizeof(Dictionary));
    if (tree == NULL) {
        free(tree);
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }

    return tree;
}

bool isDictionaryEmpty(Dictionary* tree) {
    return tree->root == NULL;
}

Node* createNode(const int key, char* value, int* errorCode) {
    Node* newNode = calloc(1, sizeof(Node));
    if (newNode == NULL) {
        free(newNode);
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }

    newNode->key = key;
    newNode->value = malloc(sizeof(char) * 100);
    if (newNode->value == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }

    strcpy(newNode->value, value);
    return newNode;
}

void addChild(Node* node, const int key, const char* value, Position position, int* errorCode) {
    Node* newNode = createNode(key, value, errorCode);
    if (*errorCode != 0) {
        return;
    }

    newNode->parent = node;

    if (position == left) {
        node->leftChild = newNode;

        return;
    }
    node->rightChild = newNode;
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
            addChild(node, key, value, left, errorCode);
            return;
        }

        insertValueInDictionary(node->leftChild, key, value, errorCode);
    }
    if (key > node->key) {
        if (node->rightChild == NULL) {
            addChild(node, key, value, right, errorCode);
            return;
        }

        insertValueInDictionary(node->rightChild, key, value, errorCode);
    }
}

void addValueInDictionary(Dictionary* tree, const int key, const char* value, int* errorCode) {
    if (tree == NULL) {
        *errorCode = POINTER_IS_NULL;
        return;
    }

    if (isDictionaryEmpty(tree)) {
        Node* newRoot = createNode(key, value, errorCode);
        tree->root = newRoot;
        return;
    }

    insertValueInDictionary(tree->root, key, value, errorCode);
}

Node* getNodeByKey(Node* node, const int key) {
    if (node == NULL) {
        return NULL;
    }

    if (node->key == key) {
        return node;
    }

    if (key > node->key) {
        return getNodeByKey(node->rightChild, key);
    }

    return getNodeByKey(node->leftChild, key);
}

char* getValue(Dictionary* tree, const int key, int* errorCode) {
    if (tree == NULL) {
        *errorCode = POINTER_IS_NULL;
        return NULL;
    }

    Node* foundNode = getNodeByKey(tree->root, key);
    if (foundNode == NULL) {
        *errorCode = KEY_NOT_FOUND;
        return NULL;
    }

    return foundNode->value;
}

bool findKeyInDictionary(Node* node, const int key, int* errorCode) {
    if (node == NULL) {
        return false;
    }
    if (node->key == key) {
        return true;
    }
    if (key > node->key) {
        findKeyInDictionary(node->rightChild, key, errorCode);
    }

    findKeyInDictionary(node->leftChild, key, errorCode);
}

bool isKeyInDictionary(Dictionary* tree, const int key, int* errorCode) {
    if (tree == NULL) {
        *errorCode = POINTER_IS_NULL;
        return false;
    }

    return findKeyInDictionary(tree->root, key, errorCode);
}

Node* getReplacementNode(const Node* node, int *errorCode) {
    if (node == NULL) {
        *errorCode = POINTER_IS_NULL;
        return NULL;
    }

    Node* rightmostNodeOnTheLeft = node->leftChild;
    Node* leftmostNodeOnTheRight = node->rightChild;
    int leftLength = 1;
    int rightLength = 1;

    while (rightmostNodeOnTheLeft->rightChild != NULL) {
        rightmostNodeOnTheLeft = rightmostNodeOnTheLeft->rightChild;
        ++rightLength;
    }

    while (leftmostNodeOnTheRight->leftChild != NULL) {
        leftmostNodeOnTheRight= leftmostNodeOnTheRight->leftChild;
        ++leftLength;
    }

    return leftLength > rightLength ? rightmostNodeOnTheLeft : leftmostNodeOnTheRight;
}

void deleteNode(Node* node, int* errorCode) {
    if (node == NULL) {
        *errorCode = POINTER_IS_NULL;
        return;
    }

    if (node->leftChild != NULL && node->rightChild != NULL) {
        Node* newNode = getReplacementNode(node, errorCode);
        if (*errorCode != 0) {
            return;
        }

        node->key = newNode->key;
        strcpy(node->value, newNode->value);

        free(newNode->value);
        free(newNode);
        return;
    }

    if (node->leftChild == NULL) {
        node->rightChild->parent = node->parent;

        if (node->key < node->parent->key) {
            node->parent->leftChild = node->rightChild;
        }
        else {
            node->parent->rightChild = node->rightChild;
        }
    }
    else {
        node->leftChild->parent = node->parent;

        if (node->key < node->parent->key) {
            node->parent->leftChild = node->leftChild;
        }
        else {
            node->parent->rightChild = node->leftChild;
        }
    }
    free(node);
}

void deleteRoot(Dictionary* tree, int* errorCode){
    if (tree == NULL) {
        *errorCode = POINTER_IS_NULL;
        return;
    }

    if (tree->root->leftChild != NULL && tree->root->rightChild != NULL){
        Node* newRoot = getReplacementNode(tree->root, errorCode);
        if (*errorCode != 0) {
            return;
        }

        tree->root->key = newRoot->key;
        strcpy(tree->root->value, newRoot->value);

        free(newRoot->value);
        free(newRoot);
        return;
    }

    Node* previosRoot = tree->root;

    if (tree->root->leftChild == NULL) {
        tree->root = tree->root->rightChild;
    }
    else {
        tree->root = tree->root->leftChild;
    }

    free(previosRoot);
}

void deleteValue(Dictionary* tree, const int key, int* errorCode) {
    if (tree == NULL) {
        *errorCode = POINTER_IS_NULL;
        return;
    }

    Node* nodeToDeleted = getNodeByKey(tree->root, key);
    if (*errorCode != 0) {
        return;
    }

    if (isDictionaryEmpty(tree)) {
        return;
    }

    if (nodeToDeleted == tree->root) {
        deleteRoot(tree, errorCode);
        return;
    }

    deleteNode(nodeToDeleted, errorCode);
}

void deleteChildren(Node* node) {
    if (node == NULL) {
        return;
    }

    deleteChildren(node->leftChild);
    deleteChildren(node->rightChild);

    free(node->value);
    free(node);
}

void deleteDictionary(Dictionary* tree) {
    deleteChildren(tree->root);
    free(tree);
}

