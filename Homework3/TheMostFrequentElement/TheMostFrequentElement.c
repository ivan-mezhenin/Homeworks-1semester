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

void fillingArrayOfRandowNumbers(int array[], int length) {
    for (int i = 0; i < length; ++i) {
        array[i] = rand() % 14 + 1;
    }
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
        QSort(array, left, rightPointer);
    }

    if ((right - leftPointer + 1) < 10) {
        insertionSort(array, leftPointer, right);
    }
    else {
        QSort(array, leftPointer, right);
    }

}

int TheMostFrequentElementInTheArray(int array[], int arrayLength) {
    QSort(array, 0, arrayLength - 1);

    int currentElement = array[0];
    int currentElementCounter = 0;
    int mostFrequentELement = -1;
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

bool testCorrectCase() {
    int testArray[] = {1,90,6,3,6,70,2,90,15,30,1,1,6,3,6};
    return TheMostFrequentElementInTheArray(testArray, 14) == 6;
}

int main(void) {
    if (!testCorrectCase()) {
        printf("Tests failed!!!\n");
        return;
    }

    int arrayLength = 0;
    
    printf("Inter length of array: ");
    scanf("%d", &arrayLength);

    int* array = malloc(arrayLength * sizeof(int));
    printf("Inter the array:\n");
    for (int i = 0; i < arrayLength; ++i) {
        scanf("%d", &array[i]);
    }

    printf("The most Frequent ELement in Array: %d", TheMostFrequentElementInTheArray(array, arrayLength));
}