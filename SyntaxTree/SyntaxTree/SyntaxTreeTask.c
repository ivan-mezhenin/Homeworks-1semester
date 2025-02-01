#include "SyntaxTree.h"
#include "SyntaxTreeTest.h"

#include <stdio.h>

#define FILE_NOT_FOUND -52
#define TESTS_FAILED -323

int main(void) {
    if (!test()) {
        return TESTS_FAILED;
    }

    int errorCode = 0;
    FILE* file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("File not found\n");
        return FILE_NOT_FOUND;
    }

    SyntaxTree* tree = NULL;
    buildSyntaxTree(&tree, file, &errorCode);
    if (errorCode == MEMORY_ALLOCATION_ERROR) {
        printf("Memory allocation error\n");
        return errorCode;
    }
    fclose(file);

    printf("Syntax tree building from file: \n");
    printSyntaxTree(tree);
    printf("\n");
    printf("The result of calculation: %d", calculateSyntaxTree(tree));
    deleteSyntaxTree(&tree);
    
    return errorCode;
}
