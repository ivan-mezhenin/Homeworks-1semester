#define _CRT_SECURE_NO_WARNINGS
#include "States.h"
#include "Graph.h"

#include <stdio.h>
#include <stdbool.h>

#define MAX_AMOUNT_OF_CITIES 100
#define INCORRECT_INPUT 1
#define MEMORY_ALLOCATION_ERROR -1
#define POINTER_IS_NULL -2
#define FILE_NOT_FOUND -3
#define TESTS_FAILED -4

int findClosestCity(Graph* graph, int* state, int stateNumber) {
    int minDistance = 10000;
    int closestCity = -1;

    for (int i = 1; i <= graph->amountOfCities; ++i) {
        if (state[i] == stateNumber) {
            Edge* edge = graph->edges[i];
            while (edge != NULL) {
                if (state[edge->neighborNumber] == 0 && edge->length < minDistance) {
                    minDistance = edge->length;
                    closestCity = edge->neighborNumber;
                }
                edge = edge->next;
            }
        }
    }
    
    return closestCity;
}

void distributeCities(Graph* graph, int k, State* states[]) {
    int remainingCities = graph->amountOfCities - k;
    int state[MAX_AMOUNT_OF_CITIES] = { 0 };

    for (int i = 0; i < k; ++i) {
        state[states[i]->capital] = states[i]->capital;
    }

    while (remainingCities > 0) {

        for (int i = 0; i < k; ++i) {
            if (remainingCities <= 0) {
                break;
            }

            int closestCity = findClosestCity(graph, state, states[i]->capital);

            if (closestCity != -1) {
                state[closestCity] = states[i]->capital;
                addCity(states[i], closestCity);
                remainingCities--;
            }
        }
    }
}

void readDataFromFileToGraph(FILE* file, Graph* graph, int* cities, int m, int *errorCode) {
    for (int i = 0; i < m; ++i) {
        int city = 0;
        int neighbor = 0;
        int length = 0;

        if (fscanf(file, "%d %d %d", &city, &neighbor, &length) < 0) {
            fclose(file);
            deleteGraph(graph, cities);
            *errorCode = INCORRECT_INPUT;
            return;
        }

        cities[city] = 1;
        cities[neighbor] = 1;

        addEdge(graph, city, neighbor, length, &errorCode);
        addEdge(graph, neighbor, city, length, &errorCode);
        if (*errorCode != 0) {
            fclose(file);
            deleteGraph(graph, cities);
            return;
        }
    }
}

void printStates(int k, State* states[]) {
    for (int i = 0; i < k; i++) {
        printf("State %d: ", states[i]->capital);
        for (int j = 0; j < states[i]->amountOfCities; j++) {
            printf("%d ", states[i]->cities[j]);
        }
        printf("\n");
    }
}

int solve(void) {
    int n = 0;
    int m = 0;
    int k = 0;
    int capitals[MAX_AMOUNT_OF_CITIES] = { 0 };
    int errorCode = 0;
    int cities[MAX_AMOUNT_OF_CITIES] = { 0 };

    FILE* file = fopen("data.txt", "r");
    if (file == NULL) {
        return FILE_NOT_FOUND;
    }

    if (fscanf(file, "%d %d", &n, &m) < 0) {
        fclose(file);
        return INCORRECT_INPUT;
    }

    Graph* graph = createGraph(n, &errorCode);
    if (errorCode != 0) {
        fclose(file);
        return errorCode;
    }

    readDataFromFileToGraph(file, graph, cities, m, &errorCode);
    if (errorCode != 0) {
        return errorCode;
    }

    if (fscanf(file, "%d", &k) < 0) {
        fclose(file);
        deleteGraph(graph, cities);
        return INCORRECT_INPUT;
    }

    for (int i = 0; i < k; ++i) {
        if (fscanf(file, "%d", &capitals[i]) < 0) {
            fclose(file);
            deleteGraph(graph, cities);
            return INCORRECT_INPUT;
        }
    }

    fclose(file);

    State* states[MAX_AMOUNT_OF_CITIES];
    initializeStates(states, k, capitals, &errorCode);
    if (errorCode != 0) {
        deleteGraph(graph, cities);
        return errorCode;
    }

    distributeCities(graph, k, states);

    printStates(k, states);

    deleteGraph(graph, cities);
    deleteStates(states, k);

    return errorCode;
}

bool test1(void) {
    int n = 0;
    int m = 0;
    int k = 0;
    int capitals[MAX_AMOUNT_OF_CITIES] = { 0 };
    int errorCode = 0;
    int cities[MAX_AMOUNT_OF_CITIES] = { 0 };
    int state[MAX_AMOUNT_OF_CITIES] = { 0 };

    state[1] = 1;
    state[2] = 2;

    FILE* file = fopen("testdata1.txt", "r");
    if (file == NULL) {
        return false;
    }

    if (fscanf(file, "%d %d", &n, &m) < 0) {
        fclose(file);
        return false;
    }

    Graph* graph = createGraph(n, &errorCode);
    if (errorCode != 0) {
        fclose(file);
        return false;
    }

    readDataFromFileToGraph(file, graph, cities, m, &errorCode);
    if (errorCode != 0) {
        return false;
    }

    fclose(file);

    int expectedResult1 = 3;
    int expectedResult2 = 4;

    bool passed = expectedResult1 == findClosestCity(graph, state, 1)
        && expectedResult2 == findClosestCity(graph, state, 2);

    deleteGraph(graph, cities);
    
    return passed;
}

bool test2(void) {
    int n = 0;
    int m = 0;
    int k = 0;
    int capitals[MAX_AMOUNT_OF_CITIES] = { 0 };
    int errorCode = 0;
    int cities[MAX_AMOUNT_OF_CITIES] = { 0 };
    int state[MAX_AMOUNT_OF_CITIES] = { 0 };

    state[1] = 1;

    FILE* file = fopen("testdata2.txt", "r");
    if (file == NULL) {
        return false;
    }

    if (fscanf(file, "%d %d", &n, &m) < 0) {
        fclose(file);
        return false;
    }

    Graph* graph = createGraph(n, &errorCode);
    if (errorCode != 0) {
        fclose(file);
        return false;
    }

    readDataFromFileToGraph(file, graph, cities, m, &errorCode);
    if (errorCode != 0) {
        return false;
    }

    fclose(file);

    int expectedResult[] = {2, 3, 4};
    bool passed = true;

    for (int i = 0; i < 3; ++i) {
        if (findClosestCity(graph, state, 1) != expectedResult[i]) {
            passed = false;
            break;
        }
        state[expectedResult[i]] = 1;
    }

    deleteGraph(graph, cities);

    return passed;
}

bool test(void) {
    if (!test1()) {
        printf("Test 1 failed\n");
        return false;
    }

    if (!test2()) {
        printf("Test 2 failed\n");
        return false;
    }

    return true;
}

int main(void) {
    if (!test()) {
        return TESTS_FAILED;
    }

    int errorCode = solve();
    if (errorCode == MEMORY_ALLOCATION_ERROR) {
        printf("Memory allocation error\n");
    }
    else if (errorCode == POINTER_IS_NULL) {
        printf("Passing a null pointer\n");
    }
    else if (errorCode == INCORRECT_INPUT) {
        printf("Incorrect input\n");
    }
    else if (errorCode == FILE_NOT_FOUND) {
        printf("File not found\n");
    }

    return errorCode;
}