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
        printf("Файла не существует\n");
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
        printf("Файла не существует\n");
        return;
    }

    for (int i = 0; i < lineCount; ++i) {
        fprintf(file, "%s %s\n", directory[i].name, directory[i].number);
    }

    printf("Текущие данные были успешно загружены в файл %s\n", filename);
    fclose(file);
}

void commands(void) {
    printf("0 - выйти\n");
    printf("1 - добавить запись (имя и телефон)\n");
    printf("2 - распечатать все имеющиеся записи\n");
    printf("3 - найти телефон по имени\n");
    printf("4 - найти имя по телефону\n");
    printf("5 - сохранить текущие данные в файл\n");
    printf("\n");
}

void addDataInDirectory(Directory directory[], int currentLineIndex) {

    if (currentLineIndex == 100) {
        printf("В телефонной книге недостаточно места для нового контакта!\n");
        return;
    }

    printf("Введите имя: ");
    scanf("%s", directory[currentLineIndex].name);
    printf("Введите номер телефона: ");
    scanf("%s", directory[currentLineIndex].number);
    printf("Добавление нового контакта прошло успешно\n");
}

void printDirectory(Directory directory[], int currentLineIndex) {
    if (currentLineIndex == 0) {
        printf("В телефонной книге отсутствуют контакты\n");
        return;
    }

    for (int i = 0; i < currentLineIndex; ++i) {
        printf("Имя: %s Номер: %s\n", directory[i].name, directory[i].number);
    }
}

char* findNumber(char name[],Directory directory[], int lineCount) {
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
            printf("Введена некорректная команда. Попробуйте еще раз!\n");
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
            printf("Введите имя: ");
            scanf("%s", name);

            char* number = findNumber(name, directory,lineCount);
            if (strlen(number) != 0) {
                printf("По имени %s был найден телефон: %s\n", name, number);
            }
            else {
                printf("Телефон не найден\n");
            }
        }
        else if (currentCommand == 4) {
            const char number[100];
            printf("Введите номер: ");
            scanf("%s", number);

            char* name = findName(number, directory, lineCount);
            if (strlen(name) != 0) {
                printf("По номер %s было найдено имя: %s\n", number, name);
            }
            else {
                printf("Имя не найдено\n");
            }
        }
        else if (currentCommand == 5) {
            addDataInFile("data.txt", directory, lineCount);
        }
    }


}

int main(void) {
    setlocale(LC_ALL, "Russian");
    solve();

    return 0;
}