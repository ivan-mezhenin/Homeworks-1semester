#include "/CHomeworks/Stack/charStack/charStack.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS
#define MAX_STRING_SIZE 101
#define INCORRECT_EXPRESSION -1
#define TESTS_FAILED -2

void printExpressionWithSpaces(char expression[], int length) {
    for (int i = 0; i < length; ++i) {
        if (i == length - 1) {
            printf("%c", expression[i]);
        }
        else {
            printf("%c ", expression[i]);
        }
    }
    printf("\n");
}

bool isOperation(char sign) {
    return sign == '*' || sign == '+' || sign == '/' || sign == '-';
}

int getOperationPrecedence(char sign) {
    switch (sign) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 0;
    }
}

void convertExpressionFromInfixFormToPostfix(char infixExpression[], int stringLength, char postfixExpression[], int* errorCode) {
    CharStack* signs = createCharStack(errorCode);
    if (*errorCode != 0) {
        return;
    }

    int postfixExpressionIndex = 0;
    char currentSymbol = ' ';

    for (int i = 0; i < stringLength; ++i) {
        currentSymbol = infixExpression[i];

        if (currentSymbol == ' ') {
            continue;
        }
        else if ((currentSymbol <= '9' && currentSymbol >= '0')) {
            postfixExpression[postfixExpressionIndex++] = currentSymbol;
        }
        else if (currentSymbol == '(') {
            pushChar(signs, currentSymbol, errorCode);
            if (*errorCode != 0) {
                deleteCharStack(signs);
                return;
            }

        }
        else if (isOperation(currentSymbol)) {
            while (topCharStack(signs, errorCode) != '\0' &&
                (getOperationPrecedence(topCharStack(signs, errorCode)) >= getOperationPrecedence(currentSymbol))) {
                postfixExpression[postfixExpressionIndex++] = popChar(signs, errorCode);
                if (*errorCode != 0) {
                    deleteCharStack(signs);
                    return;
                }
            }
            pushChar(signs, currentSymbol, errorCode);
            if (*errorCode != 0) {
                deleteCharStack(signs);
                return;
            }
        }
        else if (currentSymbol == ')') {
            while (topCharStack(signs, errorCode) != '\0' && topCharStack(signs, errorCode) != '(') {
                postfixExpression[postfixExpressionIndex++] = popChar(signs, errorCode);
                if (*errorCode != 0) {
                    deleteCharStack(signs);
                    return;
                }
            }
            popChar(signs, errorCode);
            if (*errorCode != 0) {
                deleteCharStack(signs);
                return;
            }
        }
        else {
            *errorCode = INCORRECT_EXPRESSION;
            deleteCharStack(signs);
            return;
        }
    }

    while (topCharStack(signs, errorCode) != '\0') {
        postfixExpression[postfixExpressionIndex++] = popChar(signs, errorCode);
        if (*errorCode != 0) {
            deleteCharStack(signs);
            return;
        }
    }

    deleteCharStack(signs);
}

bool convertExpressionFromInfixFormToPostfixTest(void) {
    const char* testInfix1 = "(1 + 1) * 2";
    char postfix1[MAX_STRING_SIZE] = "";
    int errorCode1 = 0;
    const char* expectedResult1 = "11+2*";
    convertExpressionFromInfixFormToPostfix(testInfix1, strlen(testInfix1), postfix1, &errorCode1);
    if (strcmp(postfix1, expectedResult1) != 0) {
        printf("Test (%s) failed\n", testInfix1);
        return false;
    }

    const char* testInfix2 = "(2 + 3) * (4 + 5)";
    char postfix2[MAX_STRING_SIZE] = "";
    int errorCode2 = 0;
    const char* expectedResult2 = "23+45+*";
    convertExpressionFromInfixFormToPostfix(testInfix2, strlen(testInfix2), postfix2, &errorCode2);
    if (strcmp(postfix2, expectedResult2) != 0) {
        printf("Test (%s) failed\n", testInfix2);
        return false;
    }

    const char* testInfix3 = "(1 + 6) * (5 + 3 * (7 + 8))";
    char postfix3[MAX_STRING_SIZE] = "";
    int errorCode3 = 0;
    const char* expectedResult3 = "16+5378+*+*";
    convertExpressionFromInfixFormToPostfix(testInfix3, strlen(testInfix3), postfix3, &errorCode3);
    if (strcmp(postfix3, expectedResult3) != 0) {
        printf("Test (%s) failed\n", testInfix3);
        return false;
    }

    return true;
}

int main(void) {
    
    if (!convertExpressionFromInfixFormToPostfixTest()) {
        return TESTS_FAILED;
    }

    int errorCode = 0;
    char infixExpression[MAX_STRING_SIZE] = "";
    char postfixExpression[MAX_STRING_SIZE] = "";

    puts("Enter expression in infix form (max 100 symbols): ");
    gets_s(infixExpression, MAX_STRING_SIZE);

    convertExpressionFromInfixFormToPostfix(infixExpression, strlen(infixExpression), postfixExpression, &errorCode);

    if (errorCode == 0) {
        printExpressionWithSpaces(postfixExpression, strlen(postfixExpression));
    }
    else if (errorCode == INCORRECT_EXPRESSION) {
        printf("Your expression is incorrect\n");
        return INCORRECT_EXPRESSION;
    }
    
    return 0;
}