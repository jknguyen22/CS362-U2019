#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define TESTCARD "BARON"

#define MAX_TESTS 1000

void assert(_Bool result);

int main() {

    srand(time(NULL));
    struct gameState currentState, testState;
    int i;
    int j;

    int r;
    int handPos = 0;
    int choice1 = 0, choice2 = 0, choice3 = 0;
    int bonus = 0;
    int thisPlayer = 0;

    int newCards = 1;
    int discards = 1;
    int gold = 4;

    printf("<<<<<<<<<<<<<<< Testing BARON >>>>>>>>>>>>>>>\n");
    for (i = 0; i < MAX_TESTS; i++) {
        for (j = 0; j < sizeof(struct gameState)/ sizeof(int); j++) {
            ((int*)&currentState)[j] = rand() % 128;
        }

        //set up current state of game
        currentState.numPlayers = (rand() % 3)+2;
        currentState.whoseTurn = rand() % currentState.numPlayers;
        thisPlayer = whoseTurn(&currentState);
        currentState.handCount[thisPlayer] = (rand() % (MAX_HAND/2))+1;
        currentState.deckCount[thisPlayer] = (rand() % (MAX_DECK/2))+1;
        currentState.discardCount[thisPlayer] = (rand() % (MAX_DECK/2))+1;
        currentState.numBuys = 0;
        handPos = (rand() % currentState.handCount[thisPlayer]);

        // set up testing state of game
        memcpy(&testState, &currentState, sizeof(struct gameState));
        r = cardEffect(baron, choice1, choice2, choice3, &testState, handPos, &bonus);

        // should call baron properly and return 0
        assert (r != 0);

        // should check number of newCards in hand
        assert (testState.handCount[thisPlayer] != currentState.handCount[thisPlayer]+newCards-discards);

        // should check for increase in gold
        assert (testState.numBuys != currentState.numBuys + gold);
    }

    printf(" >>>>> BARON Test Finished <<<<<\n\n");
    return 0;
}

void assert(_Bool result){
    if (result)
        printf("    PASS\n\n");
    else
        printf("    FAIL\n\n");
}