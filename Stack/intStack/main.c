#include "intStack.h"

#include <stdio.h>

int main(void) {
    IntStack* stack = createIntStack();
    pushInt(stack, 4);
    pushInt(stack, 6);
    pushInt(stack, 5);
    pushInt(stack, 7);
    printIntStack(stack);
    printf("%d", getAmountOfElementsInIntStack(stack));

}