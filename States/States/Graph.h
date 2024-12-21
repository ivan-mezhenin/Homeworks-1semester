#pragma once

#define MAX_AMOUNT_OF_CITIES 100

typedef struct Edge {
    int neighborNumber;
    int length;
    struct Edge* next;
} Edge;

typedef struct Graph {
    Edge* edges[MAX_AMOUNT_OF_CITIES];
    int amountOfCities;
} Graph;

Graph* createGraph(int amountOfCities, int* errorCode);

void addEdge(Graph* graph, int city, int neighbor, int length, int* errorCode);

void deleteGraph(Graph* graph, int* cities);