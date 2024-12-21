#include "States.h"
#include <stdlib.h>

#define MAX_AMOUNT_OF_CITIES 100
#define MEMORY_ALLOCATION_ERROR -1

void initializeStates(State* states[], int amountOfCapitals, int* capitals, int* errorCode) {
    for (int i = 0; i < amountOfCapitals; ++i) {
        states[i] = malloc(sizeof(State));
        if (states[i] == NULL) {
            *errorCode = MEMORY_ALLOCATION_ERROR;
            return;
        }

        states[i]->amountOfCities = 0;
        states[i]->capital = capitals[i];
        addCity(states[i], capitals[i]);
    }
}

void addCity(State* state, int city) {
    state->cities[state->amountOfCities++] = city;
}

void deleteStates(State* states[], int amountOfCapitals) {
    for (int i = 0; i < amountOfCapitals; i++) {
        free(states[i]);
    }
}