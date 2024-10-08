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
int binarySearch(int array[], int element, int left, int right) {
    if (left > right) {
        return -1;
    }

    int middle = (left + right) / 2;

    if (array[middle] == element) {
        return middle;
    }

    if (array[middle] > element) {
        return binarySearch(array, element, left, middle - 1);
    }

    return binarySearch(array, element, middle + 1, right);
}

void NumbersThatAreContaineInArray(int arrayOfDesiredNumbers[], int numbers[], int numbersLength, int array[], int arrayLength,bool arrayIsNotEmpty) {
    int numberIndex = 0;

    for (int i = 0; i < numbersLength; ++i) {
        if (binarySearch(array, numbers[i], 0, arrayLength - 1) != -1) {
            arrayOfDesiredNumbers[numberIndex] = numbers[i];
            ++numberIndex;

        }
    }
    if (numberIndex == 0) {
        arrayIsNotEmpty = false;
    }
}

bool testCorrectCase() {
    int testArray[] = { 1,10,40,2,54,13,34,47,80,23 };
    int testNumbers[] = { 1,57,3,40,100,80,23 };
    int* arrayOfDesiredNumbers = calloc(7, sizeof(int));
    int standartArray[] = { 1,40,80,23,0,0,0 };
    bool arrayIsNotEmpty = true;

    QSort(testArray, 0, 9);
    NumbersThatAreContaineInArray(arrayOfDesiredNumbers, testNumbers, 7, testArray, 10, arrayIsNotEmpty);

    for (int i = 0; i < 7; ++i) {
        if (arrayOfDesiredNumbers[i] != standartArray[i]) {
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

    srand(time(NULL));

    int n = 0;
    int k = 0;
    printf("Inter n: ");
    scanf("%d", &n);
    printf("Inter k: ");
    scanf("%d", &k);

    int* array = malloc(n * sizeof(int));
    int* numbers = malloc(k * sizeof(int));

    fillingArrayOfRandowNumbers(array, n);
    fillingArrayOfRandowNumbers(numbers, k);

    printf("Array of random numbers of length n:\n");
    arrayOutput(array, n);
    printf("k random numbers:\n");
    arrayOutput(numbers, k);

    QSort(array,0,n - 1);
    int * arrayOfDesiredNumbers = calloc(k, sizeof(int));
    bool arrayIsNotEmpty = true;
    NumbersThatAreContaineInArray(arrayOfDesiredNumbers, numbers, k, array, n,arrayIsNotEmpty);

    if (arrayIsNotEmpty) {
        printf("Numbers, that are containe in array:\n");
        for (int i = 0; i < k; ++i) {
            if (arrayOfDesiredNumbers[i] != 0) {
                printf("%d ", arrayOfDesiredNumbers[i]);
            }
            else {
                break;
            }
        }
    }
    else {
        printf("None of the numbers are containe in the array");
    }

    free(array);
    free(numbers);
    free(arrayOfDesiredNumbers);
}