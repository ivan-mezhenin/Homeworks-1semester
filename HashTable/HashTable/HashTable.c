#include "HashTable.h"
#include "List.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define FILE_NOT_FOUND -131
#define MAX_WORD_SIZE 100

typedef struct HashTable {
    ListElement** table;
    int size;
    int amountOfUniqueWords;
} HashTable;

HashTable* createHashTable(int size, int* errorCode) {
    HashTable* hashTable = calloc(1, sizeof(HashTable));
    if (hashTable == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }

    hashTable->size = size;
    hashTable->amountOfUniqueWords = 0;
    hashTable->table = calloc(size, sizeof(ListElement*));
    if (hashTable->table == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        free(hashTable);
        return NULL;
    }

    for (int i = 0; i < size; ++i) {
        hashTable->table[i] = NULL;
    }

    return hashTable;
}

ListElement** getTable(HashTable* hashTable, int* errorCode) {
    if (hashTable == NULL || hashTable->table == NULL) {
        *errorCode = POINTER_IS_NULL;
        return NULL;
    }

    return hashTable->table;
}

unsigned int hash(char* word, int tableSize) {
    unsigned int hashValue = 0;
    int primeNumber = 31;

    for (int i = 0; word[i] != '\0'; ++i) {
        hashValue = hashValue * primeNumber + word[i];
    }

    return hashValue % tableSize;
}

void addWordInHashTable(HashTable* hashTable, char* word, int *errorCode) {
    unsigned int index = hash(word, hashTable->size);

    bool wordIsUnique = true;

    addElement(&hashTable->table[index], word, errorCode, &wordIsUnique);
    if (*errorCode != 0) {
        return;
    }

    if (wordIsUnique) {
        ++hashTable->amountOfUniqueWords;
    }
}

void fillInTheTableWithDataFromFile(char* filename, HashTable* hashTable, int* errorCode) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        *errorCode = FILE_NOT_FOUND;
        return;
    }

    while (!feof(file)) {
        char* buffer = malloc(sizeof(char) * MAX_WORD_SIZE);
        const int readBytes = fscanf(file, "%s", buffer);
        if (readBytes < 0) {
            break;
        }

        addWordInHashTable(hashTable, buffer, errorCode);
        if (*errorCode != 0) {
            fclose(file);
            return;
        }
    }

    fclose(file);
}

void printHashTable(HashTable* hashTable, int *errorCode) {
    ListElement** table = hashTable->table;
    for (int i = 0; i < hashTable->size; ++i) {
        printList(&table[i], errorCode);
        if (*errorCode != 0) {
            return;
        }
    }
}

void deleteHashTable(HashTable* hashTable) {
    for (int i = 0; i < hashTable->size; i++) {
        deleteList(hashTable->table[i]);
    }

    free(hashTable->table);
    free(hashTable);
}

void printStatisticsOfHashTable(HashTable* hashTable, int *errorCode) {
    if (hashTable == NULL) {
        *errorCode = POINTER_IS_NULL;
        return;
    }

    int amountOfNonEmptyElements = 0;
    int maxLength = 0;
    int totalLength = 0;

    for (int i = 0; i < hashTable->size; ++i) {
        int length = 0;
        ListElement* current = hashTable->table[i];
        if (current == NULL) {
            continue;
        }

        while (current != NULL) {
            ++length;
            current = current->next;
        }

        totalLength += length;
        ++amountOfNonEmptyElements;
        maxLength = max(maxLength, length);
    }

    printf("Fill factor: %.2f\n", (double)hashTable->amountOfUniqueWords / hashTable->size);
    printf("The average length of the list: %.2f\n", (amountOfNonEmptyElements > 0) ?
        (double)totalLength / amountOfNonEmptyElements : 0);
    printf("The max length of the list: %d\n", maxLength);

}