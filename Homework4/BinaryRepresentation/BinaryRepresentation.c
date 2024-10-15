#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdbool.h>

#define BINARY_NUMBER_LENGTH 8*sizeof(int)

void convertToBinary(int number, int binaryNumber[BINARY_NUMBER_LENGTH]) {
    int bit = 0b00000001;

    for (int i = BINARY_NUMBER_LENGTH - 1; i >= 0; --i) {
        binaryNumber[i] = (number & bit) ? 1 : 0;
        bit = bit << 1;
    }
}

void binaryNumberOutput(int binaryNumber[]) {
    for (int i = 0; i < BINARY_NUMBER_LENGTH; ++i)
    {
        printf("%d", binaryNumber[i]);
    }

    printf("\n");
}

void binaryAddition(int firstNumber[], int secondNumber[], int binarySum[]) {
    int memorizedNumberOne = 0;
    
    for (int i = BINARY_NUMBER_LENGTH - 1; i >= 0; --i) {
        binarySum[i] = memorizedNumberOne + firstNumber[i] + secondNumber[i];
        memorizedNumberOne = 0;
        if (binarySum[i] > 1) {
            memorizedNumberOne = 1;
            binarySum[i] -= 2;
        }
    }
}

int convertFromBinaryToDecimal(int binaryNumber[]) {
    int decimalNumber = 0;

    for (int i = BINARY_NUMBER_LENGTH - 1; i >= 0; --i) {
        decimalNumber += (binaryNumber[i] == 1) ? 1 << (BINARY_NUMBER_LENGTH - 1 - i) : 0;
    }

    return decimalNumber;
}

void binaryRepresentationSolve(int firstNumber, int secondNumber) {
    int firstBinaryNumber[BINARY_NUMBER_LENGTH] = { 0 };
    int secondBinaryNumber[BINARY_NUMBER_LENGTH] = { 0 };

    convertToBinary(firstNumber, firstBinaryNumber);
    convertToBinary(secondNumber, secondBinaryNumber);
    
    printf("Число %d в дополнительном коде: ", firstNumber);
    binaryNumberOutput(firstBinaryNumber);
    printf("Число %d в дополнительном коде: ", secondNumber);
    binaryNumberOutput(secondBinaryNumber);

    int binarySum[BINARY_NUMBER_LENGTH] = { 0 };
    binaryAddition(firstBinaryNumber, secondBinaryNumber, binarySum);
    printf("Сумма чисел в дополнительном коде: ");
    binaryNumberOutput(binarySum);
    
    int decimalSum = convertFromBinaryToDecimal(binarySum);
    printf("Сумма чисел в десятичной системе счисления: %d", decimalSum);
}

bool TwoArraysAreEqual(int array1[], int array2[], int arrayLength) {
    for (int i = 0; i < arrayLength; ++i) {
        if (array1[i] != array2[i]) {
            return false;
        }
    }

    return true;
}

bool convertToBinaryTest() {
    int testNumber1 = 37;
    int testNumber2 = -29;
    int binaryNumber1[BINARY_NUMBER_LENGTH] = { 0 };
    int binaryNumber2[BINARY_NUMBER_LENGTH] = { 0 };
    int correctBinaryNumber1[BINARY_NUMBER_LENGTH] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1 };
    int correctBinaryNumber2[BINARY_NUMBER_LENGTH] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1 };

    convertToBinary(testNumber1, binaryNumber1);
    convertToBinary(testNumber2, binaryNumber2);

    return TwoArraysAreEqual(binaryNumber1, correctBinaryNumber1, BINARY_NUMBER_LENGTH) && TwoArraysAreEqual(binaryNumber2, correctBinaryNumber2, BINARY_NUMBER_LENGTH);
}

bool convertFromBinaryToDecimalTest() {
    int binaryNumber1[BINARY_NUMBER_LENGTH] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1 };
    int binaryNumber2[BINARY_NUMBER_LENGTH] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1 };
    int decimalNumber1 = convertFromBinaryToDecimal(binaryNumber1);
    int decimalNumber2 = convertFromBinaryToDecimal(binaryNumber2);
    int correctNumber1 = 37;
    int correctNumber2 = -29;

    return (decimalNumber1 == correctNumber1) && (decimalNumber2 == correctNumber2);
}

bool binaryAdditionTest() {
    int testNumber1 = 37;
    int testNumber2 = -29;
    int binaryNumber1[BINARY_NUMBER_LENGTH] = { 0 };
    int binaryNumber2[BINARY_NUMBER_LENGTH] = { 0 };
    int correctBinarySum[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 };
    int binarySum[BINARY_NUMBER_LENGTH] = { 0 };

    convertToBinary(testNumber1, binaryNumber1);
    convertToBinary(testNumber2, binaryNumber2);
    binaryAddition(binaryNumber1, binaryNumber2, binarySum);

    if (!TwoArraysAreEqual(correctBinarySum,binarySum,BINARY_NUMBER_LENGTH)) {
        printf("Test from numbers %d and %d is failed", testNumber1,testNumber2);
        return false;
    }

    testNumber1 = -15;
    testNumber2 = -14;
    int binaryNumber3[BINARY_NUMBER_LENGTH] = { 0 };
    int binaryNumber4[BINARY_NUMBER_LENGTH] = { 0 };
    int correctBinarySum2[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1};
    int binarySum2[BINARY_NUMBER_LENGTH] = { 0 };

    convertToBinary(testNumber1, binaryNumber3);
    convertToBinary(testNumber2, binaryNumber4);
    binaryAddition(binaryNumber3, binaryNumber4, binarySum2);

    if (!TwoArraysAreEqual(correctBinarySum2, binarySum2, BINARY_NUMBER_LENGTH)) {
        printf("Test from numbers %d and %d is failed", testNumber1, testNumber2);
        return false;
    }

    return true;
}

bool mainTest() {
    return convertToBinaryTest() && convertFromBinaryToDecimalTest() && binaryAdditionTest();
}

int main(void) {
    setlocale(LC_ALL, "Rus");

    if (!mainTest()) {
        printf("Tests failed!!!\n");
        return 0;
    }

    int firstNumber = 0;
    int secondNumber = 0;

    printf("Введите 2 числа:\n");
    scanf("%d %d", &firstNumber, &secondNumber);

    binaryRepresentationSolve(firstNumber, secondNumber);
}