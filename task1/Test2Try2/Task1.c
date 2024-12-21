#include "List.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NUMBER_SIZE 100
#define MEMORY_ALLOCATION_ERROR -1
#define POINTER_IS_NULL -2
#define FILE_NOT_FOUND -3
#define TESTS_FAILED -4

void writeToFile(Node* head, FILE* file, int* errorCode) {
    if (head == NULL) {
        *errorCode = POINTER_IS_NULL;
        return;
    }

    Node* current = head;
    while (current != NULL) {
        fprintf(file, "%d ", current->value);
        current = current->next;
    }
}

void solve(char* filename1, char* filename2, int a, int b, int* errorCode) {
    List* lessThanA = createList(errorCode);
    if (*errorCode != 0) {
        return;
    }

    List* inRangeAB = createList(errorCode);
    if (*errorCode != 0) {
        deleteList(lessThanA);
        return;
    }

    List* greaterThanB = createList(errorCode);
    if (*errorCode != 0) {
        deleteList(lessThanA);
        deleteList(inRangeAB);
        return;
    }

    FILE* file = fopen(filename1, "r");
    if (file == NULL) {
        *errorCode = FILE_NOT_FOUND;
        deleteList(lessThanA);
        deleteList(inRangeAB);
        deleteList(greaterThanB);
        return;
    }

    while (!feof(file)) {
        int number = 0;;
        const int readBytes = fscanf(file, "%d", &number);
        if (readBytes < 0) {
            return;
        }

        if (number < a) {
            addElement(lessThanA, number, errorCode);
            if (*errorCode != 0) {
                deleteList(lessThanA);
                deleteList(inRangeAB);
                deleteList(greaterThanB);
                fclose(file);
                return;
            }
            continue;
        }

        if (number >= a && number <= b) {
            addElement(inRangeAB, number, errorCode);
            if (*errorCode != 0) {
                deleteList(lessThanA);
                deleteList(inRangeAB);
                deleteList(greaterThanB);
                fclose(file);
                return;
            }
            continue;
        }

        addElement(greaterThanB, number, errorCode);
        if (*errorCode != 0) {
            deleteList(lessThanA);
            deleteList(inRangeAB);
            deleteList(greaterThanB);
            fclose(file);
            return;
        }
        continue;
    }
    fclose(file);

    FILE* file2 = fopen(filename2, "w");
    if (file2 == NULL) {
        *errorCode = FILE_NOT_FOUND;
        deleteList(lessThanA);
        deleteList(inRangeAB);
        deleteList(greaterThanB);
        return;
    }

    writeToFile(lessThanA->head, file2, errorCode);
    writeToFile(inRangeAB->head, file2, errorCode);
    writeToFile(greaterThanB->head, file2, errorCode);
    if (*errorCode != 0) {
        *errorCode = FILE_NOT_FOUND;
        deleteList(lessThanA);
        deleteList(inRangeAB);
        deleteList(greaterThanB);
        fclose(file2);
        return;
    }

    deleteList(lessThanA);
    deleteList(inRangeAB);
    deleteList(greaterThanB);
    fclose(file2);
}

bool test1(void) {
    int a = 15;
    int b = 30;
    int errorCode = 0;
    solve("testf1.txt", "testg1.txt", a, b, &errorCode);
    if (errorCode != 0) {
        printf("Test 1 failed\n");
        return false;
    }

    int expectedResult[] = {11, 9, 12, 1, 28, 56, 49, 233, 70, 34};
    FILE* file = fopen("testg1.txt", "w");
    if (file == NULL) {
        printf("Test 1 failed\n");
        return false;
    }

    int index = 0;

    while (!feof(file)) {
        int number = 0;;
        const int readBytes = fscanf(file, "%d", &number);
        if (readBytes < 0) {
            printf("Test 1 failed\n");
            return false;
        }

        if (expectedResult[index] != number) {
            printf("Test 1 failed\n");
            return false;
        }
    }

    fclose(file);
    return true;
}

bool test2(void) {
    int a = 3;
    int b = 8;
    int errorCode = 0;
    solve("testf2.txt", "testg2.txt", a, b, &errorCode);
    if (errorCode != 0) {
        printf("Test 2 failed\n");
        return false;
    }

    int expectedResult[] = {2, 1, 0, 8, 7, 6, 5, 4, 3, 11, 10, 9};
    FILE* file = fopen("testg2.txt", "w");
    if (file == NULL) {
        printf("Test 2 failed\n");
        return false;
    }

    int index = 0;

    while (!feof(file)) {
        int number = 0;;
        const int readBytes = fscanf(file, "%d", &number);
        if (readBytes < 0) {
            printf("Test 2 failed\n");
            return false;
        }

        if (expectedResult[index] != number) {
            printf("Test 2 failed\n");
            return false;
        }
    }

    fclose(file);
    return true;
}

bool test(void) {
    return test1() && test2();
}

int main(void) {
    if (!test()) {
        printf("Tests failed\n");
        return TESTS_FAILED;
    }

    int errorCode = 0;
    int a = 13;
    int b = 30;
    
    solve("f.txt", "g.txt", a, b, &errorCode);
    if (errorCode == POINTER_IS_NULL) {
        printf("Passing a null pointer\n");
    }
    else if (errorCode == MEMORY_ALLOCATION_ERROR) {
        printf("Memory allocation error\n");
    }
    else if (errorCode == FILE_NOT_FOUND) {
        printf("File not found\n");
    }

    return errorCode;
}