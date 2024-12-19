#include "AVLTree.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node {
    int height;
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

int getHeight(Node* node) {
    return (node == NULL) ? -1 : node->height;
}

int getBalanceFactor(Node* node) {
    return getHeight(node->rightChild) - getHeight(node->leftChild);
}

void updateHeight(Node* node) {
    int lengthOfLeftSubtree = getHeight(node->leftChild);
    int lengthOfRightSubtree = getHeight(node->rightChild);

    node->height = ((lengthOfLeftSubtree > lengthOfRightSubtree) ? lengthOfLeftSubtree : lengthOfRightSubtree) + 1;
}

AVLTree* createAVLTree(int* errorCode) {
    AVLTree* tree = calloc(1, sizeof(AVLTree));
    if (tree == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }

    return tree;
}

//     a                  b    
//   /   \              /   \  
//  L     b    -->     a     R 
//      /   \        /   \     
//     C     R      L     C    

Node* rotateLeft(Node* a) {
    Node* b = a->rightChild;
    Node* c = b->leftChild;
    b->leftChild = a;
    a->rightChild = c;
    updateHeight(a);
    updateHeight(b);

    return b;
}

//        a               b       
//      /   \           /   \     
//     b     R    -->  L     a    
//   /   \                 /   \  
//  L     C               C     R 

Node* rotateRight(Node* a) {
    Node* b = a->leftChild;
    Node* c = b->rightChild;
    b->rightChild = a;
    a->leftChild = c;
    updateHeight(a);
    updateHeight(b);

    return b;
}

Node* bigRotateLeft(Node* node) {
    node->rightChild = rotateRight(node->rightChild);
    return rotateLeft(node);
}

Node* bigRotateRight(Node* node) {
    node->leftChild = rotateLeft(node->leftChild);
    return rotateRight(node);
}

Node* balance(Node* node, int* errorCode) {
    if (node == NULL) {
        *errorCode = POINTER_IS_NULL;
        return NULL;
    }

    updateHeight(node);

    if (getBalanceFactor(node) == 2) {
        if (getBalanceFactor(node->rightChild) > 0) {
            return rotateLeft(node);
        }

        return bigRotateLeft(node);
    }

    if (getBalanceFactor(node) == -2) {
        if (getBalanceFactor(node->leftChild) < 0) {
            return rotateRight(node);
        }

        return bigRotateRight(node);
    }

    return node;
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
        free(newNode);
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }

    newNode->key = malloc(strlen(key) + 1);
    if (newNode->key == NULL) {
        free(newNode);
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }

    strcpy(newNode->key, key);
    strcpy(newNode->value, value);

    return newNode;
}

Node* insertValueInDictionary(Node* node, const char* key, const char* value, int* errorCode) {
    if (node == NULL) {
        return createNode(key, value, errorCode);
    }

    if (strcmp(key, node->key) == 0) {
        free(node->value);
        node->value = malloc(strlen(value) + 1);
        if (node->value != NULL) {
            strcpy(node->value, value);
        }
    }
    else if (strcmp(key, node->key) < 0) {
        node->leftChild = insertValueInDictionary(node->leftChild, key, value, errorCode);
        node->leftChild = balance(node->leftChild, errorCode);
    }
    else {
        node->rightChild = insertValueInDictionary(node->rightChild, key, value, errorCode);
        node->rightChild = balance(node->rightChild, errorCode);
    }

    return node;
}

void addValueInAVLTree(AVLTree* tree, const char* key, const char* value, int* errorCode) {
    if (tree == NULL) {
        *errorCode = POINTER_IS_NULL;
        return;
    }

    if (isAVLTreeEmpty(tree)) {
        tree->root = createNode(key, value, errorCode);
        return;
    }

    tree->root = insertValueInDictionary(tree->root, key, value, errorCode);
    tree->root = balance(tree->root, errorCode);
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
        return "\0";
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
        updateHeight(*node);
        *node = balance(*node, errorCode);
    }
    else if (strcmp(key, (*node)->key) > 0) {
        deleteNode(&(*node)->rightChild, key, errorCode);
        updateHeight(*node);
        *node = balance(*node, errorCode);
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

        free((*node)->key);
        free((*node)->value);

        (*node)->value = malloc(strlen(temporaryNode->value) + 1);
        if ((*node)->value == NULL) {
            *errorCode = MEMORY_ALLOCATION_ERROR;
            return;
        }

        (*node)->key = malloc(strlen(temporaryNode->key) + 1);
        if ((*node)->key == NULL) {
            *errorCode = MEMORY_ALLOCATION_ERROR;
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