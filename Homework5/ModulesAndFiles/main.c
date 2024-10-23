#define _CRT_SECURE_NO_WARNINGS

#include "Qsort.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ARRAY_LENGTH 1000

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

int TheMostFrequentElementInTheArray(int array[], int arrayLength) {
    qSort(array, 0, arrayLength - 1);

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
    int testArray[] = { 1,90,6,3,6,70,2,90,15,30,1,1,6,3,6 };
    return TheMostFrequentElementInTheArray(testArray, 14) == 6;
}

int main(void) {
    if (!testCorrectCase()) {
        printf("Tests failed!!!\n");
        return;
    }

    int arrayLength = 0;
    int array[ARRAY_LENGTH];

    fileReadData("data.txt", array, &arrayLength);

    printf("Your array from file:\n");
    arrayOutput(array, arrayLength);

    printf("The most Frequent ELement in Array: %d", TheMostFrequentElementInTheArray(array, arrayLength));
}