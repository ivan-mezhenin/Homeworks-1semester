#include "ForPostfixToInfixFormTest.h"
#include "/CHomeworks/Stack/charStack/charStack.h"
#include "ForPostfixToInfixForm.h"

#include "string.h"

#define MAX_STRING_SIZE 101
#define INCORRECT_EXPRESSION -3

bool test1(void) {
    const char* testInfix = "(1 + 1) * 2";
    char postfix[MAX_STRING_SIZE] = "";
    int errorCode = 0;
    const char* expectedResult = "11+2*";

    convertExpressionFromInfixFormToPostfix(testInfix, strlen(testInfix), postfix, &errorCode);

    return strcmp(postfix, expectedResult) == 0 && errorCode == 0;
}

bool test2(void) {
    const char* testInfix = "(2 + 3) * (4 + 5)";
    char postfix[MAX_STRING_SIZE] = "";
    int errorCode = 0;
    const char* expectedResult = "23+45+*";

    convertExpressionFromInfixFormToPostfix(testInfix, strlen(testInfix), postfix, &errorCode);

    return strcmp(postfix, expectedResult) == 0 && errorCode == 0;
}

bool test3(void) {
    const char* testInfix = "(1 + 6) * (5 + 3 * (7 + 8))";
    char postfix[MAX_STRING_SIZE] = "";
    int errorCode = 0;
    const char* expectedResult = "16+5378+*+*";

    convertExpressionFromInfixFormToPostfix(testInfix, strlen(testInfix), postfix, &errorCode);

    return strcmp(postfix, expectedResult) == 0 && errorCode == 0;
}

bool test4(void) {
    const char* testInfix = "(1 + 6) * !";
    char postfix[MAX_STRING_SIZE] = "";
    int errorCode = 0;

    convertExpressionFromInfixFormToPostfix(testInfix, strlen(testInfix), postfix, &errorCode);

    return errorCode == INCORRECT_EXPRESSION;
}


bool test(void) {
    int amountOfTests = 4;
    bool testCases[4] = { test1(), test2(), test3(), test4()};
    bool testsCompleted = true;

    for (int i = 0; i < amountOfTests; ++i) {
        if (!testCases[i]) {
            printf("Test %d failed\n", i + 1);
            testsCompleted = false;
        }
    }

    return testsCompleted;
}