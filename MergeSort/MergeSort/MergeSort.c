#define _CRT_SECURE_NO_WARNINGS

#include "PhoneBook.h"
#include <stdio.h>
#include <stdbool.h>

#define ERROR_OPEN_FILE -1
#define INCORRECT_INPUT_CRITERIA -2
#define TESTS_FAILED -3
#define SORTING_BY_NAMES 1
#define SORTING_BY_NUMBERS 2

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

bool mergeSortSolveTests(void) {
    int errorCode1 = 0;
    int phoneBookLength1 = 0;
    PhoneBook* testPhoneBook1 = createPhoneBook(&errorCode1);
    int criteria1 = SORTING_BY_NUMBERS;

    readDataFromFileToPhoneBook("testdata1.txt", testPhoneBook1, &errorCode1, &phoneBookLength1);
    mergeSort(testPhoneBook1, 0, phoneBookLength1, criteria1);

    if (!isPhoneBookSortedByCriteria(testPhoneBook1, criteria1, errorCode1) || errorCode1 != 0) {
        printf("Test with data from testdata1.txt failed\n");
        deletePhonebook(testPhoneBook1);
        return false;
    }

    int errorCode2 = 0;
    int phoneBookLength2 = 0;
    PhoneBook* testPhoneBook2 = createPhoneBook(&errorCode2);
    int criteria2 = SORTING_BY_NAMES;

    readDataFromFileToPhoneBook("testdata2.txt", testPhoneBook2, &errorCode2, &phoneBookLength2);
    mergeSort(testPhoneBook2, 0, phoneBookLength2, criteria2);

    if (!isPhoneBookSortedByCriteria(testPhoneBook2, criteria2, errorCode2) || errorCode2 != 0) {
        printf("Test with data from testdata2.txt failed\n");
        deletePhonebook(testPhoneBook2);
        return false;
    }

    int errorCode3 = 0;
    int phoneBookLength3 = 0;
    PhoneBook* testPhoneBook3 = createPhoneBook(&errorCode3);
    int criteria3 = SORTING_BY_NUMBERS;

    readDataFromFileToPhoneBook("testdata3.txt", testPhoneBook3, &errorCode3, &phoneBookLength3);
    mergeSort(testPhoneBook3, 0, phoneBookLength3, criteria3);

    if (!isPhoneBookSortedByCriteria(testPhoneBook3, criteria3, errorCode3) || errorCode3 != 0) {
        printf("Test with data from testdata3.txt failed\n");
        deletePhonebook(testPhoneBook3);
        return false;
    }

    deletePhonebook(testPhoneBook1);
    deletePhonebook(testPhoneBook2);
    deletePhonebook(testPhoneBook3);

    return true;
}


int main(void) {
    if (!mergeSortSolveTests()) {
        return TESTS_FAILED;
    }

    bool k = mergeSortSolveTests();
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