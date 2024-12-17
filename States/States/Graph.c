#include "Graph.h"

#include "stdlib.h"

#define MAX_AMOUNT_OF_CITIES 100
#define MEMORY_ALLOCATION_ERROR -1
#define POINTER_IS_NULL -2

typedef struct Edge {
    int neighborNumber;
    int length;
    struct Edge* next;
} Edge;

typedef struct Graph {
    Edge* edges[MAX_AMOUNT_OF_CITIES];
    int amountOfCities;
} Graph;

Graph* createGraph(int amountOfCities, int* errorCode) {
    Graph* graph = calloc(1, sizeof(Graph));
    if (graph == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }

    graph->amountOfCities = amountOfCities;

    return graph;
}

void addEdge(Graph* graph, int city, int neighbor, int length, int* errorCode) {
    if (graph == NULL) {
        *errorCode = POINTER_IS_NULL;
        return;
    }

    Edge* newEdge = calloc(1, sizeof(Edge));
    if (newEdge == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return;
    }

    newEdge->length = length;
    newEdge->neighborNumber = neighbor;
    newEdge->next = graph->edges[city];
    graph->edges[city] = newEdge;
}