#pragma once

typedef struct State State;

void initializeStates(State* states[], int amountOfCities, int* capitals);

void addCity(State* state, int city);