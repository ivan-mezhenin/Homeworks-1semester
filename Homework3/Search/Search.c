#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define POINTER_IS_NULL -1
#define TESTS_FAILED -2
#define MEMORY_ALLOCATION_ERROR -3
#define INPUT_ERROR -4 

void printArray(int array[], int length) {
    for (int i = 0; i < length; ++i) {
        printf("%d ", array[i]);
    }

    printf("\n");
}

void fillArrayOfRandowNumbers(int array[], int length) {
    for (int i = 0; i < length; ++i) {
        array[i] = rand() % 30 + 1;
    }
}

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
            --numberIndex;
            --currentNumberIndex;
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

void NumbersThatAreContaineInArray(int arrayOfDesiredNumbers[], int numbers[], int numbersLength, int array[], int arrayLength, bool arrayIsNotEmpty) {
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

bool test1() {
    int errorCode = 0;
    int testArray[] = {1, 10, 40, 2, 54, 13, 34, 47, 80, 23};
    int testNumbers[] = {1, 57, 3, 40, 100, 80, 23};
    int standartArray[] = {1, 40, 80, 23, 0, 0, 0};
    bool arrayIsNotEmpty = true;
    int* arrayOfDesiredNumbers = calloc(7, sizeof(int));
    if (arrayOfDesiredNumbers == NULL) {
        return false;
    }

    QSort(testArray, 0, 9, &errorCode);
    if (errorCode != 0) {
        return false;
    }

    NumbersThatAreContaineInArray(arrayOfDesiredNumbers, testNumbers, 7, testArray, 10, arrayIsNotEmpty);

    for (int i = 0; i < 7; ++i) {
        if (arrayOfDesiredNumbers[i] != standartArray[i]) {
            return false;
        }
    }

    return true;
}

bool test2() {
    int left = 0;
    int size = 11;
    int array[] = { 1, 6, 34, 13, 12, 9, 23, 56, 3, 5, 10 };

    bool passed = binarySearch(array, 6, left, size - 2) == 1 && binarySearch(array, 666, left, size - 2) == -1
        && binarySearch(array, 12, left, size - 2) == 4;

    return passed;
}

bool test() {
    return test1() && test2();
}

int main(void) {
    if (!test()) {
        printf("Tests failed!!!\n");
        return TESTS_FAILED;
    }

    srand(time(NULL));

    int errorCode = 0;
    int n = 0;
    int k = 0;

    printf("Inter n: ");
    if (scanf("%d", &n) != 1) {
        printf("Input error\n");
        return INPUT_ERROR;
    }

    printf("Inter k: ");
    if (scanf("%d", &k) != 1) {
        printf("Input error\n");
        return INPUT_ERROR;
    }

    int* array = malloc(n * sizeof(int));
    if (array == NULL) {
        printf("Memory allocation error while creating array\n");
        return MEMORY_ALLOCATION_ERROR;
    }

    int* numbers = malloc(k * sizeof(int));
    if (numbers == NULL) {
        printf("Memory allocation error while creating array\n");
        free(array);
        return MEMORY_ALLOCATION_ERROR;
    }

    fillArrayOfRandowNumbers(array, n);
    fillArrayOfRandowNumbers(numbers, k);

    printf("Array of random numbers of length n:\n");
    printArray(array, n);
    printf("k random numbers:\n");
    printArray(numbers, k);

    QSort(array, 0, n - 1, &errorCode);
    if (errorCode == POINTER_IS_NULL) {
        printf("Passing a null pointer in function QSort\n");
        return errorCode;
    }

    int* arrayOfDesiredNumbers = calloc(k, sizeof(int));
    if (arrayOfDesiredNumbers == NULL) {
        printf("Memory allocation error while creating array\n");
        free(array);
        free(numbers);
        return MEMORY_ALLOCATION_ERROR;
    }

    bool arrayIsNotEmpty = true;
    NumbersThatAreContaineInArray(arrayOfDesiredNumbers, numbers, k, array, n, arrayIsNotEmpty);

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
        printf("None of the numbers are containe in the array\n");
    }

    free(array);
    free(numbers);
    free(arrayOfDesiredNumbers);

    return errorCode;
}