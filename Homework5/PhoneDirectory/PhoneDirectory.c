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

void addDataInFile(char filename[], Directory directory[], int lineCount) {
    FILE* file = fopen(filename, "w");

    if (file == NULL) {
        printf("����� �� ����������\n");
        return;
    }

    for (int i = 0; i < lineCount; ++i) {
        fprintf(file, "%s %s\n", directory[i].name, directory[i].number);
    }

    printf("������� ������ ���� ������� ��������� � ���� %s\n", filename);
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

void addDataInDirectory(Directory directory[], int currentLineIndex) {

    if (currentLineIndex == 100) {
        printf("� ���������� ����� ������������ ����� ��� ������ ��������!\n");
        return;
    }

    printf("������� ���: ");
    scanf("%s", &directory[currentLineIndex].name);

    printf("������� ����� ��������: ");
    scanf("%s", &directory[currentLineIndex].number);

    printf("���������� ������ �������� ������ �������\n");
}

void printDirectory(Directory directory[], int currentLineIndex) {
    if (currentLineIndex == 0) {
        printf("� ���������� ����� ����������� ��������\n");
        return;
    }

    for (int i = 0; i < currentLineIndex; ++i) {
        printf("���: %s �����: %s\n", directory[i].name, directory[i].number);
    }
}

char* findNumber(char name[], Directory directory[], int lineCount) {
    for (int i = 0; i < lineCount; ++i) {
        if (strcmp(name, directory[i].name) == 0) {
            return directory[i].number;
        }
    }

    return "";
}

char* findName(char number[], Directory directory[], int lineCount) {
    for (int i = 0; i < lineCount; ++i) {
        if (strcmp(number, directory[i].number) == 0) {
            return directory[i].name;
        }
    }

    return "";
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
            addDataInDirectory(directory, lineCount);
            ++lineCount;
        }
        else if (currentCommand == 2) {
            printDirectory(directory, lineCount);
        }
        else if (currentCommand == 3) {
            const char name[100];

            printf("������� ���: ");
            scanf("%s", &name);

            char* number = findNumber(name, directory, lineCount);
            if (strlen(number) != 0) {
                printf("�� ����� %s ��� ������ �������: %s\n", name, number);
            }
            else {
                printf("������� �� ������\n");
            }
        }
        else if (currentCommand == 4) {
            const char number[100];

            printf("������� �����: ");
            scanf("%s", &number);

            char* name = findName(number, directory, lineCount);
            if (strlen(name) != 0) {
                printf("�� ����� %s ���� ������� ���: %s\n", number, name);
            }
            else {
                printf("��� �� �������\n");
            }
        }
        else if (currentCommand == 5) {
            addDataInFile("data.txt", directory, lineCount);
        }
    }


}

bool fileReadDataTest(Directory testDirectory[], int lineCount) {
    if (lineCount != 2) {
        return false;
    }

    return strcmp(testDirectory[0].name, "Andrey") == 0 && strcmp(testDirectory[0].number, "89659155656") == 0 &&
        strcmp(testDirectory[1].name, "Nikita") == 0 && strcmp(testDirectory[1].number, "89632565349") == 0;
}

bool findNumberTest(Directory testDirectory[], int lineCount) {
    return (strcmp(findNumber("Nikita", testDirectory, lineCount), "89632565349") == 0 &&
        strcmp(findNumber("Andrey", testDirectory, lineCount), "89659155656") == 0);
}

bool findNameTest(Directory testDirectory[], int lineCount) {
    return (strcmp(findName("89632565349", testDirectory, lineCount), "Nikita") == 0 &&
        strcmp(findName("89659155656", testDirectory, lineCount), "Andrey") == 0);
}

bool mainTest(void) {
    Directory testDirectory[100];
    int lineCount = 0;

    fileReadData("testdata.txt", testDirectory, &lineCount);
    if (!fileReadDataTest(testDirectory, lineCount)) {
        printf("������ � ������� ReadDataTest\n");
        return false;
    }

    if (!findNameTest(testDirectory, lineCount)) {
        printf("������ � ������� findNameTest\n");
        return false;
    }

    if (!findNumberTest(testDirectory, lineCount)) {
        printf("������ � ������� findNumberTest\n");
        return false;
    }

    return true;
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