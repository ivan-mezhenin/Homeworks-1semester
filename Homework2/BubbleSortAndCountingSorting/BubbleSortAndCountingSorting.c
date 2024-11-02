#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define ARRAY_LENGTH 100

void fillingArrayOfRandowNumbers(int *array, int length) {
    for (int i = 0; i < length; ++i) {
        array[i] = rand() % 100 + 1;
    }
}

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
void bubbleSort(int* array, int length) {

    for (int i = 0; i < length - 1; ++i) {
        for (int j = 0; j < length - 1 - i; ++j) {
            if (array[j] > array[j + 1]) {
                swapElements(&array[j], &array[j + 1]);
            }
        }
    }
}

void countingSort(int* array, int length) {
    int maxOfarray = 0;
    for (int i = 0; i < length; ++i) {
        if (array[i] > maxOfarray) {
            maxOfarray = array[i];
        }
    }
    int* indexArray = calloc(maxOfarray + 1, sizeof(int));

    for (int i = 0; i < length; ++i) {
        indexArray[array[i]]++;
    }
    int counter = 0;
    for (int i = 0; i <= maxOfarray; ++i) {
        if (indexArray[i] > 0) {
            while (indexArray[i] != 0) {
                array[counter++] = i;
                indexArray[i]--;
            }
        }
    }
    free(indexArray);
}

bool testCorrectCaseCountingSort() {
    int* unsortedArray = malloc(ARRAY_LENGTH * sizeof(int));
    fillingArrayOfRandowNumbers(unsortedArray, ARRAY_LENGTH);
    countingSort(unsortedArray, ARRAY_LENGTH);
    for (int i = 1; i < ARRAY_LENGTH; ++i) {
        if (unsortedArray[i - 1] > unsortedArray[i]) {
            return false;
        }
    }
    free(unsortedArray);
    return true;
}

bool testCorrectCaseBubbleSort() {
    int* unsortedArray = malloc(ARRAY_LENGTH * sizeof(int));
    fillingArrayOfRandowNumbers(unsortedArray, ARRAY_LENGTH);
    bubbleSort(unsortedArray, ARRAY_LENGTH);
    for (int i = 1; i < ARRAY_LENGTH; ++i) {
        if (unsortedArray[i - 1] > unsortedArray[i]) {
            return false;
        }
    }
    free(unsortedArray);
    return true;
}

int main(void) {
    if (!testCorrectCaseBubbleSort() || !testCorrectCaseCountingSort()) {
        printf("Tests failed!!\n");
        return;
    }

    int length = 0;
    printf("Inter the length of array: ");
    scanf("%d", &length);
    printf("\n");

    int* unsortedArray1 = malloc(length * sizeof(int));
    int* unsortedArray2 = malloc(length * sizeof(int));

    fillingArrayOfRandowNumbers(unsortedArray1, length);
    for (int i = 0; i < length; ++i) {
        unsortedArray2[i] = unsortedArray1[i];
    }

    if (length < 50) {
        printf("Array before sorting:\n");
        arrayOutput(unsortedArray1, length);
    }
    printf("\n");

    clock_t timeStart = clock();
    countingSort(unsortedArray1, length);
    clock_t timeCountingSort = clock() - timeStart;

    if (length < 50) {
        printf("Array after sorting:\n");
        arrayOutput(unsortedArray1, length);
    }
    printf("\n");

    clock_t timeStartBubbleSort = clock();
    bubbleSort(unsortedArray2, length);
    clock_t timeBubbleSort = clock() - timeStartBubbleSort;

    printf("Time of bubble sorting: %d\n", timeBubbleSort);
    printf("Time of counting sorting: %d\n", timeCountingSort);

    free(unsortedArray1);
    free(unsortedArray2);
}
