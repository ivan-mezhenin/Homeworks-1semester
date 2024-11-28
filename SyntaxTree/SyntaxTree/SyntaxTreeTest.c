#include "SyntaxTreeTest.h"
#include "SyntaxTree.h"

#include <stdio.h>
#include <stdbool.h>

bool test1(void) {
    int errorCode = 0;
    FILE* file = fopen("testdata1.txt", "r");
    SyntaxTree* tree = NULL;

    buildSyntaxTree(&tree, file, &errorCode);
    fclose(file);

    int expectedResult = 836;

    bool passed = expectedResult == calculateSyntaxTree(tree);
    deleteSyntaxTree(&tree);
    return passed;
}

bool test2(void) {
    int errorCode = 0;
    FILE* file = fopen("testdata2.txt", "r");
    SyntaxTree* tree = NULL;

    buildSyntaxTree(&tree, file, &errorCode);
    fclose(file);

    int expectedResult = 360;

    bool passed = expectedResult == calculateSyntaxTree(tree);
    deleteSyntaxTree(&tree);
    return passed;
}

bool test3(void) {
    int errorCode = 0;
    FILE* file = fopen("testdata3.txt", "r");
    SyntaxTree* tree = NULL;

    buildSyntaxTree(&tree, file, &errorCode);
    fclose(file);

    int expectedResult = 44;

    bool passed = expectedResult == calculateSyntaxTree(tree);
    deleteSyntaxTree(&tree);
    return passed;
}

bool test(void) {
    bool testCases[3] = { test1(), test2(), test3()};
    bool testsCompleted = true;

    for (int i = 0; i < 3; ++i) {
        if (!testCases[i]) {
            printf("Test %d failed\n", i + 1);
            testsCompleted = false;
        }
    }

    return testsCompleted;
}