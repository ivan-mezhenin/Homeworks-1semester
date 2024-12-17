#include "States.h"

#define MAX_AMOUNT_OF_CITIES 100

typedef struct State {
    int capital;
    int cities[MAX_AMOUNT_OF_CITIES];
    int amountOfCities;
} State;

void initializeStates(State* states[], int amountOfCities, int* capitals) {
    for (int i = 0; i < amountOfCities; ++i) {
        states[i]->amountOfCities = 0;
        states[i]->capital = capitals[i];
    }
}

void addCity(State* state, int city) {
    state->cities[state->amountOfCities++] = city;
}