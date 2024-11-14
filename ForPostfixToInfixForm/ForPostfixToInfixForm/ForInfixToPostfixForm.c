#include "/CHomeworks/Stack/charStack/charStack.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define _CRT_SECURE_NO_WARNINGS
#define MAX_STRING_SIZE 101
#define INCORRECT_EXPRESSION -1

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
    CharStack* signs = createCharStack();
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
            pushChar(signs, currentSymbol);
        }
        else if (isOperation(currentSymbol)) {
            while (topCharStack(signs) != '\0' &&
                (getOperationPrecedence(topCharStack(signs)) >= getOperationPrecedence(currentSymbol))) {
                postfixExpression[postfixExpressionIndex++] = popChar(signs);
            }
            pushChar(signs, currentSymbol);
        }
        else if (currentSymbol == ')') {
            while (topCharStack(signs) != '\0' && topCharStack(signs) != '(') {
                postfixExpression[postfixExpressionIndex++] = popChar(signs);
            }
            popChar(signs);
        }
        else {
            *errorCode = INCORRECT_EXPRESSION;
            return;
        }
    }

    while (topCharStack(signs) != '\0') {
        postfixExpression[postfixExpressionIndex++] = popChar(signs);
    }
}

int main(void) {
    
    int errorCode = 0;
    char infixExpression[MAX_STRING_SIZE] = "";
    char postfixExpression[MAX_STRING_SIZE] = "";

    puts("Enter expression in infix form (max 100 symbols): ");
    gets_s(infixExpression, MAX_STRING_SIZE);

    convertExpressionFromInfixFormToPostfix(infixExpression, strlen(infixExpression), postfixExpression, &errorCode);
    if (errorCode == 0) {
        printf("%s", postfixExpression);
    }
    else if (errorCode == INCORRECT_EXPRESSION) {
        printf("Your expression is incorrect\n");
        return INCORRECT_EXPRESSION;
    }
    

}