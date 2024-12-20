#pragma once

#include <stdio.h>

#define MEMORY_ALLOCATION_ERROR -14141

typedef struct SyntaxTree SyntaxTree;

//build syntax tree
void buildSyntaxTree(SyntaxTree** root, FILE* file, int* errorCode);

//return result of calculation syntax tree
int calculateSyntaxTree(SyntaxTree* root);

//print syntax tree
void printSyntaxTree(SyntaxTree* root);

//delete syntax tree
void deleteSyntaxTree(SyntaxTree** root);