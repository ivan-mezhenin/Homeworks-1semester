#include "AVLTree.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node {
    int balance;
    const char* key;
    const char* value;
    struct Node* leftChild;
    struct Node* rightChild;
} Node;

typedef struct AVLTree {
    Node* root;
} AVLTree;

typedef enum {
    left,
    right
} Position;

AVLTree* createAVLTree(int* errorCode) {
    AVLTree* tree = calloc(1, sizeof(AVLTree));
    if (tree == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }

    return tree;
}

bool isAVLTreeEmpty(AVLTree* tree) {
    return tree->root == NULL;
}

Node* createNode(const char* key, const char* value, int* errorCode) {
    Node* newNode = calloc(1, sizeof(Node));
    if (newNode == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }

    newNode->value = malloc(strlen(value) + 1);
    if (newNode->value == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }

    newNode->key = malloc(strlen(key) + 1);
    if (newNode->key == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }

    strcpy(newNode->key, key);
    strcpy(newNode->value, value);

    return newNode;
}

void addChild(Node* node, const char* key, const char* value, Position position, int* errorCode) {
    Node* newNode = createNode(key, value, errorCode);
    if (*errorCode != 0) {
        return;
    }

    if (position == left) {
        node->leftChild = newNode;
        return;
    }

    node->rightChild = newNode;
}

void insertValueInAVLTree(Node* node, const char* key, const char* value, int* errorCode) {
    if (node == NULL) {
        *errorCode = POINTER_IS_NULL;
        return;
    }

    if (strcmp(key, node->key) == 0) {
        free(node->value);
        node->value = malloc(strlen(value) + 1);
        if (node->value != NULL) {
            strcpy(node->value, value);
        }
        return;
    }

    if (strcmp(key, node->key) < 0) {
        if (node->leftChild == NULL) {
            addChild(node, key, value, left, errorCode);
            return;
        }

        insertValueInAVLTree(node->leftChild, key, value, errorCode);
    }
    if (strcmp(key, node->key) > 0) {
        if (node->rightChild == NULL) {
            addChild(node, key, value, right, errorCode);
            return;
        }

        insertValueInAVLTree(node->rightChild, key, value, errorCode);
    }
}

void addValueInAVLTree(AVLTree* tree, const char* key, const char* value, int* errorCode) {
    if (tree == NULL) {
        *errorCode = POINTER_IS_NULL;
        return;
    }

    if (isAVLTreeEmpty(tree)) {
        Node* newRoot = createNode(key, value, errorCode);
        if (*errorCode != 0) {
            return;
        }

        tree->root = newRoot;
        return;
    }

    insertValueInAVLTree(tree->root, key, value, errorCode);
}


Node* getNodeByKey(Node* node, const char* key) {
    if (node == NULL) {
        return NULL;
    }

    if (strcmp(key, node->key) == 0) {
        return node;
    }

    if (strcmp(key, node->key) > 0) {
        return getNodeByKey(node->rightChild, key);
    }

    return getNodeByKey(node->leftChild, key);
}

const char* getValue(AVLTree* tree, const char* key, int* errorCode) {
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

bool findKeyInAVLTree(Node* node, const char* key, int* errorCode) {
    if (node == NULL) {
        return false;
    }

    if (strcmp(key, node->key) == 0) {
        return true;
    }

    if (strcmp(key, node->key) > 0) {
        return findKeyInAVLTree(node->rightChild, key, errorCode);
    }

    return findKeyInAVLTree(node->leftChild, key, errorCode);
}

bool isKeyInAVLTree(AVLTree* tree, const char* key, int* errorCode) {
    if (tree == NULL) {
        *errorCode = POINTER_IS_NULL;
        return false;
    }

    return findKeyInAVLTree(tree->root, key, errorCode);
}

Node* getMinValueNode(Node* node) {
    Node* currentNode = node;
    while (currentNode->leftChild != NULL) {
        currentNode = currentNode->leftChild;
    }
    
    return currentNode;
}

void deleteNode(Node** node, const char * key, int* errorCode) {
    if (*node == NULL) {
        return;
    }

    if (strcmp(key, (*node)->key) < 0) {
        deleteNode(&(*node)->leftChild, key, errorCode);
    }
    else if (strcmp(key, (*node)->key) > 0) {
        deleteNode(&(*node)->rightChild, key, errorCode);
    }

    else {
        if ((*node)->leftChild == NULL && (*node)->rightChild == NULL) {
            free((*node)->key);
            free((*node)->value);
            free(*node);
            *node = NULL;
            return;
        }

        if ((*node)->leftChild == NULL) {
            Node* temporaryNode = (*node)->rightChild;
            free((*node)->key);
            free((*node)->value);
            free(*node);
            *node = temporaryNode;
            return;
        }

        if ((*node)->rightChild == NULL) {
            Node* temporaryNode = (*node)->leftChild;
            free((*node)->key);
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

        strcpy((*node)->key, temporaryNode->key);
        strcpy((*node)->value, temporaryNode->value);
        deleteNode(&(*node)->rightChild, temporaryNode->key, errorCode);
    }
}


void deleteValue(AVLTree* tree, const char * key, int* errorCode) {
    if (tree == NULL) {
        *errorCode = POINTER_IS_NULL;
        return;
    }
    if (!isKeyInAVLTree(tree, key, errorCode)) {
        *errorCode = KEY_NOT_FOUND;
        return;
    }

    deleteNode(&tree->root, key, errorCode);
}

int main(void) {
    int errorCode = 0;
    AVLTree* tree = createAVLTree(&errorCode);
    char key1[] = "abcd", key2[] = "bbcd";
    char val1[] = "ivan", val2[] = "Nikita";

    addValueInAVLTree(tree, key1, val1, &errorCode);
    addValueInAVLTree(tree, key2, val2, &errorCode);
    deleteValue(tree, key2, &errorCode);
    printf("%s", tree->root->value);


}


void deleteChildren(Node* node) {
    if (node != NULL) {
        deleteChildren(node->leftChild);
        deleteChildren(node->rightChild);

        if (node->value != NULL) {
            free(node->value);
        }

        if (node->key != NULL) {
            free(node->key);
        }

        free(node);
    }
}

void deleteAVLTree(AVLTree* tree) {
    if (tree != NULL) {
        deleteChildren(tree->root);
        free(tree);
    }
}