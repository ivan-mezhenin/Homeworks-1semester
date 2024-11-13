#include "/CHomeworks/Stack/intStack/intStack.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define _CRT_SECURE_NO_WARNINGS
#define MAX_STRING_SIZE 150
#define INCORRECT_POSTFIX_FORM -2
#define DIVISION_BY_ZERO -3
#define TESTS_FAILED -4

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
                *errorCode = INCORRECT_POSTFIX_FORM;
                return INCORRECT_POSTFIX_FORM;
            }

            nextSymbol = postfixString[i + 2];

            if (amountOfNumbersInStack == 2) {
                if (nextSymbol == '-' || nextSymbol == '+' || nextSymbol == '*' || nextSymbol == '/') {
                    pushInt(numbers, currentSymbol - '0');
                    ++amountOfNumbersInStack;
                }
                else {
                    *errorCode = INCORRECT_POSTFIX_FORM;
                    return INCORRECT_POSTFIX_FORM;
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
        *errorCode = INCORRECT_POSTFIX_FORM;
        return INCORRECT_POSTFIX_FORM;
    }

    return topIntStack(numbers);
}

bool calculateTheResultOfTheExpressionInPostfixFormCorrectCase(void) {
    const char *testData1 = "5 5 + 4 2 / -";
    int expectedResult1 = 8;
    int errorCode1 = 0;
    int result1 = calculateTheResultOfTheExpressionInPostfixForm(testData1, strlen(testData1), &errorCode1);
    if (result1 != expectedResult1) {
        printf("Test (%s) failed\n", testData1);
        return false;
    }

    const char *testData2 = "3 2 - 3 2 - + 3 2 - + 3 2 - +";
    int expectedResult2 = 4;
    int errorCode2 = 0;
    int result2 = calculateTheResultOfTheExpressionInPostfixForm(testData2, strlen(testData2), &errorCode2);
    if (result2 != expectedResult2) {
        printf("Test (%s) failed\n", testData2);
        return false;
    }

    const char* testData3 = "9 2 3 * - 8 4 / +";
    int expectedResult3 = 5;
    int errorCode3 = 0;
    int result3 = calculateTheResultOfTheExpressionInPostfixForm(testData3, strlen(testData3), &errorCode3);
    if (result3 != expectedResult3) {
        printf("Test (%s) failed\n", testData3);
        return false;
    }

    return true;
}

bool calculateTheResultOfTheExpressionInPostfixFormIncorrectCase(void) {
    const char* testData1 = "5 5 + 4 0 / -";
    int errorCode1 = 0;
    int result1 = calculateTheResultOfTheExpressionInPostfixForm(testData1, strlen(testData1), &errorCode1);
    if (errorCode1 != DIVISION_BY_ZERO) {
        printf("Test (%s) failed\n", testData1);
        return false;
    }

    const char* testData2 = "3 2 2 -";
    int errorCode2 = 0;
    int result2 = calculateTheResultOfTheExpressionInPostfixForm(testData2, strlen(testData2), &errorCode2);
    if (errorCode2 != INCORRECT_POSTFIX_FORM) {
        printf("Test (%s) failed\n", testData2);
        return false;
    }

    const char* testData3 = "9 3 / 5 4 + - 6";
    int errorCode3 = 0;
    int result3 = calculateTheResultOfTheExpressionInPostfixForm(testData3, strlen(testData3), &errorCode3);
    if (errorCode3 != INCORRECT_POSTFIX_FORM) {
        printf("Test (%s) failed\n", testData3);
        return false;
    }

    return true;
}

bool test(void) {
    return calculateTheResultOfTheExpressionInPostfixFormCorrectCase()
        && calculateTheResultOfTheExpressionInPostfixFormIncorrectCase();
}

int main(void) {

    if (!test()) {
        return TESTS_FAILED;
    }

    int errorCode = 0;
    char postfixString[MAX_STRING_SIZE] = "";

    puts("Enter expression in postfix form: ");
    gets_s(postfixString, MAX_STRING_SIZE);

    int result = calculateTheResultOfTheExpressionInPostfixForm(postfixString, strlen(postfixString), &errorCode);

    if (errorCode == 0) {
        printf("Result: %d\n", result);
    }
    else if (errorCode == INCORRECT_POSTFIX_FORM) {
        printf("Your expression is incorrect\n");
        return errorCode;
    }
    else if (errorCode == DIVISION_BY_ZERO) {
        printf("Division by zero\n");
        return errorCode;
    }

    return 0;
}