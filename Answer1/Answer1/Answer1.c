#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

bool Palindrom(char word[]) {
    int wordIndex = 0;
    char* wordWithoutSpaces = malloc(strlen(word) * sizeof(char));
    int wordLength = strlen(word);
    int spaceCounter = 0;

    for (int i = 0; i < wordLength; ++i) {
        if (word[i] != ' '){
            wordWithoutSpaces[wordIndex] = word[i];
            ++wordIndex;
        }
        else {
            ++spaceCounter;
        }
    }

    wordLength -= spaceCounter;

    for (int i = 0; i < wordLength / 2; ++i) {
        if (wordWithoutSpaces[i] != wordWithoutSpaces[wordLength - i - 1]) {
            free(wordWithoutSpaces);
            return false;
        }
    }

    free(wordWithoutSpaces);
    return true;
}

bool testCorrectCase() {
    return Palindrom("коту скоро сорок суток");
}

bool testIncorrectCase() {
    return !Palindrom("я хожу в школу");
}

int main(void) {
    setlocale(LC_ALL, "Rus");
    if (!testCorrectCase() || !testIncorrectCase()) {
        printf("Tests failed!!!");
        return true;
    }

    char* word = "я иду с мечем судия";

    printf("Sentence '");
    for (int i = 0; i < strlen(word); ++i) {
        printf("%c", word[i]);
    }
    printf("' ");
    if (Palindrom(word)) {
        printf("is Palindrom\n");
    }
    else {
        printf("is not Palindrom");
    }
}