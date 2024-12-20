#include "Dictionary.h"
#include "BinarySearchTreeTest.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define TESTS_FAILED -3
#define INPUT_ERROR -1488
#define MAX_VALUE_SIZE 100

void printOperations(void) {
    printf("Program has some operations:\n");
    printf("0 - Exit\n");
    printf("1 - Add the value of the specified key to the dictionary.\n");
    printf("2 - Get the value for a given key from the dictionary.\n");
    printf("3 - Check the presence of the specified key in the dictionary\n");
    printf("4 - Delete the specified key and its associated value from the dictionary\n");
    printf("\n");
}

int binarySearchTreeTask(void) {
    int errorCode = 0;
    Dictionary* dictionary = createDictionary(&errorCode);
    if (errorCode == MEMORY_ALLOCATION_ERROR) {
        printf("Memory allocation error while creating dictionary\n");
        return errorCode;
    }

    printOperations();

    printf("Enter number of operation: \n");
    int operation = 0;
    if (scanf("%d", &operation) != 1) {
        printf("Input error\n");
        deleteDictionary(dictionary);
        return INPUT_ERROR;
    }

    int key = 0;
    char* value = malloc(sizeof(char)*MAX_VALUE_SIZE);
    if (value == NULL) {
        errorCode = MEMORY_ALLOCATION_ERROR;
        printf("Memory allocation error while creating value\n");
        deleteDictionary(dictionary);
        return errorCode;
    }

    bool keyInDictionary = false;
    bool isOperationEqualZero = false;

    while (!isOperationEqualZero) {

        switch (operation) {
        case 0: {
            isOperationEqualZero = true;
            break;
        }
        case 1: {
            printf("Enter key: ");
            if (scanf("%d", &key) <= 0) {
                printf("Input error\n");
                deleteDictionary(dictionary);
                free(value);
                return INPUT_ERROR;
            }

            printf("Enter value: ");
            if (scanf("%s", value) <= 0) {
                printf("Input error\n");
                deleteDictionary(dictionary);
                free(value);
                return INPUT_ERROR;
            }

            addValueInDictionary(dictionary, key, value, &errorCode);
            if (errorCode == POINTER_IS_NULL) {
                printf("Passing a null pointer while adding value in dictionary\n");
                deleteDictionary(dictionary);
                free(value);
                return errorCode;
            }
            else if (errorCode == MEMORY_ALLOCATION_ERROR) {
                deleteDictionary(dictionary);
                free(value);
                printf("Memory allocation error while adding value in dictionary\n");
            }

            printf("Value %s was added in dictionary by key %d\n", value, key);
            break;
        }
        case 2: {
            printf("Enter key: ");
            if (scanf("%d", &key) <= 0) {
                printf("Input error\n");
                deleteDictionary(dictionary);
                free(value);
                return INPUT_ERROR;
            }

            value = getValue(dictionary, key, &errorCode);
            if (errorCode == POINTER_IS_NULL) {
                printf("Passing a null pointer while getting value from dictionary\n");
                deleteDictionary(dictionary);
                free(value);
                return errorCode;
            }
            else if (errorCode == KEY_NOT_FOUND) {
                printf("No such key in dictionary. Try again\n");
                errorCode = 0;
                break;
            }

            printf("Value by key: %s\n", value);
            break;
        }
        case 3: {
            printf("Enter key: ");
            if (scanf("%d", &key) <= 0) {
                printf("Input error\n");
                deleteDictionary(dictionary);
                free(value);
                return INPUT_ERROR;
            }

            keyInDictionary = isKeyInDictionary(dictionary, key, &errorCode);
            if (errorCode == POINTER_IS_NULL) {
                printf("Passing a null pointer while checking presence of key in dictionary\n");
                deleteDictionary(dictionary);
                free(value);
                return errorCode;
            }

            if (keyInDictionary) {
                printf("Key is in the dictionary\n");
            }
            else {
                printf("Key is not in the dictionary\n");
            }
            break;
        }
        case 4: {
            printf("Enter key: ");
            if (scanf("%d", &key) <= 0) {
                printf("Input error\n");
                deleteDictionary(dictionary);
                free(value);
                return INPUT_ERROR;
            }

            deleteValue(dictionary, key, &errorCode);
            if (errorCode == POINTER_IS_NULL) {
                printf("Passing a null pointer while removal value from dictionary\n");
                deleteDictionary(dictionary);
                free(value);
                return errorCode;
            }
            else if (errorCode == KEY_NOT_FOUND) {
                printf("No such key in dictionary. Try again\n");
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
        
        if (scanf("%d", &operation) != 1) {
            printf("Input error\n");
            deleteDictionary(dictionary);
            free(value);
            return INPUT_ERROR;
        }
    }

    free(value);
    deleteDictionary(dictionary);

    return 0;
}

int main(void) {
    if (!test()) {
        return TESTS_FAILED;
    }

    int errorCode = binarySearchTreeTask();
    return errorCode;
}