#include "SortedList.h"

#include <stdio.h>
#include <stdbool.h>

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
    scanf("%d", &operation);

    while (operation != 0) {
        int value = 0;

        if (operation == 1) {
            printf("Enter the value you want to add to the sorted list: \n");
            scanf("%d", &value);
            addElementInSortedList(list, value, &errorCode);
            if (errorCode != 0) {
                return errorCode;
            }
            printf("Value %d was added in sorted list\n", value);
        }
        else if (operation == 2) {
            printf("Enter the value you want to remove from the sorted list: \n");
            scanf("%d", &value);
            deleteSortedListElement(list, value, &errorCode);
            if (errorCode != 0) {
                return errorCode;
            }
        }
        else if (operation == 3) {
            printSortedList(list, &errorCode);
            if (errorCode != 0) {
                return errorCode;
            }
        }
        else {
            printf("The program does not have such an operation. Try again...\n");
        }

        scanf("%d", &operation);
    }

    deleteSortedList(list, &errorCode);
    if (errorCode != 0) {
        return errorCode;
    }

    return 0;
}

bool test(void) {

}

int main(void) {

    int errorCode = sortedListTaskSolve();

    if (errorCode == POINTER_IS_NULL) {
        printf("Passing a null pointer\n");
        return POINTER_IS_NULL;
    }
    else if (errorCode == MEMORY_ALLOCATION_ERROR) {
        printf("Memory allocation error\n");
        return MEMORY_ALLOCATION_ERROR;
    }

    return 0;
}