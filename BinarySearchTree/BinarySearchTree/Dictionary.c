#include "Dictionary.h"

#include <stdio.h>
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

Dictionary* createDictionary(int* errorCode) {
    Dictionary* tree = calloc(1, sizeof(Dictionary));
    if (tree == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }

    return tree;
}

bool isDictionaryEmpty(Dictionary* tree) {
    return tree->root == NULL;
}

Node* createNode(int key, char* value, int* errorCode) {
    Node* newNode = calloc(1, sizeof(Node));
    if (newNode == NULL) {
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

Node* insertValueInDictionary(Node* node, int key, char* value, int * errorCode) {
    if (node == NULL) {
        return createNode(key, value, errorCode);
    }

    if (key == node->key) {
        strcpy(node->value, value);
    }
    else if (key < node->key) {
        node->leftChild = insertValueInDictionary(node->leftChild, key, value, errorCode);
    }
    else {
        node->rightChild = insertValueInDictionary(node->rightChild, key, value, errorCode);
    }

    return node;
}

void addValueInDictionary(Dictionary* tree, int key, char* value, int* errorCode) {
    if (tree == NULL) {
        *errorCode = POINTER_IS_NULL;
        return;
    }

    if (isDictionaryEmpty(tree)) {
        tree->root = createNode(key, value, errorCode);
        return;
    }

    tree->root = insertValueInDictionary(tree->root, key, value, errorCode);
}

Node* getNodeByKey(Node* node, int key) {
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

char* getValue(Dictionary* tree, int key, int* errorCode) {
    if (tree == NULL) {
        *errorCode = POINTER_IS_NULL;
        return "\0";
    }

    Node* foundNode = getNodeByKey(tree->root, key);
    if (foundNode == NULL) {
        *errorCode = KEY_NOT_FOUND;
        return NULL;
    }

    return foundNode->value;
}

bool isKeyInDictionary(Dictionary* tree, int key, int* errorCode) {
    if (tree == NULL) {
        *errorCode = POINTER_IS_NULL;
        return false;
    }

    return getNodeByKey(tree->root, key, errorCode) != NULL;
}

Node* getMinValueNode(Node* node) {
    Node* currentNode = node;
    while (currentNode->leftChild != NULL) {
        currentNode = currentNode->leftChild;
    }

    return currentNode;
}

void deleteNode(Node** node, int key, int* errorCode) {
    if (*node == NULL) {
        return;
    }

    if (key < (*node)->key) {
        deleteNode(&(*node)->leftChild, key, errorCode);
    }
    else if (key > (*node)->key) {
        deleteNode(&(*node)->rightChild, key, errorCode);
    }
    else {
        if ((*node)->leftChild == NULL && (*node)->rightChild == NULL) {
            free((*node)->value);
            free(*node);
            *node = NULL;
            return;
        }

        if ((*node)->leftChild == NULL) {
            Node* temporaryNode = (*node)->rightChild;
            free((*node)->value);
            free(*node);
            *node = temporaryNode;
            return;
        }

        if ((*node)->rightChild == NULL) {
            Node* temporaryNode = (*node)->leftChild;
            free((*node)->value);
            free(*node);
            *node = temporaryNode;
            return;
        }

        Node* temporaryNode = getMinValueNode((*node)->rightChild);
        if (temporaryNode == NULL) {
            *errorCode = POINTER_IS_NULL;
            return;
        }

        free((*node)->value);

        (*node)->value = malloc(strlen(temporaryNode->value) + 1);
        if ((*node)->value == NULL) {
            *errorCode = MEMORY_ALLOCATION_ERROR;
            return;
        }

        (*node)->key = temporaryNode->key;
        strcpy((*node)->value, temporaryNode->value);

        deleteNode(&(*node)->rightChild, temporaryNode->key, errorCode);
    }
}

void deleteValue(Dictionary* tree, int key, int* errorCode) {
    if (tree == NULL) {
        *errorCode = POINTER_IS_NULL;
        return;
    }

    if (!isKeyInDictionary(tree, key, errorCode)) {
        *errorCode = KEY_NOT_FOUND;
        return;
    }

    deleteNode(&tree->root, key, errorCode);
}

void deleteTreeNodes(Node* node) {
    if (node == NULL) {
        return;
    }

    deleteTreeNodes(node->leftChild);
    deleteTreeNodes(node->rightChild);

    free(node->value);
    free(node);
}

void deleteDictionary(Dictionary* dict) {
    if (dict == NULL) {
        return;
    }

    deleteTreeNodes(dict->root);

    dict->root = NULL;
}