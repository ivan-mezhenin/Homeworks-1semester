#pragma once

typedef struct Edge Edge;

typedef struct Graph Graph;

Graph* createGraph(int amountOfCities, int* errorCode);

void addEdge(Graph* graph, int city, int neighbor, int length, int* errorCode);