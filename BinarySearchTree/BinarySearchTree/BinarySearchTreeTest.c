#include "BinarySearchTreeTest.h"
#include "Dictionary.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>


bool test1(void) {
    int errorCode = 0;
    Dictionary* dictionary = createDictionary(&errorCode);
    if (errorCode != 0) {
        return false;
    }

    char* value1 = "amogus";
    char* value2 = "tp2024";

    addValueInDictionary(dictionary, 1488, value1, &errorCode);
    addValueInDictionary(dictionary, 5, value2, &errorCode);
    addValueInDictionary(dictionary, 700, value1, &errorCode);
    addValueInDictionary(dictionary, 1, value2, &errorCode);
    addValueInDictionary(dictionary, 1500, value1, &errorCode);
    addValueInDictionary(dictionary, 3, value2, &errorCode);
    addValueInDictionary(dictionary, 8, value1, &errorCode);
    addValueInDictionary(dictionary, 148, value2, &errorCode);
    addValueInDictionary(dictionary, 9, value1, &errorCode);
    if (errorCode != 0) {
        return false;
    }

    bool passed = (strcmp(getValue(dictionary, 1488, &errorCode), value1) == 0) &&
        (strcmp(getValue(dictionary, 9, &errorCode), value1) == 0) &&
        (strcmp(getValue(dictionary, 1, &errorCode), value2) == 0);

    passed = passed && isKeyInDictionary(dictionary, 1488, &errorCode) && isKeyInDictionary(dictionary, 148, &errorCode) &&
            isKeyInDictionary(dictionary, 700, &errorCode);

    deleteDictionary(dictionary);
   return passed && (errorCode == 0);
}

bool test2(void) {
    int errorCode = 0;
    Dictionary* dictionary = createDictionary(&errorCode);
    if (errorCode != 0) {
        return false;
    }

    char* value1 = "aboba";
    char* value2 = "barabimbam";

    addValueInDictionary(dictionary, 13, value1, &errorCode);
    addValueInDictionary(dictionary, 58, value2, &errorCode);
    addValueInDictionary(dictionary, 700, value1, &errorCode);
    addValueInDictionary(dictionary, 12, value2, &errorCode);
    addValueInDictionary(dictionary, 11500, value1, &errorCode);
    addValueInDictionary(dictionary, 34, value2, &errorCode);
    addValueInDictionary(dictionary, 5, value1, &errorCode);
    addValueInDictionary(dictionary, 11, value2, &errorCode);
    addValueInDictionary(dictionary, 2, value1, &errorCode);
    if (errorCode != 0) {
        return false;
    }

    bool passed = (strcmp(getValue(dictionary, 13, &errorCode), value1) == 0);

    addValueInDictionary(dictionary, 13, value2, &errorCode);
    passed = passed && (strcmp(getValue(dictionary, 13, &errorCode), value2) == 0);

    deleteValue(dictionary, 11500, &errorCode);
    deleteValue(dictionary, 34, &errorCode);
    deleteValue(dictionary, 5, &errorCode);
    deleteValue(dictionary, 700, &errorCode);


    passed = passed && !isKeyInDictionary(dictionary, 11500, &errorCode) && !isKeyInDictionary(dictionary, 34, &errorCode) &&
        !isKeyInDictionary(dictionary, 5, &errorCode) && !isKeyInDictionary(dictionary, 700, &errorCode);

    deleteDictionary(dictionary);
    return passed && (errorCode == 0);
}

bool test(void) {
    bool testCases[2] = { test1(), test2() };
    bool testsCompleted = true;
    for (int i = 0; i < 2; ++i) {
        if (!testCases[i]) {
            printf("Test %d failed\n", i + 1);
            testsCompleted = false;
        }
    }

    return testsCompleted;
}