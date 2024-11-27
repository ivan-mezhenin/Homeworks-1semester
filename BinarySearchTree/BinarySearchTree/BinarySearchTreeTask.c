#include "Dictionary.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define TESTS_FAILED -3
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
    scanf_s("%d", &operation);

    int key = 0;
    char* value = malloc(sizeof(char)*MAX_VALUE_SIZE);

    while (operation != 0) {

        switch (operation){
        case 1: {
            printf("Enter key: ");
            scanf_s("%d", &key);
            printf("Enter value: ");
            int result = scanf("%s", value);
            addValueInDictionary(dictionary, key, value, &errorCode);
            break;
        }
        case 2: {
            printf("Enter key: ");
            scanf_s("%d", &key);
            value = getValue(dictionary, key, &errorCode);
            printf("Value by key: %s\n", value);
            break;
        }


        }

        scanf("%d", &operation);
    }

    return 0;

}


int main(void) {
    //if (!test()) {
    //    return TESTS_FAILED;
    //}

    int errorCode = binarySearchTreeTask();

}