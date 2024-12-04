#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define MEMORY_ALLOCATION_ERROR -1
#define POINTER_IS_NULL -2
#define MAX_DATA_SIZE 100

typedef struct HashTable HashTable;

//create Hash table
HashTable* createHashTable(int size, int* errorCode);

//return hash key for word
unsigned int hash(char* word, int tableSize);

//add word in hash table
void addWordInHashTable(HashTable* hashTable, char* word, int* errorCode);