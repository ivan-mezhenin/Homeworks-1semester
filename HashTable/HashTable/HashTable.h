#pragma once

#include <stdio.h>

#define MEMORY_ALLOCATION_ERROR -1
#define POINTER_IS_NULL -2
#define MAX_DATA_SIZE 100

typedef struct HashTable HashTable;

typedef struct ListElement ListElement;

// create Hash table
HashTable* createHashTable(int size, int* errorCode);

// add word in hash table
void addWordInHashTable(HashTable* hashTable, char* word, int* errorCode);

// print hash table
void printHashTable(HashTable* hashTable, int* errorCode);

// print statistics of hash table
void printStatisticsOfHashTable(HashTable* hashTable, int* errorCode);

// free memory of hash table
void deleteHashTable(HashTable* hashTable);

// fill hash table with data from the file
void fillInTheTableWithDataFromFile(char* filename, HashTable* hashTable, int* errorCode);

// return table
ListElement** getTable(HashTable* hashTable, int* errorCode);

// return hash
unsigned int hash(char* word, int tableSize);