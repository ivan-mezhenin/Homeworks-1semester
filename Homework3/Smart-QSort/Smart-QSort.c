#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void arrayOutput(int array[], int length) {
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

void QSort(int array[], int left, int right) {
    if (left >= right) {
        return;
    }

    const int middleElement = array[(left + right)/2];
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
        QSort(array, left, rightPointer);
    }

    if ((right - leftPointer + 1) < 10) {
        insertionSort(array, leftPointer, right);
    }
    else {
        QSort(array, leftPointer, right);
    }
    
}

bool testCorrectCase() {
    int testArray[] = {1500, 1, 34, 14, 12, 3, 1000, 10000, 69, 78, 31, 100, 23};
    int arraySize = sizeof(testArray) / sizeof(testArray[0]);

    QSort(testArray, 0, arraySize - 1);

    int standartArray[] = { 1, 3, 12, 14, 23, 31, 34, 69, 78, 100, 1000,1500,10000 };
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

int main(void) {
    if (!testCorrectCase()) {
        printf("Tests failed!!!\n");
        return;
    }
    int start = 0;
    int end = 0;
    int arrayLength = 0;

    printf("Inter the length of array: ");
    scanf("%d", &arrayLength);

    int *array = malloc(arrayLength * sizeof(int));

    printf("Inter array:\n");
    for (int i = 0; i < arrayLength; ++i) {
        scanf("%d", &array[i]);
    }
    printf("Array before sorting:\n");
    arrayOutput(array, arrayLength);

    QSort(array, 0, arrayLength - 1);

    printf("Array after sorting:\n");
    arrayOutput(array, arrayLength);

    free(array);
}