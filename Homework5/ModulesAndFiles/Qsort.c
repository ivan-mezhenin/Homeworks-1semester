#define _CRT_SECURE_NO_WARNINGS

#include "Qsort.h"

#include <stdio.h>

void swapElements(int* left, int* right) {
    if (*left != *right) {
        *left ^= *right;
        *right ^= *left;
        *left ^= *right;
    }
}

void insertionSort(int array[], int left, int right) {
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

void qSort(int array[], int left, int right) {
    if (left >= right) {
        return;
    }

    const int middleElement = array[(left + right) / 2];
    int leftPointer = left;
    int rightPointer = right;

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

    if ((rightPointer - left + 1) < 10) {
        insertionSort(array, left, rightPointer);
    }
    else {
        qSort(array, left, rightPointer);
    }

    if ((right - leftPointer + 1) < 10) {
        insertionSort(array, leftPointer, right);
    }
    else {
        qSort(array, leftPointer, right);
    }
}

void fileReadData(const char fileName[], int array[], int *arrayLength) {
    FILE* file = fopen(fileName, "r");

    if (file == NULL) {
        printf("Файл не найден\n");
        return;
    }
    
    const int readBytes = fscanf(file, "%d", arrayLength);

    for (int i = 0; i < *arrayLength; ++i) {
        fscanf(file, "%d", &array[i]);
    }

    fclose(file);
}