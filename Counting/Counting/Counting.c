#define _CRT_SECURE_NO_WARNINGS

#include "CyclicList.h"

#include <stdio.h>
#include <stdbool.h>

#define TESTS_FAILED -155

int getLastWarriorCounting(const int amount, const int step, int* errorCode) {
    CyclicList* list = createCyclicList(errorCode);
    if (*errorCode != 0) {
        deleteCyclicList(list, errorCode);
        return *errorCode;
    }

    for (int i = 1; i <= amount; ++i) {
        addElementInCyclicList(list, i, errorCode);
        if (*errorCode != 0) {
            deleteCyclicList(list, errorCode);
            return *errorCode;
        }
    }

    CyclicListElement* current = getElementInCyclicList(list, 0, errorCode);
    if (*errorCode != 0) {
        deleteCyclicList(list, errorCode);
        return *errorCode;
    }

    while (current != getNextElement(list, current, errorCode)) {
        deleteElementInCyclicList(list, &current, step, errorCode);
        if (*errorCode != 0) {
            deleteCyclicList(list, errorCode);
            return *errorCode;
        }
    }

    const int lastWarrior = getElementsValue(list, current, errorCode);
    if (*errorCode != 0) {
        deleteCyclicList(list, errorCode);
        return *errorCode;
    }

    deleteCyclicList(list, errorCode);
    if (*errorCode != 0) {
        return *errorCode;
    }

    return lastWarrior;
}

bool test(void) {
    int errorCode1 = 0;
    int amountOfPeople1 = 1;
    int step1 = 17;
    int expectedResult1 = 1;
    int result1 = getLastWarriorCounting(amountOfPeople1, step1, &errorCode1);
    if (errorCode1 != 0 || result1 != expectedResult1) {
        printf("Test with n = %d, m = %d is failed\n", amountOfPeople1, step1);
        return false;
    }

    int errorCode2 = 0;
    int amountOfPeople2 = 1000;
    int step2 = 17;
    int expectedResult2 = 431;
    int result2 = getLastWarriorCounting(amountOfPeople2, step2, &errorCode2);
    if (errorCode1 != 0 || result2 != expectedResult2) {
        printf("Test with n = %d, m = %d is failed\n", amountOfPeople2, step2);
        return false;
    }
    
    int errorCode3 = 0;
    int amountOfPeople3 = 1214;
    int step3 = 416;
    int expectedResult3 = 743;
    int result3 = getLastWarriorCounting(amountOfPeople3, step3, &errorCode3);
    if (errorCode3 != 0 || result3 != expectedResult3) {
        printf("Test with n = %d, m = %d is failed\n", amountOfPeople3, step3);
        return false;
    }

    return true;
}

int main(void) {
    if (!test()) {
        return TESTS_FAILED;
    }

    int errorCode = 0;
    int step = 0;
    int amountOfPeople = 0;

    printf("Enter n: ");
    scanf("%d", &amountOfPeople);
    printf("Enter m: ");
    scanf("%d", &step);

    const int lastWarrior = getLastWarriorCounting(amountOfPeople, step, &errorCode);

    if (errorCode == MEMORY_ERROR) {
        printf("Memory allocation error\n");
        return MEMORY_ERROR;
    }
    else if (errorCode == LIST_POINTER_IS_NULL) {
        printf("Passing a null pointer\n");
        return LIST_POINTER_IS_NULL;
    }
    else {
        printf("Last alive warrior's position from beginning: %d", lastWarrior);
    }
    
    return 0;
}