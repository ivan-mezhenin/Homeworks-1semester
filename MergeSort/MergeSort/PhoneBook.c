#include "PhoneBook.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS

typedef struct PhoneBookElement {
    char name[MAX_DATA_SIZE];
    char number[MAX_DATA_SIZE];
    struct PhoneBookElement* next;
} PhoneBookElement;

typedef struct PhoneBook {
    PhoneBookElement* head;
} PhoneBook;

PhoneBook* createPhoneBook(int* errorCode) {
    PhoneBook* phoneBook = calloc(1, sizeof(PhoneBook));
    if (phoneBook == NULL) {
        *errorCode = ALLOCATION_PHONEBOOK_ERROR;
        return NULL;
    }

    return phoneBook;
}

bool isPhoneBookEmpty(PhoneBook* phoneBook, int* errorCode) {
    if (phoneBook == NULL) {
        *errorCode = POINTER_IS_NULL;
        return true;
    }

    return phoneBook->head == NULL;
}

PhoneBookElement* lastPhoneBookElement(PhoneBook* phonebook, int* errorCode) {
    if (phonebook == NULL || phonebook->head == NULL) {
        *errorCode = EMPTY_PHONEBOOK;
        return NULL;
    }

    PhoneBookElement* currentElement = phonebook->head;
    while (currentElement->next != NULL) {
        currentElement = currentElement->next;
    }

    return currentElement;
}

void addNewPhoneBookElement(PhoneBook* phoneBook, const char* name, const char* number, int* errorCode) {
    PhoneBookElement* newElement = calloc(1, sizeof(PhoneBookElement));
    if (newElement == NULL) {
        *errorCode = POINTER_IS_NULL;
        return;
    }

    strcpy_s(newElement->name, 100, name);
    strcpy_s(newElement->number, 100, number);

    if (isPhoneBookEmpty(phoneBook, errorCode)) {
        phoneBook->head = newElement;
    }
    else {
        PhoneBookElement* lastElement = lastPhoneBookElement(phoneBook, errorCode);
        lastElement->next = newElement;
    }

    newElement->next = NULL;
}

void printPhoneBook(PhoneBook* phoneBook) {
    PhoneBookElement* currentElement = phoneBook->head;

    if (currentElement == NULL) {
        printf("PhoneBook is empty");
    }
    else {
        while (currentElement != NULL) {
            printf("%s : %s \n", currentElement->name, currentElement->number);
            currentElement = currentElement->next;
        }
    }
    printf("\n");
}

void deletePhonebook(PhoneBook* phonebook) {
    if (phonebook == NULL) {
        return;
    }

    int errorCode = 0;
    while (!isPhoneBookEmpty(phonebook, &errorCode)) {
        if (errorCode != 0) {
            break;
        }

        PhoneBookElement* currentElement = phonebook->head;
        phonebook->head = phonebook->head->next;
        free(currentElement);
    }

    free(phonebook);
}

int comparisonPhoneBookElements(PhoneBookElement* left, PhoneBookElement* right, const int parameter) {
    return (parameter == 1) ? strcmp(left->name, right->name) : strcmp(left->number, right->number);
}

void merge(PhoneBook* phoneBook, int leftBorderIndex, int rightBorderIndex, const int parameter) {

    int middleIndex = (leftBorderIndex + rightBorderIndex) / 2;
    int leftIndex = leftBorderIndex;
    int rightIndex = middleIndex;
    PhoneBookElement* current = phoneBook->head;

    for (int i = 0; i < leftIndex; ++i) {
        current = current->next;
    }

    PhoneBookElement* leftSubPhoneBookELement = current;
    PhoneBookElement* rightSubPhoneBookElement = NULL;

    for (int i = leftIndex; i < middleIndex; ++i) {
        current = current->next;
    }

    rightSubPhoneBookElement = current;
    int errorCode3 = 0;
    PhoneBook* sortedPhoneBook = createPhoneBook(&errorCode3);

    while (leftIndex < middleIndex && rightIndex < rightBorderIndex) {
        if (comparisonPhoneBookElements(leftSubPhoneBookELement, rightSubPhoneBookElement, parameter) > 0) {
            addNewPhoneBookElement(sortedPhoneBook, rightSubPhoneBookElement->name, rightSubPhoneBookElement->number, &errorCode3);
            ++rightIndex;
            rightSubPhoneBookElement= rightSubPhoneBookElement->next;
        }
        else {
            addNewPhoneBookElement(sortedPhoneBook, leftSubPhoneBookELement->name, leftSubPhoneBookELement->number, &errorCode3);
            ++leftIndex;
            leftSubPhoneBookELement = leftSubPhoneBookELement->next;
        }
    }

    while (leftIndex < middleIndex) {
        addNewPhoneBookElement(sortedPhoneBook, leftSubPhoneBookELement->name, leftSubPhoneBookELement->number, &errorCode3);
        ++leftIndex;
        leftSubPhoneBookELement = leftSubPhoneBookELement->next;
    }

    while (rightIndex < rightBorderIndex) {
        addNewPhoneBookElement(sortedPhoneBook, rightSubPhoneBookElement->name, rightSubPhoneBookElement->number, &errorCode3);
        ++rightIndex;
        rightSubPhoneBookElement= rightSubPhoneBookElement->next;
    }

    current = phoneBook->head;
    for (int i = 0; i < leftBorderIndex; ++i) {
        current = current->next;
    }

    for (int i = leftBorderIndex; i < rightBorderIndex; ++i) {
        strcpy_s(current->name, MAX_DATA_SIZE, sortedPhoneBook->head->name);
        strcpy_s(current->number, MAX_DATA_SIZE, sortedPhoneBook->head->number);

        current = current->next;
        PhoneBookElement* sortedPhoneBookCurrentHead = sortedPhoneBook->head;
        sortedPhoneBook->head = sortedPhoneBook->head->next;

        free(sortedPhoneBookCurrentHead);
    }

    free(sortedPhoneBook);
}

void mergeSort(PhoneBook* phoneBook, int leftIndex, int rightIndex, int parameter) {
    if (rightIndex <= leftIndex + 1) {
        return;
    }

    int middleIndex = (leftIndex + rightIndex) / 2;
    mergeSort(phoneBook, leftIndex, middleIndex, parameter);
    mergeSort(phoneBook, middleIndex, rightIndex, parameter);
    merge(phoneBook, leftIndex, rightIndex, parameter);
}

bool isPhoneBookSortedByCriteria(PhoneBook* phoneBook, const int criteria, int *errorCode) {
    if (isPhoneBookEmpty(phoneBook, errorCode)) {
        return true;
    }

    PhoneBookElement* previosElement = phoneBook->head;
    PhoneBookElement* currentElement = previosElement->next;
    while (currentElement != NULL) {
        if (comparisonPhoneBookElements(previosElement, currentElement, criteria) > 0) {
            return false;
        }
        previosElement = currentElement;
        currentElement = currentElement->next;
    }

    return true;
}
