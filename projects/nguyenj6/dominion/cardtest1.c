#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

void assert(_Bool result);

//initializeGame
int main() {
    struct gameState currentState, testState;
    int numPlayers = 2;
    int seed = 1000;
    int playerOne[10] = {adventurer,
                         embargo,
                         village,
                         minion,
                         mine,
                         cutpurse,
                         sea_hag,
                         tribute,
                         smithy,
                         council_room};

    initializeGame(numPlayers, playerOne, seed, &currentState);

    printf("<<<<<<<<<<<<<<< Testing initializeGame >>>>>>>>>>>>>>>\n");

    printf("initializeGame should return 0\n");
    memcpy(&testState, &currentState, sizeof(struct gameState));
    assert(initializeGame(numPlayers, playerOne, seed, &currentState) == 0);

    printf(" >>>>> initializeGame Test Finished <<<<<\n\n");
}

void assert(_Bool result) {
    if (result)
        printf("    PASS\n\n");
    else
        printf("    FAIL\n\n");
}