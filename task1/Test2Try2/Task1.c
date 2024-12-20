#include "List.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NUMBER_SIZE 100
#define MEMORY_ALLOCATION_ERROR -1
#define POINTER_IS_NULL -2
#define FILE_NOT_FOUND -3

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

int main(void) {
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
}