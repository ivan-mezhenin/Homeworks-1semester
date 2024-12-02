#include "AVLTreeTest.h"
#include "AVLTree.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>


bool test1(void) {
    int errorCode = 0;
    AVLTree* tree= createAVLTree(&errorCode);
    if (errorCode != 0) {
        return false;
    }

    char value1[] = "amogus";
    char value2[] = "tp2024";

    addValueInAVLTree(tree, "a", value1, &errorCode);
    addValueInAVLTree(tree, "b", value2, &errorCode);
    addValueInAVLTree(tree, "c", value1, &errorCode);
    addValueInAVLTree(tree, "d", value2, &errorCode);
    addValueInAVLTree(tree, "h", value1, &errorCode);
    addValueInAVLTree(tree, "k", value2, &errorCode);
    addValueInAVLTree(tree, "a", value2, &errorCode);

    if (errorCode != 0) {
        return false;
    }

    bool passed = (strcmp(getValue(tree, "a", &errorCode), value2) == 0) &&
        (strcmp(getValue(tree, "c", &errorCode), value1) == 0) &&
        (strcmp(getValue(tree, "h", &errorCode), value1) == 0);

    passed = passed && isKeyInAVLTree(tree, "a", &errorCode) && isKeyInAVLTree(tree, "k", &errorCode) &&
        isKeyInAVLTree(tree, "c", &errorCode);

    deleteAVLTree(tree);
    return passed && (errorCode == 0);
}

bool test2(void) {
    int errorCode = 0;
    AVLTree* tree= createAVLTree(&errorCode);
    if (errorCode != 0) {
        return false;
    }

    char value1[] = "aboba";
    char value2[] = "barabimbam";

    addValueInAVLTree(tree, "k", value1, &errorCode);
    addValueInAVLTree(tree, "sa", value2, &errorCode);
    addValueInAVLTree(tree, "j", value1, &errorCode);
    addValueInAVLTree(tree, "dafa", value2, &errorCode);
    addValueInAVLTree(tree, "a", value1, &errorCode);
    addValueInAVLTree(tree, "b", value2, &errorCode);
    addValueInAVLTree(tree, "et", value2, &errorCode);
    if (errorCode != 0) {
        return false;
    }

    bool passed = (strcmp(getValue(tree, "sa", &errorCode), value2) == 0);

    addValueInAVLTree(tree, "sa", value1, &errorCode);
    passed = passed && (strcmp(getValue(tree, "sa", &errorCode), value1) == 0);

    deleteValue(tree, "k", &errorCode);
    deleteValue(tree, "a", &errorCode);
    deleteValue(tree, "j", &errorCode);
    deleteValue(tree, "dafa", &errorCode);


    passed = passed && !isKeyInAVLTree(tree, "k", &errorCode) && !isKeyInAVLTree(tree, "a", &errorCode) &&
        !isKeyInAVLTree(tree, "j", &errorCode) && !isKeyInAVLTree(tree, "dafa", &errorCode);

    deleteAVLTree(tree);
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