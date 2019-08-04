#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX_TESTS 20

#define TESTCARD "MINION"


void assert(_Bool result);

int main() {
    struct gameState currentState, testState;

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
    int seed = 1000;

    int i;
    int r;
    int thisPlayer = 0;
    int numPlayers = 0;

    printf("<<<<<<<<<<<<<<< Testing MINION >>>>>>>>>>>>>>>\n");
    for (i = 0; i < MAX_TESTS; i++) {
        // 2 - 4 players
        numPlayers = (rand() % 3)+2;
        seed = rand();
        initializeGame(numPlayers, playerOne, seed, &currentState);
        thisPlayer = rand() % numPlayers;

        //set up current state of game
        currentState.whoseTurn = thisPlayer;
        currentState.deckCount[thisPlayer] = rand() % MAX_DECK;
        currentState.discardCount[thisPlayer] = rand() % MAX_DECK;
        currentState.handCount[thisPlayer] = rand() % MAX_HAND;
        currentState.hand[thisPlayer][0] = minion;
        currentState.numActions = rand() % 10;

        // set up testing state of game
        memcpy(&testState, &currentState, sizeof(struct gameState));
        r = cardEffect(minion, 0, 0, 0, &currentState, 0, 0);

        // should call minion properly and return 0
        assert (r == 0);

        // card should be drawn from correct player's deck
        assert (currentState.deckCount[thisPlayer] != (testState.deckCount[thisPlayer] - 1));

        // should increase player's actions by 1
        assert (currentState.numActions != (testState.numActions + 1));

    }
    printf(" >>>>> MINION Test Finished <<<<<\n\n");
    return 0;
}

void assert(_Bool result){
    if (result)
        printf("    PASS\n\n");
    else
        printf("    FAIL\n\n");
}