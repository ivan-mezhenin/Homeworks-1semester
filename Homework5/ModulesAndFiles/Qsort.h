#pragma once

//сортировка сортировками, принимает массив, и границы, в пределах которых его нужно отсортировать
void insertionSort(int array[], int left, int right);

//быстрая сортировка, принимает массив, и границы, в пределах которых его нужно отсортировать
void qSort(int array[], int left, int right);

//функция для чтения массива и его длинны из файла, принимает имя файла, указатель на массив и его длинну
void fileReadData(const char fileName[], int array[], int* arrayLength);

//функция меняет местами два элемента, принимает два элемента
void swapElements(int* left, int* right);