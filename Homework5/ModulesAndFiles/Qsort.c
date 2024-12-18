#define _CRT_SECURE_NO_WARNINGS

#include "Qsort.h"

#include <stdio.h>

#define POINTER_IS_NULL -1
#define FILE_NOT_FOUND -2
#define READ_DATA_ERROR -3

void swapElements(int* left, int* right) {
    if (*left != *right) {
        *left ^= *right;
        *right ^= *left;
        *left ^= *right;
    }
}

void insertionSort(int* array, int left, int right, int* errorCode) {
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

void QSort(int* array, int left, int right, int* errorCode) {
    if (array == NULL) {
        *errorCode = POINTER_IS_NULL;
        return;
    }

    if (left >= right) {
        return;
    }

    const int middleElement = array[(left + right) / 2];
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

void fileReadData(const char fileName[], int array[], int *arrayLength, int* errorCode) {
    FILE* file = fopen(fileName, "r");

    if (file == NULL) {
        *errorCode = FILE_NOT_FOUND;
        return;
    }
    
    const int readBytes = fscanf(file, "%d", arrayLength);

    for (int i = 0; i < *arrayLength; ++i) {
        if (fscanf(file, "%d", &array[i]) != 1) {
            *errorCode = READ_DATA_ERROR;
            fclose(file);
            return;
        }
    }

    fclose(file);
}