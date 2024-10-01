#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

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
    QSort(array, left, rightPointer);
    QSort(array, leftPointer, right);
}

int main(void) {
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
    QSort(array, 0, arrayLength - 1);
    arrayOutput(array, arrayLength);




    free(array);
}