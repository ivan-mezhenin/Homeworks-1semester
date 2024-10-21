#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>

typedef struct {
    char name[100];
    char number[100];
} Directory;

void fileReadData(const char fileName[], Directory directory[], int* currentLineIndex) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("����� �� ����������\n");
        return;
    }
    int itIsNumber = 0;
    while (!feof(file)) {
        char buffer[100];
        const int readBytes = fscanf(file, "%s", buffer);
        if (readBytes < 0) {
            break;
        }
        if (itIsNumber == 0) {
            strcpy(directory[*currentLineIndex].name, buffer);
            itIsNumber = 1;
        }
        else {
            strcpy(directory[*currentLineIndex].number, buffer);
            itIsNumber = 0;
            ++*currentLineIndex;
        }
        

    }
    fclose(file);
}

void commands(void) {
    printf("0 - �����\n");
    printf("1 - �������� ������ (��� � �������)\n");
    printf("2 - ����������� ��� ��������� ������\n");
    printf("3 - ����� ������� �� �����\n");
    printf("4 - ����� ��� �� ��������\n");
    printf("5 - ��������� ������� ������ � ����\n");
    printf("\n");
}

void addDataInFile(Directory directory[], int currentLineIndex) {

    if (currentLineIndex == 100) {
        printf("� ���������� ����� ������������ ����� ��� ������ ��������!\n");
        return;
    }

    printf("������� ���: ");
    scanf("%s", directory[currentLineIndex].name);
    printf("������� ����� ��������: ");
    scanf("%s", directory[currentLineIndex].number);
    printf("���������� ������ �������� ������ �������\n");
}

void printDirectory(Directory directory[], int currentLineIndex) {
    setlocale(LC_ALL, "Russian");
    if (currentLineIndex == 0) {
        printf("� ���������� ����� ����������� ��������\n");
        return;
    }

    for (int i = 0; i < currentLineIndex; ++i) {
        printf("���: %s �����: %s\n", directory[i].name, directory[i].number);
    }
}

void solve(void) {
    Directory directory[100];
    int lineCount = 0;
    const short int  currentCommand = -1;

    fileReadData("data.txt", directory, &lineCount);
    commands();

    while (currentCommand != 0) {
        scanf("%hd", &currentCommand);

        if (currentCommand < 0 || currentCommand > 5) {
            printf("������� ������������ �������. ���������� ��� ���!\n");
            continue;
        }

        if (currentCommand == 0) {
            return;
        }
        else if (currentCommand == 1) {
            addDataInFile(directory, lineCount);
            ++lineCount;
        }
        else if (currentCommand == 2) {
            printDirectory(directory, lineCount);
        }
    }


}

int main(void) {
    setlocale(LC_ALL, "Russian");
    solve();

    return 0;
}