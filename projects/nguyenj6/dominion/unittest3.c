#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "AMBASSADOR"

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

    printf("<<<<<<<<<<<<<<< Testing AMBASSADOR >>>>>>>>>>>>>>>\n");

    printf("should gain 2 cards\n");
    memcpy(&testState, &currentState, sizeof(struct gameState));
    choice1 = 1;
    cardEffect(ambassador, choice1, choice2, choice3, &testState, handPos, &bonus);
    newCards = 2;
    newCoins = 0;
    discarded = 0;
    assert(testState.handCount[thisPlayer] == currentState.handCount[thisPlayer] + newCards - discarded);

    printf("should have current coins + gained gold\n");
    assert(testState.coins == currentState.coins + newCoins);

    printf("should have correct amount of cards after drawing and discarding\n");
    memcpy(&testState, &currentState, sizeof(struct gameState));
    cardEffect(ambassador, choice1, choice2, choice3, &testState, handPos, &bonus);
    discarded = 1;
    assert(testState.handCount[thisPlayer] == currentState.handCount[thisPlayer] + newCards - discarded);

    printf("should discard only 1 card\n");
    assert(testState.handCount[thisPlayer] == currentState.handCount[thisPlayer] + newCards - discarded);

    printf("should play ambassador card\n");
    assert(testState.playedCardCount+1 == currentState.playedCardCount);

    printf("should discard ambassador card\n");
    assert(testState.discardCount[thisPlayer] == currentState.discardCount[thisPlayer]);
    memcpy(&testState, &currentState, sizeof(struct gameState));
    cardEffect(ambassador, choice1, choice2, choice3, &testState, handPos, &bonus);

    printf("should have no changes done to kingdom pile\n");
    assert(playerOne[10] == playerTwo[10]);

    printf(" >>>>> AMBASSADOR Test Finished <<<<<\n\n");

    return 0;
};

void assert(_Bool result){
    if (result)
        printf("    PASS\n\n");
    else
        printf("    FAIL\n\n");
}