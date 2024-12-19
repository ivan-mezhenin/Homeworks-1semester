#define _CRT_SECURE_NO_WARNINGS

#include "SortedList.h"
#include "SortedListTaskTests.h"

#include <stdio.h>

#define TESTS_FAILED -4
#define MEMORY_ALLOCATION_ERROR -1
#define POINTER_IS_NULL -2
#define INVALID_OPERATION_WITH_EMPTY_LIST -3
#define INPUT_ERROR -5

void printOperations(void) {
    printf("Programm has some operations:\n");
    printf("0 - Exit\n");
    printf("1 - add a value in sorted list\n");
    printf("2 - remove a value from sorted list\n");
    printf("3 - print the sorted list\n\n");
}

int sortedListTaskSolve(void) {
    int errorCode = 0;
    SortedList* list = createSortedList(&errorCode);
    if (errorCode == MEMORY_ALLOCATION_ERROR) {
        printf("Memory allocation error\n");
        return MEMORY_ALLOCATION_ERROR;
    }

    printOperations();

    printf("Enter number of operation: \n");
    int operation = 0;
    if (scanf("%d", &operation) != 1) {
        deleteSortedList(list, &errorCode);
        return INPUT_ERROR;
    }

    while (operation != 0) {
        int value = 0;

        switch (operation) {
            case 1: {
                printf("Enter the value you want to add to the sorted list: \n");
                if (scanf("%d", &value) != 1) {
                    deleteSortedList(list, &errorCode);
                    return INPUT_ERROR;
                }

                addElementInSortedList(list, value, &errorCode);
                if (errorCode != 0) {
                    deleteSortedList(list, &errorCode);
                    return errorCode;
                }
                printf("Value %d was added in sorted list\n", value);

                break;
            }

            case 2: {
                printf("Enter the value you want to remove from the sorted list: \n");
                if (scanf("%d", &value) != 1) {
                    deleteSortedList(list, &errorCode);
                    return INPUT_ERROR;
                }

                deleteSortedListElement(list, value, &errorCode);
                if (errorCode != 0) {
                    deleteSortedList(list, &errorCode);
                    return errorCode;
                }
                
                break;
            }
            case 3: {
                printSortedList(list, &errorCode);
                if (errorCode != 0) {
                    deleteSortedList(list, &errorCode);
                    return errorCode;
                }

                break;
            }
            default: {
                printf("The program does not have such an operation. Try again...\n");
                break;
            }
        }

        if (scanf("%d", &operation) != 1) {
            deleteSortedList(list, &errorCode);
            return INPUT_ERROR;
        }
    }

    deleteSortedList(list, &errorCode);
    if (errorCode != 0) {
        return errorCode;
    }

    return 0;
}

int main(void) {
    if (!test()) {
        return TESTS_FAILED;
    }

    int errorCode = sortedListTaskSolve();

    if (errorCode == POINTER_IS_NULL) {
        printf("Passing a null pointer\n");
    }
    else if (errorCode == MEMORY_ALLOCATION_ERROR) {
        printf("Memory allocation error\n");
    }
    else if (errorCode == INVALID_OPERATION_WITH_EMPTY_LIST) {
        printf("Invalid operation with empty list\n");
    }
    else if (errorCode == INPUT_ERROR) {
        printf("Input error\n");
    }

    return errorCode;
}