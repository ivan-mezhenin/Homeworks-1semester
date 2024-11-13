#include "/CHomeworks/Stack/intStack/intStack.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define _CRT_SECURE_NO_WARNINGS
#define MAX_STRING_SIZE 150
#define INCORRECT_STRING -2
#define DIVISION_BY_ZERO -3

int operationWithNumbers(IntStack* stack, char operation, int* errorCode) {

    if (operation == '-') {
        int number1 = popInt(stack);
        int number2 = popInt(stack);
        return number2 - number1;
    }

    if (operation == '+') {
        int number1 = popInt(stack);
        int number2 = popInt(stack);
        return number2 + number1;
    }

    if (operation == '*') {
        int number1 = popInt(stack);
        int number2 = popInt(stack);
        return number2 * number1;
    }

    if (operation == '/') {
        int number1 = popInt(stack);
        int number2 = popInt(stack);

        if (number1 == 0) {
            *errorCode = DIVISION_BY_ZERO;
            return DIVISION_BY_ZERO;
        }

        return number2 / number1;
    }

}

int calculateTheResultOfTheExpressionInPostfixForm(char postfixString[], int size,  int* errorCode) {

    IntStack *numbers = createIntStack();
    int amountOfNumbersInStack = 0;
    char currentSymbol = ' ';
    char nextSymbol = ' ';

    for (int i = 0; i < size; ++i) {
        currentSymbol = postfixString[i];

        if (currentSymbol == ' ') {
            continue;
        }

        if (currentSymbol <= '9' && currentSymbol >= '0') {

            if (i == size - 1){
                *errorCode = INCORRECT_STRING;
                return INCORRECT_STRING;
            }

            nextSymbol = postfixString[i + 2];
            if (amountOfNumbersInStack == 2) {
                if (nextSymbol == '-' || nextSymbol == '+' || nextSymbol == '*' || nextSymbol == '/') {
                    pushInt(numbers, currentSymbol - '0');
                    ++amountOfNumbersInStack;
                }
                else {
                    *errorCode = INCORRECT_STRING;
                    return INCORRECT_STRING;
                }
            }
            else {
                pushInt(numbers, currentSymbol - '0');
                ++amountOfNumbersInStack;
            }
            
        }

        if (currentSymbol == '-' || currentSymbol == '+' || currentSymbol == '*' || currentSymbol == '/') {

            pushInt(numbers, operationWithNumbers(numbers, currentSymbol, errorCode));
            if (*errorCode != 0) {
                return *errorCode;
            }
            --amountOfNumbersInStack;
        }
    }

    if (getAmountOfElementsInIntStack(numbers) > 1) {
        *errorCode = INCORRECT_STRING;
        return INCORRECT_STRING;
    }

    return topIntStack(numbers);
}

int main(void) {

    int errorCode = 0;
    char postfixString[MAX_STRING_SIZE] = "";

    puts("Enter expression in postfix form: ");
    gets_s(postfixString, MAX_STRING_SIZE);
    int result = calculateTheResultOfTheExpressionInPostfixForm(postfixString, strlen(postfixString), & errorCode);

    if (errorCode == 0) {
        printf("Result: %d\n", result);
    }
    else if (errorCode == INCORRECT_STRING) {
        printf("Your expression is incorrect\n");
        return errorCode;
    }
    else if (errorCode == DIVISION_BY_ZERO) {
        printf("Division by zero\n");
        return errorCode;
    }


    return 0;
}