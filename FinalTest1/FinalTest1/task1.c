#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_DECIMAL_NOTATION_SIZE 20
#define INCORRECT_BINARY_NOTATION -1
#define MEMORY_ALLOCATION_ERROR -2
#define TESTS_FAILED -3

const char* convertFromBinaryToDecimal(const char* binaryNumber, int* errorCode) {
    int decimalNumber = 0;
    char* stringDecimalNumber = malloc(MAX_DECIMAL_NOTATION_SIZE*sizeof(char));
    if (stringDecimalNumber == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }

    for (int i = strlen(binaryNumber) - 1; i >= 0; --i) {
        char currentNumber = binaryNumber[i];
        if (currentNumber != '0' && currentNumber != '1') {
            *errorCode = INCORRECT_BINARY_NOTATION;
            free(stringDecimalNumber);
            return NULL;
        }

        decimalNumber += (currentNumber == '1') ? 1 << (strlen(binaryNumber) - 1 - i) : 0;
    }

    sprintf(stringDecimalNumber, "%d", decimalNumber);
    
    return stringDecimalNumber;
}

bool testCorrectCase1(void) {
    const char* binaryNotation = "10101011";
    int errorCode = 0;
    const char* expectedResult = "171";

    const char* result = convertFromBinaryToDecimal(binaryNotation, &errorCode);
    bool passed = strcmp(result, expectedResult) == 0 && (errorCode == 0);
    
    free(result);
    return passed;
}

bool testCorrectCase2(void) {
    const char* binaryNotation = "0001";
    int errorCode = 0;
    const char* expectedResult = "1";

    const char* result = convertFromBinaryToDecimal(binaryNotation, &errorCode);
    bool passed = strcmp(result, expectedResult) == 0 && (errorCode == 0);

    free(result);
    return passed;
}

bool testCorrectCase3(void) {
    const char* binaryNotation = "1010";
    int errorCode = 0;
    const char* expectedResult = "10";

    const char* result = convertFromBinaryToDecimal(binaryNotation, &errorCode);
    bool passed = strcmp(result, expectedResult) == 0 && (errorCode == 0);

    free(result);
    return passed;
}

bool test(void) {
    return testCorrectCase1() && testCorrectCase2() && testCorrectCase3();
}

int main(void) {
    if (!test()) {
        printf("Tests failed\n");
        return TESTS_FAILED;
    }

    int errorCode = 0;
    const char* binaryNotation = "0101101";

    const char* decimalNotation = convertFromBinaryToDecimal(binaryNotation, &errorCode);
    if (errorCode == INCORRECT_BINARY_NOTATION) {
        printf("Incorrect binary notation\n");
        return errorCode;
    }
    else if (errorCode == MEMORY_ALLOCATION_ERROR) {
        printf("Memory allocation error\n");
        return errorCode;
    }

    printf("Binary notation: %s\n", binaryNotation);
    printf("Decimal notation: %s\n", decimalNotation);

    free(decimalNotation);
    return errorCode;
}