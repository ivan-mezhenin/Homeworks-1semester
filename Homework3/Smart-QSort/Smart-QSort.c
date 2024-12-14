#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TESTS_FAILED -1
#define MEMORY_ALLOCATION_ERROR -2
#define INPUT_ERROR -3
#define POINTER_IS_NULL -4

void printArray(int array[], int length) {
    for (int i = 0; i < length; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void fillArrayOfRandowNumbers(int* array, int length) {
    for (int i = 0; i < length; ++i) {
        array[i] = rand() % 100 + 1;
    }
}


void swapElements(int* left, int* right) {
    if (*left != *right) {
        *left ^= *right;
        *right ^= *left;
        *left ^= *right;
    }
}

void insertionSort(int *array, int left, int right, int * errorCode) {
    if (array == NULL) {
        *errorCode = POINTER_IS_NULL;
        return;
    }

    for (int i = left + 1; i <= right; ++i) {
        int numberIndex = i - 1;
        int currentNumberIndex = i;

        while (array[numberIndex] > array[currentNumberIndex]) {
            swapElements(&array[numberIndex], &array[currentNumberIndex]);
            numberIndex--;
            currentNumberIndex--;
        }
    }
}

void QSort(int *array, int left, int right, int *errorCode) {
    if (array == NULL) {
        *errorCode = POINTER_IS_NULL;
        return;
    }

    if (left >= right) {
        return;
    }

    const int middleElement = array[(left + right)/2];
    int leftPointer = left;
    int rightPointer = right;

    if ((rightPointer - left + 1) < 10) {
        insertionSort(array, left, rightPointer, errorCode);
    }
    if ((right - leftPointer + 1) < 10) {
        insertionSort(array, leftPointer, right, errorCode);
    }

    while (leftPointer <= rightPointer) {
        while (array[leftPointer] < middleElement) {
            leftPointer++;
        }
        while (array[rightPointer] > middleElement) {
            rightPointer--;
        }
        if (leftPointer <= rightPointer) {
            swapElements(&array[leftPointer], &array[rightPointer]);
            leftPointer++;
            rightPointer--;
        }
    }

    QSort(array, left, rightPointer, errorCode);
    QSort(array, leftPointer, right, errorCode);
}

bool test1() {
    int errorCode = 0;
    int testArray[] = {1500, 1, 34, 14, 12, 3, 1000, 10000, 69, 78, 31, 100, 23};
    int arraySize = sizeof(testArray) / sizeof(testArray[0]);

    QSort(testArray, 0, arraySize - 1, &errorCode);
    if (errorCode != 0) {
        return false;
    }

    int standartArray[] = {1, 3, 12, 14, 23, 31, 34, 69, 78, 100, 1000, 1500, 10000};
    int standartSize = sizeof(standartArray) / sizeof(standartArray[0]);

    if (arraySize != standartSize) {
        return false;
    }

    for (int i = 0; i < arraySize; ++i) {
        if (testArray[i] != standartArray[i]) {
            return false; 
        }
    }

    return true; 
}

bool test2() {
    int errorCode = 0;
    int arraySize = 100;
    int* testArray = malloc(arraySize * sizeof(int));
    if (testArray == NULL) {
        return false;
    }

    fillArrayOfRandowNumbers(testArray, arraySize);

    QSort(testArray, 0, arraySize - 1, &errorCode);
    if (errorCode != 0) {
        return false;
    }

    for (int i = 1; i < arraySize; ++i) {
        if (testArray[i] < testArray[i - 1]) {
            free(testArray);
            return false;
        }
    }
    return true;
}

bool test(void) {
    return test1() && test2();
}

int main(void) {
    if (!test()) {
        printf("Tests failed!!!\n");
        return TESTS_FAILED;
    }

    int errorCode = 0;
    int start = 0;
    int end = 0;
    int arrayLength = 0;

    printf("Inter the length of array: ");
    if (scanf("%d", &arrayLength) != 1) {
        printf("Input error\n");
        return INPUT_ERROR;
    }

    int *array = malloc(arrayLength * sizeof(int));
    if (array == NULL) {
        printf("Memory allocation error\n");
        return MEMORY_ALLOCATION_ERROR;
    }

    printf("Inter array:\n");
    for (int i = 0; i < arrayLength; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            printf("Input error\n");
            return INPUT_ERROR;
        }
    }

    printf("Array before sorting:\n");
    printArray(array, arrayLength);

    QSort(array, 0, arrayLength - 1, &errorCode);
    if (errorCode == POINTER_IS_NULL) {
        printf("Passing a null pointer\n");
        return POINTER_IS_NULL;
    }

    printf("Array after sorting:\n");
    printArray(array, arrayLength);

    free(array);
    return errorCode;
}