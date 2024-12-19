#include "SortedListTaskTests.h"
#include "SortedList.h"

#include <stdio.h>
#include <stdbool.h>

bool test1(void) {
    int errorCode = 0;
    SortedList* list = createSortedList(&errorCode);
    if (errorCode != 0) {
        return false;
    }

    addElementInSortedList(list, 214141, &errorCode);
    addElementInSortedList(list, 1, &errorCode);
    addElementInSortedList(list, 0, &errorCode);
    addElementInSortedList(list, 13114, &errorCode);
    addElementInSortedList(list, 2141, &errorCode);
    addElementInSortedList(list, 45, &errorCode);
    addElementInSortedList(list, 10, &errorCode);
    addElementInSortedList(list, 1331, &errorCode);
    addElementInSortedList(list, 1000000, &errorCode);
    if (errorCode != 0) {
        return false;
    }

    bool isTestCompleted = true;
    for (int i = 1; i < getListLength(list); ++i) {
        if (getValueByIndex(list, i - 1) > getValueByIndex(list, i)) {
            isTestCompleted = false;
            break;
        }
    }

    deleteSortedList(list, &errorCode);
    if (errorCode != 0) {
        return false;
    }

    return isTestCompleted;
}

bool test2(void) {
    int errorCode = 0;
    SortedList* list = createSortedList(&errorCode);
    if (errorCode != 0) {
        return false;
    }

    addElementInSortedList(list, 5, &errorCode);
    addElementInSortedList(list, 4, &errorCode);
    addElementInSortedList(list, 6, &errorCode);
    addElementInSortedList(list, 7, &errorCode);
    addElementInSortedList(list, 3, &errorCode);
    addElementInSortedList(list, 2, &errorCode);
    deleteSortedListElement(list, 6, &errorCode);
    addElementInSortedList(list, 10, &errorCode);
    deleteSortedListElement(list, 4, &errorCode);
    deleteSortedListElement(list, 5, &errorCode);

    if (errorCode != 0) {
        return false;
    }

    bool isTestCompleted = true;
    for (int i = 1; i < getListLength(list); ++i) {
        if (getValueByIndex(list, i - 1) > getValueByIndex(list, i)) {
            isTestCompleted = false;
            break;
        }
    }

    deleteSortedList(list, &errorCode);
    if (errorCode != 0) {
        return false;
    }

    return isTestCompleted;
}

bool test(void) {
    bool testCases[2] = { test1(), test2() };
    bool testsCompleted = true;
    for (int i = 0; i < 2; ++i) {
        if (!testCases[i]) {
            printf("Test %d failed\n", i + 1);
            testsCompleted = false;
        }
    }

    return testsCompleted;
}