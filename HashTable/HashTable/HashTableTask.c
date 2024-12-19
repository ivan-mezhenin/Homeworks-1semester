#include "HashTable.h"
#include "List.h"
#include "HashTableTest.h"

#include <stdio.h>
#include <stdlib.h>

#define INPUT_ERROR -1241
#define FILE_NOT_FOUND -131
#define TESTS_FAILED -45
#define MAX_WORD_SIZE 100

int hashTableTask(char* filename, int hashTableSize, int* errorCode) {
    HashTable* hashTable = createHashTable(hashTableSize, errorCode);
    if (*errorCode != 0) {
        return *errorCode;
    }

    fillInTheTableWithDataFromFile(filename, hashTable, errorCode);
    if (*errorCode != 0) {
        deleteHashTable(hashTable);
        return *errorCode;
    }

    printf("Hash table: \n");
    printHashTable(hashTable, errorCode);
    printf("\n");
    printStatisticsOfHashTable(hashTable, errorCode);

    deleteHashTable(hashTable);

    return *errorCode;
}

int main(void) {
    if (!test()) {
        printf("Tests failed\n");
        return TESTS_FAILED;
    }

    int errorCode = 0;
    int hashTableSize = 0;

    printf("Enter size of hash table: ");
    if (scanf_s("%d", &hashTableSize) != 1) {
        printf("Input error\n");
        return INPUT_ERROR;
    }

    errorCode = hashTableTask("data.txt", hashTableSize, &errorCode);
    if (errorCode == POINTER_IS_NULL) {
        printf("Passing a null pointer\n");
    }
    else if (errorCode == MEMORY_ALLOCATION_ERROR) {
        printf("Memory allocation error\n");
    }
    else if (errorCode == FILE_NOT_FOUND) {
        printf("File not found\n");
    }

    return errorCode;
}
