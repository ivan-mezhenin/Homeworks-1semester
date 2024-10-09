#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

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

void shellSort(int* array, int arrayLength) {
    for (int i = arrayLength / 2; i > 0; i /= 2) {
        for (int j = i; j < arrayLength; ++j) {
            for (int k = j - i; k >= 0 && array[k] > array[k + i]; k -= i) {
                swapElements(&array[k], &array[k + i]);
            }
        }
    }
}

bool testCorrectCase() {
    int testArray[] = { 1500, 1, 34, 14, 12, 3, 1000, 10000, 69, 78, 31, 100, 23 };
    int arrayLength = sizeof(testArray) / sizeof(testArray[0]);

    shellSort(testArray, arrayLength);

    int standartArray[] = { 1, 3, 12, 14, 23, 31, 34, 69, 78, 100, 1000,1500,10000 };
    int standartLength = sizeof(standartArray) / sizeof(standartArray[0]);

    if (arrayLength != standartLength) {
        return false;
    }

    for (int i = 0; i < arrayLength; ++i) {
        if (testArray[i] != standartArray[i]) {
            return false;
        }
    }

    return true;
}

int main(void) {
    if (!testCorrectCase()) {
        printf("Tests failed!!!");
        return true;
    }

    int arrayLength = 0;
    printf("Inter length of array: ");
    scanf("%d", &arrayLength);

    int* array = malloc(arrayLength * sizeof(int));
    printf("Inter array:\n");
    for (int i = 0; i < arrayLength; ++i) {
        scanf("%d", &array[i]);
    }
    
    printf("Array before sorting: \n");
    arrayOutput(array, arrayLength);

    shellSort(array, arrayLength);

    printf("Array after sorting: \n");
    arrayOutput(array, arrayLength);

    free(array);
}