#include "Dictionary.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define VALUE_SIZE 100

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

Dictionary* createSearchTree(int* errorCode) {
    Dictionary* tree = calloc(1, sizeof(Dictionary));
    if (tree == NULL) {
        free(tree);
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }

    return tree;
}

typedef enum {
    left,
    right
} Position;

bool isTreeEmpty(Dictionary* tree) {
    return tree->root == NULL;
}

Node* createNode(Node* parent, const int key, const char* value, int* errorCode) {
    Node* newNode = calloc(1, sizeof(Node));
    if (newNode == NULL) {
        free(newNode);
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }

    newNode->parent = parent;
    newNode->key = key;
    newNode->value = calloc(sizeof(value), sizeof(char));
    strcpy(newNode->value, value);
    return newNode;
}

void addChild(Node* parent, const int key, const char* value, Position position, int* errorCode) {
    Node* newNode = createNode(parent, key, value, errorCode);
    if (*errorCode != 0) {
        return;
    }

    if (position == left) {
        parent->leftChild = newNode;
        return;
    }
    parent->rightChild = newNode;
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

    if (isTreeEmpty(tree)) {
        Node* newRoot = calloc(1, sizeof(Node));
        if (newRoot == NULL) {
            *errorCode = MEMORY_ALLOCATION_ERROR;
            return;
        }

        newRoot->key = key;
        strcpy_s(newRoot->value, VALUE_SIZE, value);

        tree->root = newRoot;
        return;
    }

    insertValueInDictionary(tree->root, key, value, errorCode);
}

char* get(Node* node, const int key, int* errorCode) {
    if (node == NULL) {
        *errorCode = POINTER_IS_NULL;
        return NULL;
    }

    if (node->key == key) {
        return node->value;
    }

    if (node->key > key) {
        return get(node->leftChild, key, errorCode);
    }

    return get(node->rightChild, key, errorCode);
}

char* getValue(Dictionary* tree, const int key, int* errorCode) {
    if (tree == NULL) {
        *errorCode = POINTER_IS_NULL;
        return NULL;
    }

    return get(tree->root, key, errorCode);
}

bool findKeyInDictionary(Node* node, const int key, int* errorCode) {
    if (node == NULL) {
        return false;
    }
    if (node->key == key) {
        return true;
    }
    if (key > node->key) {
        return findKeyInDictionary(node->rightChild, key, errorCode);
    }
    return findKeyInDictionary(node->leftChild, key, errorCode);
}

bool isKeyInDictionary(Dictionary* tree, const int key, int* errorCode) {
    if (tree == NULL) {
        *errorCode = POINTER_IS_NULL;
        return false;
    }

    return findKeyInDictionary(tree->root, key, errorCode);
}

void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->leftChild);
        printf("%d: %s  ", root->key, root->value);
        inorderTraversal(root->rightChild);
    }
}

int main(void) {
    int errorCode = 0;
    Dictionary * tree = createSearchTree(&errorCode);
    addValueInDictionary(tree, 5, "aboba", &errorCode);
    addValueInDictionary(tree, 37, "pipipi", &errorCode);
    addValueInDictionary(tree, 44, "bambamba", &errorCode);
    addValueInDictionary(tree, 8, "tp24", &errorCode);
    addValueInDictionary(tree, 1, "andrey", &errorCode);
    addValueInDictionary(tree, 17, "vanya", &errorCode);
    inorderTraversal(tree->root);

}