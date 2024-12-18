#include "/CHomeworks/Stack/intStack/intStack.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_STRING_SIZE 150
#define INCORRECT_POSTFIX_FORM -6
#define DIVISION_BY_ZERO -3
#define TESTS_FAILED -4
#define INVALID_OPERATION_WITH_EMPTY_STACK 1
#define MEMORY_ALLOCATION_ERROR -1
#define POINTER_IS_NULL -2

int operationWithNumbers(IntStack* stack, char operation, int* errorCode) {

    if (operation == '-') {
        int number2 = popInt(stack, errorCode);
        int number1 = popInt(stack, errorCode);
        if (*errorCode != 0) {
            return *errorCode;
        }

        return number1 - number2;
    }

    if (operation == '+') {
        int number2 = popInt(stack, errorCode);
        int number1 = popInt(stack, errorCode);
        if (*errorCode != 0) {
            return *errorCode;
        }

        return number1 + number2;
    }

    if (operation == '*') {
        int number2 = popInt(stack, errorCode);
        int number1 = popInt(stack, errorCode);
        if (*errorCode != 0) {
            return *errorCode;
        }

        return number1 * number2;
    }

    if (operation == '/') {
        int number2 = popInt(stack, errorCode);
        int number1 = popInt(stack, errorCode);
        if (*errorCode != 0) {
            return *errorCode;
        }

        if (number2 == 0) {
            *errorCode = DIVISION_BY_ZERO;
            return DIVISION_BY_ZERO;
        }

        return number1 / number2;
    }
}

int calculateTheResultOfTheExpressionInPostfixForm(char postfixString[], int size,  int* errorCode) {

    IntStack *numbers = createIntStack(errorCode);
    if (*errorCode != 0) {
        return *errorCode;
    }

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

            if (getStackLength(numbers) == 2) {
                if (nextSymbol == '-' || nextSymbol == '+' || nextSymbol == '*' || nextSymbol == '/') {
                    pushInt(numbers, currentSymbol - '0', errorCode);
                    if (*errorCode != 0) {
                        deleteIntStack(numbers);
                        return *errorCode;
                    }
                }
                else {
                    *errorCode = INCORRECT_POSTFIX_FORM;

                    return INCORRECT_POSTFIX_FORM;
                }
            }
            else {
                pushInt(numbers, currentSymbol - '0', errorCode);
                if (*errorCode != 0) {
                    deleteIntStack(numbers);
                    return *errorCode;
                }
            }
        }

        if (currentSymbol == '-' || currentSymbol == '+' || currentSymbol == '*' || currentSymbol == '/') {
            pushInt(numbers, operationWithNumbers(numbers, currentSymbol, errorCode), errorCode);
            if (*errorCode != 0) {
                deleteIntStack(numbers);
                return *errorCode;
            }
        }
    }

    if (getStackLength(numbers) > 1) {
        *errorCode = INCORRECT_POSTFIX_FORM;
        deleteIntStack(numbers);
        return INCORRECT_POSTFIX_FORM;
    }

    int totalResult = topIntStack(numbers, errorCode);
    deleteIntStack(numbers);
    return totalResult;
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
    }
    else if (errorCode == DIVISION_BY_ZERO) {
        printf("Division by zero\n");
    }
    else if (errorCode == INVALID_OPERATION_WITH_EMPTY_STACK) {
        printf("Invalid operation with empty stack\n");
    }
    else if (errorCode == POINTER_IS_NULL) {
        printf("Passing a null pointer\n");
    }
    else if (errorCode == MEMORY_ALLOCATION_ERROR) {
        printf("Memory allocation error\n");
    }

    return errorCode;
}