#include "charStack.h"

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"

#define _CRT_SECURE_NO_WARNINGS
#define MAX_STRING_LENGTH 100
#define INPUT_ERROR -1
#define TOP_OF_STACK_IS_NULL '\0'

char pairedBracket(char bracket) {

    if (bracket == ')') {
        return '(';
    }
    if (bracket == '}') {
        return '{';
    }
    if (bracket == ']') {
        return '[';
    }
}

bool isBracketSequenceCorrect(char secuence[], int length, int *errorCode) {
    CharStack* bracketStack = createCharStack();

    pushChar(bracketStack, secuence[0]);

    for (int i = 1; i < length; ++i) {
        char rightBracket = secuence[i];
        if (rightBracket == '(' || rightBracket == '[' || rightBracket == '{') {
            pushChar(bracketStack, rightBracket);
        }
        else if (rightBracket == '}' || rightBracket == ']' || rightBracket == ')') {
            char leftBracket = pairedBracket(secuence[i], errorCode);
            char currentTopStackElement = popChar(bracketStack);
            if (currentTopStackElement != leftBracket) {
                return false;
            }
        }
        else {
            *errorCode = INPUT_ERROR;
            return false;
        }
    }
    return topCharStack(bracketStack) == TOP_OF_STACK_IS_NULL;

}   

int main(void) {

    char secuence[MAX_STRING_LENGTH] = "";
    int errorCode = 0;
    puts("Inter bracket sequence: ");
    gets_s(secuence, MAX_STRING_LENGTH);
    const int secuenceLength = strlen(secuence);

    if (isBracketSequenceCorrect(secuence, secuenceLength, &errorCode)) {
        printf("Balance\n");
    }
    else {
        if (errorCode == INPUT_ERROR) {
            printf("Sequence must consist of \"({[)}]\"");
        }
        else {
            printf("No balance");
        }
    }
}