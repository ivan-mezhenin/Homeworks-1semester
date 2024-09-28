#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void fillingArrayOfRandowNumbers(int array[], int length) {
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

void halfOfQSort(int array[], int length) {
    const int firstElement = array[0];
    int leftPointer = 0;
    int rightPointer = length - 1;
    while (leftPointer <= rightPointer) {
        while (array[leftPointer] < firstElement) {
            leftPointer++;
        }
        while (array[rightPointer] >= firstElement) {
            rightPointer--;
        }
        if (leftPointer <= rightPointer) {
            swapElements(&array[leftPointer], &array[rightPointer]);
            leftPointer++;
            rightPointer--;
        }
    }
}

bool testCorrectCase() {
    int arrayLength = 20;
    int* unsortedArray = malloc(arrayLength * sizeof(int));
    fillingArrayOfRandowNumbers(unsortedArray, arrayLength);

    const int firstNumber = unsortedArray[0];
    int countOfNubersThatAreSmallerThanFirstNumber = 0;

    for (int i = 0; i < arrayLength; ++i) {
        if (unsortedArray[i] < firstNumber) {
            countOfNubersThatAreSmallerThanFirstNumber++;
        }
    }

    halfOfQSort(unsortedArray, arrayLength);

    for (int i = 0; i < countOfNubersThatAreSmallerThanFirstNumber; ++i) {
        if (unsortedArray[i] >= firstNumber) {
            
            return false;
        }
    }

    for (int i = countOfNubersThatAreSmallerThanFirstNumber; i < arrayLength; ++i) {
        if (unsortedArray[i] < firstNumber) {
            return false;
        }
    }
    free(unsortedArray);
    return true;

}
int main(void) {
    if (!testCorrectCase()) {   
        printf("Tests failed\n");
        return;
    }
    int arrayLength = 20;
    int *unsortedArray = malloc(arrayLength * sizeof(int));

    fillingArrayOfRandowNumbers(unsortedArray, arrayLength);

    printf("Array before:\n");
    arrayOutput(unsortedArray, arrayLength);

    halfOfQSort(unsortedArray, arrayLength);

    printf("Array after: \n");
    arrayOutput(unsortedArray, arrayLength);

    free(unsortedArray);
}