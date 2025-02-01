#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100
#define MEMORY_ALLOCATION_ERROR -1
#define TESTS_FAILED -2

void dfs(int graph[MAX_VERTICES][MAX_VERTICES], int visited[], int vertex, int amountOfVertices) {
    visited[vertex] = 1;

    for (int i = 0; i < amountOfVertices; ++i) {
        if (graph[vertex][i] && !visited[i]) {
            dfs(graph, visited, i, amountOfVertices);
        }
    }
}

int* findReachableVertices(int graph[MAX_VERTICES][MAX_VERTICES], int amountOfVertices, int* amountOfReachebleVertices, int* errorCode) {
    int reachableVertices[MAX_VERTICES] = {0};
    int index = 0;

    for (int i = 0; i < amountOfVertices; ++i) {
        int visited[MAX_VERTICES] = { 0 };
        dfs(graph, visited, i, amountOfVertices);

        bool reachable = true;
        for (int j = 0; j < amountOfVertices; ++j) {
            if (!visited[j]) {
                reachable = false;
                break;
            }
        }

        if (reachable) {
            reachableVertices[index++] = i;
            ++*amountOfReachebleVertices;
        }
    }

    return reachableVertices;
}

bool findReachableVerticesTest1(void) {
    int graph[MAX_VERTICES][MAX_VERTICES] = {
        {0, 1, 0, 0, 1, 1},
        {1, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0, 0},
        {0, 0, 1, 0, 0, 0},
        {1, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0}
    };
    int numVertices = 6;
    int errorCode = 0;
    int amountOfReachebleVertices = 0;

    int* reachableVertices = findReachableVertices(graph, numVertices, &amountOfReachebleVertices, &errorCode);
    if (errorCode != 0) {
        return false;
    }

    int expectedResult[] = {0, 1, 2, 3, 4, 5};

    bool passed = true;

    for (int i = 0; i < amountOfReachebleVertices; ++i) {
        if (reachableVertices[i] != expectedResult[i]) {
            passed = false;
            break;
        }
    }

    return passed;
}

bool findReachableVerticesTest2(void) {
    int graph[MAX_VERTICES][MAX_VERTICES] = {
        {0, 1, 0},
        {1, 0, 0},
        {0, 0, 0},
    };
    int numVertices = 3;
    int errorCode = 0;
    int amountOfReachebleVertices = 0;

    int* reachableVertices = findReachableVertices(graph, numVertices, &amountOfReachebleVertices, &errorCode);
    if (errorCode != 0) {
        return false;
    }

    bool passed = amountOfReachebleVertices == 0;

    return passed;
}

bool test(void) {
    if (!findReachableVerticesTest1()) {
        printf("Test 1 failed\n");
        return false;
    }

    if (!findReachableVerticesTest2()) {
        printf("Test 2 failed\n");
        return false;
    }

    return true;
}

int main(void) {
    if (!test()) {
        return TESTS_FAILED;
    }

    int graph[MAX_VERTICES][MAX_VERTICES] = {
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {1, 0, 0, 0}
    };

    int numVertices = 4;
    int errorCode = 0;
    int amountOfReachebleVertices = 0;

    int* reachableVertices = findReachableVertices(graph, numVertices, &amountOfReachebleVertices, &errorCode);
    if (errorCode == 0) {
        printf("Vertices from which all other vertices are reachable:\n");

        for (int i = 0; i < amountOfReachebleVertices; ++i) {
            printf("%d ", reachableVertices[i]);
        }

    }
    else if (errorCode == MEMORY_ALLOCATION_ERROR) {
        printf("Memory allocation error\n");
    }

    return errorCode;
}