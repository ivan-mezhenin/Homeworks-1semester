#include "HashTable.h"
#include "List.h"

#include <stdio.h>
#include <stdlib.h>

#define INPUT_ERROR -1241
#define FILE_NOT_FOUND -131
#define MAX_WORD_SIZE 100

int hashTableTask(char* filename, int hashTableSize, int* errorCode) {
    HashTable* hashTable = createHashTable(hashTableSize, errorCode);
    if (*errorCode != 0) {
        return *errorCode;
    }

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        *errorCode = FILE_NOT_FOUND;
        return *errorCode;
    }

    while (!feof(file)) {
        char* buffer = malloc(sizeof(char) * MAX_WORD_SIZE);
        const int readBytes = fscanf(file, "%s", buffer);
        if (readBytes < 0) {
            break;
        }

        addWordInHashTable(hashTable, buffer, errorCode);
        if (*errorCode != 0) {
            return errorCode;
        }
    }

    printf("Hash table: \n");
    printHashTable(hashTable, errorCode);
    printf("\n");
    printStatisticsOfHashTable(hashTable, errorCode);
    return *errorCode;
}

int main(void) {
    int errorCode = 0;
    int hashTableSize = 0;
    printf("Enter size of hash table: ");
    if (scanf("%d", &hashTableSize) != 1) {
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
