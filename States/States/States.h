#pragma once

#define MAX_AMOUNT_OF_CITIES 100

typedef struct State {
    int capital;
    int cities[MAX_AMOUNT_OF_CITIES];
    int amountOfCities;
} State;

void initializeStates(State* states[], int amountOfCities, int* capitals, int* errorCode);

void addCity(State* state, int city);

void deleteStates(State* states[], int amountOfCapitals);