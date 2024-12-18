#pragma once

// sort array
void QSort(int* array, int left, int right, int* errorCode);

// read data from file to array
void fileReadData(const char fileName[], int array[], int* arrayLength, int* errorCode);