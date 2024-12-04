#include "List.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct ListElement {
    char* word;
    int frequency;
    struct ListElement* next;
}ListElement;

ListElement* createListElement(char* word, int* errorCode) {
    ListElement* node = calloc(1, sizeof(ListElement));
    if (node == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }
    node->frequency = 1;

    node->word = malloc(strlen(word) + 1);
    if (node->word == NULL) {
        free(node);
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }

    strcpy(node->word, word);
    node->next = NULL;

    return node;
}

void printList(ListElement** head, int* errorCode) {
    if (head == NULL || *head == NULL) {
        *errorCode = POINTER_IS_NULL;
        return;
    }

    ListElement* current = *head;
    while (current != NULL) {
        printf("%s %d\n", current->word, current->frequency);
        current = current->next;
    }
}

void addElement(ListElement** head, char* word, int* errorCode, bool* wordIsUnique) {
    if (head == NULL) {
        *errorCode = POINTER_IS_NULL;
        return;
    }

    ListElement* current = *head;
    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            ++current->frequency;
            *wordIsUnique = false;
            return;
        }
        current = current->next;
    }

    ListElement* newElement = createListElement(word, errorCode);
    if (*errorCode != 0) {
        return;
    }

    newElement->next = *head;
    *head = newElement;
}

void deleteList(ListElement* head) {
    ListElement* current = head;
    while (current != NULL) {
        ListElement* toDelete = current;
        current = current->next;
        free(toDelete->word);
        free(toDelete);
    }
}

int getFrequency(ListElement* node) {
    return node->frequency;
}