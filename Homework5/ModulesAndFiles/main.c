#define _CRT_SECURE_NO_WARNINGS

#include "Qsort.h"

#include <stdio.h>
#include <stdbool.h>

#define ARRAY_LENGTH 1000
#define POINTER_IS_NULL -1
#define FILE_NOT_FOUND -2
#define READ_DATA_ERROR -3
#define TESTS_FAILED -4

void printArray(int array[], int length) {
    for (int i = 0; i < length; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int TheMostFrequentElementInTheArray(int array[], int arrayLength, int* errorCode) {
    QSort(array, 0, arrayLength - 1, errorCode);
    if (*errorCode != 0) {
        return *errorCode;
    }

    int currentElement = array[0];
    int currentElementCounter = 0;
    int mostFrequentELement = array[0];
    int mostFrequentELementCounter = 0;

    for (int i = 1; i < arrayLength; ++i) {
        if (array[i] != currentElement) {
            if (currentElementCounter > mostFrequentELementCounter) {
                mostFrequentELementCounter = currentElementCounter;
                mostFrequentELement = currentElement;
                currentElementCounter = 0;
            }
            currentElement = array[i];
        }
        else {
            ++currentElementCounter;
        }
    }

    return mostFrequentELement;
}

bool testCorrectCase1() {
    int errorCode = 0;
    int size = 15;
    int testArray[] = {1, 90, 6, 3, 6, 70, 2, 90, 15, 30, 1, 1, 6, 3, 6};
    int expectedResult = 6;

    bool passed = TheMostFrequentElementInTheArray(testArray, size, &errorCode) == expectedResult && (errorCode == 0);
    
    return passed;
}

bool testCorrectCase2() {
    int errorCode = 0;
    int size = 1;
    int testArray[] = {1};
    int expectedResult = 1;

    bool passed = TheMostFrequentElementInTheArray(testArray, size, &errorCode) == expectedResult && (errorCode == 0);
    
    return passed;
}

bool testCorrectCase3() {
    int errorCode = 0;
    int size = 10;
    int testArray[] = {1, 1, 1, 1, 1, 2, 2, 2, 2, 2};
    int expectedResult = 1;

    bool passed = TheMostFrequentElementInTheArray(testArray, size, &errorCode) == expectedResult && (errorCode == 0);

    return passed;
}

bool test(void) {

    if (!testCorrectCase1()) {
        printf("Test 1 failed\n");
        return false;
    }

    if (!testCorrectCase2()) {
        printf("Test 2 failed\n");
        return false;
    }

    if (!testCorrectCase3()) {
        printf("Test 3 failed\n");
        return false;
    }

    return true;
}

int main(void) {
    if (!test()) {
        return TESTS_FAILED;
    }

    int errorCode = 0;
    int arrayLength = 0;
    int array[ARRAY_LENGTH];

    fileReadData("data.txt", array, &arrayLength, &errorCode);
    if (errorCode == FILE_NOT_FOUND) {
        printf("File not found\n");
        return FILE_NOT_FOUND;
    }
    else if (errorCode == READ_DATA_ERROR) {
        printf("Error while reading data from file\n");
        return READ_DATA_ERROR;
    }

    int mostFrequentElement = TheMostFrequentElementInTheArray(array, arrayLength, &errorCode);
    if (errorCode == POINTER_IS_NULL) {
        printf("Pussing a null pointer\n");
        return POINTER_IS_NULL;
    }

    printf("Your array from file:\n");
    printArray(array, arrayLength);
    printf("The most Frequent ELement in Array: %d", mostFrequentElement);

    return errorCode;
}