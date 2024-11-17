#define _CRT_SECURE_NO_WARNINGS

#include "PhoneBook.h"
#include <stdio.h>
#include <stdbool.h>

#define ERROR_OPEN_FILE -1
#define INCORRECT_INPUT_CRITERIA -2

void readDataFromFileToPhoneBook(const char* filename, PhoneBook* phoneBook, int* errorCode, int* size) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        *errorCode = ERROR_OPEN_FILE;
        return;
    }

    int itIsNumber = 0;
    char name[MAX_DATA_SIZE] = "";
    char number[MAX_DATA_SIZE] = "";

    while (!feof(file)) {
        char buffer[MAX_DATA_SIZE];
        const int readBytes = fscanf(file, "%s", buffer);

        if (readBytes < 0) {
            return;
        }

        if (itIsNumber == 0) {
            strcpy(name, buffer);
            itIsNumber = 1;
        }
        else {
            strcpy(number, buffer);
            addNewPhoneBookElement(phoneBook, name, number, errorCode);
            if (*errorCode != 0) {
                return;
            }
            itIsNumber = 0;
            ++(*size);
        }
    }
    fclose(file);
}

void mergeSortSolve(const char *filename,PhoneBook* phoneBook, int* errorCode) {
    int phoneBookSize = 0;
    readDataFromFileToPhoneBook(filename, phoneBook, errorCode, &phoneBookSize);
    if (*errorCode != 0) {
        return;
    }

    printf("Your Phonebook from file %s\n",filename);
    printPhoneBook(phoneBook);

    printf("How would you like to sort phonebook?\n");
    printf("Enter: 1 - by name, 2 - by number\n");

    int sortingCriteria = 0;
    scanf("%d", &sortingCriteria);
    if (sortingCriteria != 1 && sortingCriteria != 2) {
        *errorCode = INCORRECT_INPUT_CRITERIA;
        return INCORRECT_INPUT_CRITERIA;
    }

    mergeSort(phoneBook, 0, phoneBookSize, sortingCriteria);

    printf("Phonebook after sorting:\n");
    printPhoneBook(phoneBook);

    deletePhonebook(phoneBook);
}

//bool mergeSortSolveTests(void) {
//  
//}


int main(void) {
    int errorCode = 0;
    PhoneBook* phoneBook = createPhoneBook(&errorCode);
    if (errorCode == ALLOCATION_PHONEBOOK_ERROR) {
        printf("Error during creation PhoneBook\n");
        return ALLOCATION_PHONEBOOK_ERROR;
    }

    mergeSortSolve("data.txt", phoneBook, &errorCode);

    if (errorCode == INCORRECT_INPUT_CRITERIA) {
        printf("Criteria must be 1 or 2\n");
    }
    else if (errorCode == ERROR_OPEN_FILE) {
        printf("Error during opening file\n");
    }
    else if (errorCode == POINTER_IS_NULL) {
        printf("Error allocation memory\n");
    }

    return 0;
}