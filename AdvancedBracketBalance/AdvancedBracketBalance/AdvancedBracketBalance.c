#include "/CHomeworks/Stack/charStack/charStack.h"

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"

#define MAX_STRING_LENGTH 100
#define INPUT_ERROR -3
#define TESTS_FAILED -6
#define INVALID_OPERATION_WITH_EMPTY_STACK 1
#define MEMORY_ALLOCATION_ERROR -1
#define POINTER_IS_NULL -2

char pairedBracket(char bracket) {
    if (bracket == ')') {
        return '(';
    }
    if (bracket == '}') {
        return '{';
    }
    if (bracket == ']') {
        return '[';
    }
}

bool isBracketSequenceCorrect(char secuence[], int length, int* errorCode) {
    CharStack* bracketStack = createCharStack(errorCode);
    if (*errorCode != 0) {
        return false;
    }

    for (int i = 0; i < length; ++i) {
        char rightBracket = secuence[i];

        if (rightBracket == '(' || rightBracket == '[' || rightBracket == '{') {
            pushChar(bracketStack, rightBracket, errorCode);
            if (*errorCode != 0) {
                return false;
            }

            continue;
        }

        if (rightBracket == '}' || rightBracket == ']' || rightBracket == ')') {
            char leftBracket = pairedBracket(rightBracket);

            if (getStackLength(bracketStack) == 0) {
                deleteCharStack(bracketStack);
                return false;
            }

            char currentTopStackElement = popChar(bracketStack, errorCode);
            if (*errorCode != 0) {
                return false;
            }

            if (currentTopStackElement != leftBracket) {
                deleteCharStack(bracketStack);
                return false;
            }

            continue;
        }

        *errorCode = INPUT_ERROR;

        deleteCharStack(bracketStack);
        return false;
    }

    bool isBalanced = getStackLength(bracketStack) == 0;
    deleteCharStack(bracketStack);
    return isBalanced;
}

bool isBracketSequenceCorrectTestCorrectCase(void) {
    int errorCode = 0;
    return isBracketSequenceCorrect("{}{}{}[][]()()()", 16, &errorCode)
        && isBracketSequenceCorrect("[({[{()}]})]", 12, &errorCode)
        && isBracketSequenceCorrect("((((()))))", 10, &errorCode);
}

bool isBracketSequenceCorrectTestIncorrectCase(void) {
    int errorCode = 0;
    return !isBracketSequenceCorrect(")))))(((((", 10, &errorCode)
        || !isBracketSequenceCorrect("{[{(})]}", 8, &errorCode)
        || !isBracketSequenceCorrect("((((())))))", 11, &errorCode);
}

bool mainTest(void) {
    return isBracketSequenceCorrectTestCorrectCase() && isBracketSequenceCorrectTestIncorrectCase();
}

int main(void) {
    if (!mainTest()) {
        printf("Tests failed!!!\n");
        return TESTS_FAILED;
    }

    char secuence[MAX_STRING_LENGTH] = "";
    int errorCode = 0;
    puts("Inter bracket sequence: ");
    gets_s(secuence, MAX_STRING_LENGTH);
    const int secuenceLength = strlen(secuence);

    bool result = isBracketSequenceCorrect(secuence, secuenceLength, &errorCode);
    if (errorCode == INPUT_ERROR) {
        printf("Incorrect bracket sequence\n");
        return errorCode;
    }
    else if (errorCode == POINTER_IS_NULL) {
        printf("Passing a null pointer\n");
        return errorCode;
    }
    else if (errorCode == MEMORY_ALLOCATION_ERROR) {
        printf("Memory allocation error\n");
        return errorCode;
    }
    else if (errorCode == INVALID_OPERATION_WITH_EMPTY_STACK) {
        printf("Invalid operation with empty stack\n");
        return errorCode;
    }

    if (result) {
        printf("Balance\n");
    }
    else {
        printf("No balance\n");
    }

    return errorCode;
}
