#include "CyclicList.h"

#include <stdio.h>
#include <stdbool.h>

int main(void) {
    int errorCode = 0;
    CyclicList* list = createCyclicLIst(&errorCode);
    int step = 10;
    int amountOfPeople = 1;
    for (int i = 1; i <= amountOfPeople; ++i) {
        addElementInCyclicList(list, i, &errorCode);
    }
    printCyclicList(list, &errorCode);

    CyclicListElement* current = getElementInCyclicList(list, 0, &errorCode);
    while (getHeadOfCyclicList(list, &errorCode) != getNextElement(list, getHeadOfCyclicList(list, &errorCode), &errorCode)) {
        deleteElementInCyclicList(list, &current, step, &errorCode);
        printCyclicList(list, &errorCode);
    }
    printf("%d", getElementsValue(list, getHeadOfCyclicList(list, &errorCode), &errorCode));
}