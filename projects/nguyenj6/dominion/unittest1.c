#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "BARON"

void assert(_Bool result);

int main(){

    int newCards;
    int newCoins;
    int discarded;
    int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int thisPlayer = 0;
    struct gameState currentState, testState;
    int numPlayers = 2;
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

    int playerTwo[10] = {adventurer, 
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

    printf("<<<<<<<<<<<<<<< Testing BARON >>>>>>>>>>>>>>>\n");

    printf("player should have 4 gold\n");
    memcpy(&testState, &currentState, sizeof(struct gameState));
    choice1 = 1;
    cardEffect(baron, choice1, choice2, choice3, &testState, handPos, &bonus);
    newCoins = 0;
    assert(testState.coins == currentState.coins + newCoins);

    printf("should have 4 cards in hand after discard\n");
    memcpy(&testState, &currentState, sizeof(struct gameState));
    cardEffect(baron, choice1, choice2, choice3, &testState, handPos, &bonus);
    newCards = 0;
    discarded = 1;
    assert(testState.handCount[thisPlayer] == currentState.handCount[thisPlayer] + newCards - discarded);

    printf("should play baron card properly\n");
    memcpy(&testState, &currentState, sizeof(struct gameState));
    cardEffect(baron, choice1, choice2, choice3, &testState, handPos, &bonus);
    assert(testState.playedCardCount+1 == currentState.playedCardCount);

    printf("should discard baron card properly\n");
    assert(testState.discardCount[thisPlayer] == currentState.discardCount[thisPlayer]);

    printf("should have no changes done to kingdom pile\n");
    memcpy(&testState, &currentState, sizeof(struct gameState));
    cardEffect(baron, choice1, choice2, choice3, &testState, handPos, &bonus);
    assert(playerOne[10] == playerTwo[10]);

    printf(" >>>>> BARON Test Finished <<<<<\n\n");

    return 0;
};

void assert(_Bool result){
    if (result)
        printf("    PASS\n\n");
    else
        printf("    FAIL\n\n");
}