#include "SyntaxTree.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct SyntaxTree {
    char operation;
    int value;
    struct SyntaxTree* leftChild;
    struct SyntaxTree* rightChild;
} SyntaxTree;

void buildSyntaxTree(SyntaxTree** root, FILE* file, int* errorCode) {

    while (!feof(file)) {
        char currentSymbol = fgetc(file);
        switch (currentSymbol) {
        case '(':
        case ' ':
            continue;
        case ')':
            return;
        case '+':
        case '-':
        case '*':
        case '/': {
            *root = calloc(1, sizeof(SyntaxTree));
            if (*root == NULL) {
                *errorCode = MEMORY_ALLOCATION_ERROR;
                free(root);
                return;
            }
            (*root)->operation = currentSymbol;
            buildSyntaxTree(&(*root)->leftChild, file, errorCode);
            buildSyntaxTree(&(*root)->rightChild, file, errorCode);
            break;
        }
        default: {
            *root = calloc(1, sizeof(SyntaxTree));
            if (*root == NULL) {
                *errorCode = MEMORY_ALLOCATION_ERROR;
                free(root);
                return;
            }
            ungetc(currentSymbol, file);
            fscanf_s(file, "%d", &(*root)->value);
            return;
        }

        }
    }
}

int calculateSyntaxTree(SyntaxTree* root) {
    if (root == NULL) {
        return 0;
    }

    int leftResult = calculateSyntaxTree(root->leftChild);
    int rightResult = calculateSyntaxTree(root->rightChild);

    if (root->operation) {
        switch (root->operation)
        {
        case '+':
            return leftResult + rightResult;
        case '-':
            return leftResult - rightResult;
        case '*':
            return leftResult * rightResult;
        case '/':
            return leftResult / rightResult;
        }
    }
    else {
        return root->value;
    }
}

void printSyntaxTree(SyntaxTree* root) {
    if (root == NULL) {
        return;
    }

    if (root->operation) {
        printf("(");
        printSyntaxTree(root->leftChild);
        printf(" %c ", root->operation);
        printSyntaxTree(root->rightChild);
        printf(")");
    }
    else {
        printf("%d", root->value);
    }
}

void deleteSyntaxTree(SyntaxTree** root) {
    if (*root == NULL) {
        return;
    }

    deleteSyntaxTree(&(*root)->leftChild);
    deleteSyntaxTree(&(*root)->rightChild);

    free(*root);
    *root = NULL;
}