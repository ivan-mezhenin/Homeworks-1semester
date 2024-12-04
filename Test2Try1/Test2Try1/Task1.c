#include "BinarySearchTree.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define TESTS_FAILED -20

void fillingArrayOfRandowNumbers(int *array, int length) {
    for (int i = 0; i < length; ++i) {
        array[i] = rand() % 100 + 1;
    }
}

void arrayOutput(int* array, int length) {
    for (int i = 0; i < length; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void swapElements(int* left, int* right) {
    if (*left != *right) {
        *left ^= *right;
        *right ^= *left;
        *left ^= *right;
    }
}

void bubbleSort(int* array, int length) {
    for (int i = 0; i < length - 1; ++i) {
        for (int j = 0; j < length - 1 - i; ++j) {
            if (array[j] > array[j + 1]) {
                swapElements(&array[j], &array[j + 1]);
            }
        }
    }
}

bool test1(void) {
    int errorCode = 0;
    int n = 8;
    int array[8] = {9, 7, 6, 5, 4, 3, 2, 1};
    int sortedArray[8] = {1, 2, 3, 4, 5, 6, 7, 9};
    sortArray(array, n, &errorCode);
    if (errorCode != 0) {
        return false;
    }
    for (int i = 0; i < n; ++i) {
        if (array[i] != sortedArray[i]) {
            return false;
        }
    }
    return true;
}

bool test2(void) {
    int errorCode = 0;
    int n = 5;
    int array[5] = {245, 7, 5, 199, 3};
    int* sortedArray = calloc(n, sizeof(int));
    if (array == NULL || sortedArray == NULL) {
        return false;
    }

    for (int i = 0; i < n; ++i) {
        sortedArray[i] = array[i];
    }

    sortArray(array, n, &errorCode);
    if (errorCode != 0) {
        return false;
    }

    bubbleSort(sortedArray, n);

    for (int i = 0; i < n; ++i) {
        if (array[i] != sortedArray[i]) {
            free(sortedArray);
            free(array);
            return false;
        }
    }

    free(sortedArray);

    return true;
}

bool test(void) {
    return test1() && test2();
}

int main(void) {
    if (!test()) {
        printf("Tests failed\n");
        return TESTS_FAILED;
    }

    int errorCode = 0;
    int n = 13;
    int array[20] = { 100, 3, 15, 78, 141, 1431, 1, 431, 14, 54, 11, 17, 90, 5, 14351, 144, 13, 56, 0, 34 };

    printf("Array before sorting: \n");
    arrayOutput(array, n);

    sortArray(array, n, &errorCode);
    if (errorCode == MEMORY_ALLOCATION_ERROR) {
        printf("Memory allocation error\n");
        return MEMORY_ALLOCATION_ERROR;
    }
    else if (errorCode == POINTER_IS_NULL) {
        printf("Puting null pointer\n");
        return POINTER_IS_NULL;
    }

    printf("Array after sorting: \n");
    arrayOutput(array, n);
    
    return errorCode;
}