#include "AVLTree.h"
#include "AVLTreeTest.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define TESTS_FAILED -3
#define INPUT_ERROR -1488
#define MAX_VALUE_SIZE 100

void printOperations(void) {
    printf("Program has some operations:\n");
    printf("0 - Exit\n");
    printf("1 - Add the value of the specified key to the tree.\n");
    printf("2 - Get the value for a given key from the tree.\n");
    printf("3 - Check the presence of the specified key in the tree\n");
    printf("4 - Delete the specified key and its associated value from the tree\n");
    printf("\n");
}

int AVLTreeTask(void) {
    int errorCode = 0;
    AVLTree* tree = createAVLTree(&errorCode);
    if (errorCode == MEMORY_ALLOCATION_ERROR) {
        printf("Memory allocation error while creating AVL tree\n");
        return errorCode;
    }

    printOperations();

    printf("Enter number of operation: \n");
    int operation = 0;
    if (scanf("%d", &operation) != 1) {
        printf("Input error\n");
        deleteAVLTree(tree);
        return INPUT_ERROR;
    }

    char* key = malloc(sizeof(char) * MAX_VALUE_SIZE);
    if (key == NULL) {
        errorCode = MEMORY_ALLOCATION_ERROR;
        deleteAVLTree(tree);
        printf("Memory allocation error while creating key\n");
        return errorCode;
    }

    char* value = malloc(sizeof(char) * MAX_VALUE_SIZE);
    if (value == NULL) {
        errorCode = MEMORY_ALLOCATION_ERROR;
        deleteAVLTree(tree);
        free(key);
        printf("Memory allocation error while creating value\n");
        return errorCode;
    }

    bool keyInAVLTree = false;
    bool isOperationEqualZero = false;

    while (!isOperationEqualZero) {

        switch (operation) {
        case 0: {
            isOperationEqualZero = true;
            break;
        }
        case 1: {
            printf("Enter key: ");
            if (scanf("%s", key) <= 0) {
                printf("Input error\n");
                deleteAVLTree(tree);
                free(value);
                free(key);
                return INPUT_ERROR;
            }

            printf("Enter value: ");
            if (scanf("%s", value) <= 0) {
                printf("Input error\n");
                deleteAVLTree(tree);
                free(value);
                free(key);
                return INPUT_ERROR;
            }

            addValueInAVLTree(tree, key, value, &errorCode);
            if (errorCode == POINTER_IS_NULL) {
                deleteAVLTree(tree);
                free(value);
                free(key);
                printf("Passing a null pointer while adding value in tree\n");
                return errorCode;
            }
            else if (errorCode == MEMORY_ALLOCATION_ERROR) {
                deleteAVLTree(tree);
                free(value);
                free(key);
                printf("Memory allocation error while adding value in tree\n");
                return errorCode;
            }

            printf("Value %s was added in dictionary by key %s\n", value, key);
            break;
        }
        case 2: {
            printf("Enter key: ");
            if (scanf("%s", key) <= 0) {
                printf("Input error\n");
                deleteAVLTree(tree);
                free(value);
                free(key);
                return INPUT_ERROR;
            }

            value = getValue(tree, key, &errorCode);
            if (errorCode == POINTER_IS_NULL) {
                printf("Passing a null pointer while getting value from tree\n");
                deleteAVLTree(tree);
                free(value);
                free(key);
                return errorCode;
            }
            else if (errorCode == KEY_NOT_FOUND) {
                printf("No such key in tree. Try again\n");
                errorCode = 0;
                break;
            }

            printf("Value by key: %s\n", value);
            break;
        }
        case 3: {
            printf("Enter key: ");
            if (scanf("%s", key) <= 0) {
                printf("Input error\n");
                deleteAVLTree(tree);
                free(value);
                free(key);
                return INPUT_ERROR;
            }

            keyInAVLTree = isKeyInAVLTree(tree, key, &errorCode);
            if (errorCode == POINTER_IS_NULL) {
                printf("Passing a null pointer while checking presence of key in dictionary\n");
                deleteAVLTree(tree);
                free(value);
                free(key);
                return errorCode;
            }

            if (keyInAVLTree) {
                printf("Key is in the tree\n");
            }
            else {
                printf("Key is not in the tree\n");
            }
            break;
        }
        case 4: {
            printf("Enter key: ");
            if (scanf("%s", key) <= 0) {
                printf("Input error\n");
                deleteAVLTree(tree);
                free(value);
                free(key);
                return INPUT_ERROR;
            }

            deleteValue(tree, key, &errorCode);
            if (errorCode == POINTER_IS_NULL) {
                printf("Passing a null pointer while removal value from tree\n");
                deleteAVLTree(tree);
                free(value);
                free(key);
                return errorCode;
            }
            else if (errorCode == KEY_NOT_FOUND) {
                printf("No such key in tree. Try again\n");
                deleteAVLTree(tree);
                free(value);
                free(key);
                errorCode = 0;
            }
            else {
                printf("Key and value by key were deleted\n");
            }

            break;
        }
        default: {
            printf("Incorrect operation. Try again...\n");
            break;
        }
        }

        if (isOperationEqualZero) {
            continue;
        }

        if (scanf("%d", &operation) <= 0) {
            printf("Input error\n");
            deleteAVLTree(tree);
            free(value);
            free(key);
            return INPUT_ERROR;
        }
    }

    free(value);
    free(key);
    deleteAVLTree(tree);
    return 0;
}

int main(void) {
    if (!test()) {
        return TESTS_FAILED;
    }

    int errorCode = AVLTreeTask();
    return errorCode;
}