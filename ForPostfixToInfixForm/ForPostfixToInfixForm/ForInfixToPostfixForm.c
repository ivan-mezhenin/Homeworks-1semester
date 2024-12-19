#include "/CHomeworks/Stack/charStack/charStack.h"
#include "ForPostfixToInfixFormTest.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STRING_SIZE 101
#define INCORRECT_EXPRESSION -3
#define TESTS_FAILED -4
#define INVALID_OPERATION_WITH_EMPTY_STACK 1
#define MEMORY_ALLOCATION_ERROR -1
#define POINTER_IS_NULL -2
#define NO_ERROR 0

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

        switch (currentSymbol) {
            case ' ': {
                continue;
            }

            case '(': {
                pushChar(signs, currentSymbol, errorCode);
                if (*errorCode != 0) {
                    deleteCharStack(signs);
                    return;
                }
                break;
            }

            case ')': {
                while (getStackLength(signs) != 0 && topCharStack(signs, errorCode) != '(') {
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

                break;
            }

            default: {
                if ((currentSymbol <= '9' && currentSymbol >= '0')) {
                    postfixExpression[postfixExpressionIndex++] = currentSymbol;
                    continue;
                }

                if (isOperation(currentSymbol)) {
                    while (getStackLength(signs) != 0 &&
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

                    continue;
                }

                *errorCode = INCORRECT_EXPRESSION;
                deleteCharStack(signs);
                return;
            }
        }
    }

    while (getStackLength(signs) != 0) {
        postfixExpression[postfixExpressionIndex++] = popChar(signs, errorCode);
        if (*errorCode != 0) {
            deleteCharStack(signs);
            return;
        }
    }

    deleteCharStack(signs);
}

int main(void) {
    
    if (!test()) {
        return TESTS_FAILED;
    }

    int errorCode = NO_ERROR;
    char infixExpression[MAX_STRING_SIZE] = "";
    char postfixExpression[MAX_STRING_SIZE] = "";

    puts("Enter expression in infix form (max 100 symbols): ");
    gets_s(infixExpression, MAX_STRING_SIZE);

    convertExpressionFromInfixFormToPostfix(infixExpression, strlen(infixExpression), postfixExpression, &errorCode);

    if (errorCode == NO_ERROR) {
        printExpressionWithSpaces(postfixExpression, strlen(postfixExpression));
    }
    else if (errorCode == INCORRECT_EXPRESSION) {
        printf("Your expression is incorrect\n");
    }
    else if (errorCode == POINTER_IS_NULL) {
        printf("Passing a null pointer\n");
    }
    else if (errorCode == MEMORY_ALLOCATION_ERROR) {
        printf("Memory allocation error\n");
    }
    else if (errorCode == INVALID_OPERATION_WITH_EMPTY_STACK) {
        printf("Invalid operation with empty stack\n");
    }
    
    return errorCode;
}