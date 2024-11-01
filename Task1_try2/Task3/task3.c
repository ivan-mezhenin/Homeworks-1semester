#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>

void fileReadData(const char fileName[], char *data[]) {
    FILE* file = fopen(fileName, "r");

    if (file == NULL) {
        printf("Файл не найден\n");
        return;
    }

    int linesRead = 0;
    while (!feof(file)) {
        char *buffer = malloc(sizeof(char) * 100);
        const int readBytes = fscanf(file, "%s", buffer);
        if (readBytes < 0) {
            break;
        }
        strcpy(data, buffer);

    }

    fclose(file);
}

void removingSequencesOfDuplicateCharacters(char data[], char dataWithoutRepetitiveSequences[]) {
    int indexAnswerData = 1;
    char currentChar = data[0];

    dataWithoutRepetitiveSequences[0] = data[0];

    for (int i = 1; i < strlen(data); ++i) {
        if (data[i] != currentChar) {
            dataWithoutRepetitiveSequences[indexAnswerData] = data[i];
            currentChar = data[i];
            ++indexAnswerData;
        }
    }
}

void solve() {
    char data[1000] = {0};

    fileReadData("data.txt", data);

    char answerData[1000] = { 0 };
    
    removingSequencesOfDuplicateCharacters(data, answerData);

    printf("String from file: \n%s\n", data);
    printf("String without repetitive sequences: \n%s\n", answerData);
}

bool mainTest() {
    char data[1000] = { 0 };

    fileReadData("testData.txt", data);

    char testAnswerData[1000] = { 0 };

    const char *groundTruthArray = "abc";
    removingSequencesOfDuplicateCharacters(data, testAnswerData);

    if (strcmp(groundTruthArray, testAnswerData) == 0) {
        return true;
    }

    return false;
}

int main(void) {
    setlocale(LC_ALL, "Russian");

    if (!mainTest()) {
        printf("Tests failed!!!\n");
        return;
    }

    solve();
    return 0;
}