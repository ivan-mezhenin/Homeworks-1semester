#include "/CHomeworks/Stack/CharStack/charStack.h"

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"

#define _CRT_SECURE_NO_WARNINGS
#define MAX_STRING_LENGTH 100
#define INPUT_ERROR -3
#define TESTS_FAILED 1488
#define TOP_OF_STACK_IS_NULL '\0'

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
    CharStack* bracketStack = createCharStack();

    for (int i = 0; i < length; ++i) {
        char rightBracket = secuence[i];

        if (rightBracket == '(' || rightBracket == '[' || rightBracket == '{') {
            pushChar(bracketStack, rightBracket);
        }
        else if (rightBracket == '}' || rightBracket == ']' || rightBracket == ')') {
            char leftBracket = pairedBracket(secuence[i], errorCode);

            if (topCharStack(bracketStack) == TOP_OF_STACK_IS_NULL) {
                return false;
            }

            char currentTopStackElement = popChar(bracketStack);
            if (currentTopStackElement != leftBracket) {
                return false;
            }
        }
        else {
            *errorCode = INPUT_ERROR;
            return false;
        }
    }
    return topCharStack(bracketStack) == TOP_OF_STACK_IS_NULL;
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

    if (isBracketSequenceCorrect(secuence, secuenceLength, &errorCode)) {
        printf("Balance\n");
    }
    else {
        if (errorCode == INPUT_ERROR) {
            printf("Sequence must consist of \"({[)}]\"\n");
        }
        else {
            printf("No balance\n");
        }
    }
}
