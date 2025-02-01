#include "HashTableTest.h"
#include "List.h"
#include "HashTable.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool test1(void) {
    int errorCode = 0;
    int size = 10;
    HashTable* hashTable = createHashTable(size, &errorCode);
    if (errorCode != 0) {
        return false;
    }

    fillInTheTableWithDataFromFile("testdata1.txt", hashTable, &errorCode);
    if (errorCode != 0) {
        deleteHashTable(hashTable);
        return false;
    }

    ListElement** table = getTable(hashTable, &errorCode);
    if (errorCode != 0) {
        deleteHashTable(hashTable);
        return false;
    }

    unsigned int index = hash("amogus", size);
    ListElement* current = table[index];
    int expectedResult = 21;

    bool passed = strcmp(current->word, "amogus") == 0 && current->frequency == expectedResult;

    deleteHashTable(hashTable);
    return passed;
}

bool test(void) {
    bool testCases[1] = { test1()};
    bool testsCompleted = true;

    for (int i = 0; i < 1; ++i) {
        if (!testCases[i]) {
            printf("Test %d failed\n", i + 1);
            testsCompleted = false;
        }
    }

    return testsCompleted;
}