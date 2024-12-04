#include "HashTable.h"
#include "List.h"

#include <stdlib.h>
#include <stdbool.h>

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

    return hashTable;
}

unsigned int hash(char* word, int tableSize) {
    int primeNumber = 31;
    int hashValue = word[0] - 'a' + 1;
    for (int i = 1; i < strlen(word); ++i) {
        hashValue *= primeNumber;
        hashValue += word[i] - 'a';
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

int main(void) {
    int n = 32;
    int errorCode = 0;
    HashTable* table = createHashTable(n, &errorCode);
    addWordInHashTable(table, "aboba", &errorCode);
    addWordInHashTable(table, "aboba", &errorCode);
    addWordInHashTable(table, "aboba", &errorCode);
    addWordInHashTable(table, "aboba", &errorCode);
    addWordInHashTable(table, "aboba", &errorCode);
    addWordInHashTable(table, "aboba", &errorCode);
    addWordInHashTable(table, "aboba", &errorCode);
    addWordInHashTable(table, "aboba", &errorCode);
    addWordInHashTable(table, "aboba", &errorCode);
    addWordInHashTable(table, "aboba", &errorCode);
    addWordInHashTable(table, "aboba", &errorCode);
    addWordInHashTable(table, "aboba", &errorCode);
    addWordInHashTable(table, "ivan", &errorCode);
    addWordInHashTable(table, "nikita", &errorCode);
    addWordInHashTable(table, "really???", &errorCode);
    printf("%d", getFrequency( table->table[hash("aboba", n)]));
}