#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "MINION"

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

    printf("<<<<<<<<<<<<<<< Testing MINION >>>>>>>>>>>>>>>\n");

    printf("should gain 2 gold\n");
    memcpy(&testState, &currentState, sizeof(struct gameState));
    choice1 = 1;
    cardEffect(minion, choice1, choice2, choice3, &testState, handPos, &bonus);
    newCoins = 2;
    assert(testState.coins == currentState.coins + newCoins);

    printf("should discard 4 cards\n");
    memcpy(&testState, &currentState, sizeof(struct gameState));
    cardEffect(minion, choice1, choice2, choice3, &testState, handPos, &bonus);
    discarded = 1;
    newCards = 0;
    assert(testState.handCount[thisPlayer] == currentState.handCount[thisPlayer] + newCards - discarded);

    printf("should gain 4 cards\n");
    memcpy(&testState, &currentState, sizeof(struct gameState));
    choice1 = 1;
    cardEffect(minion, choice1, choice2, choice3, &testState, handPos, &bonus);
    newCards = 4;
    assert(testState.handCount[thisPlayer] == currentState.handCount[thisPlayer] + newCards - discarded);

    printf("should check number of cards in deck\n");
    memcpy(&testState, &currentState, sizeof(struct gameState));
    choice1 = 1;
    cardEffect(minion, choice1, choice2, choice3, &testState, handPos, &bonus);
    assert(testState.deckCount[thisPlayer] == 1);


    printf("should play minion card\n");
    assert(testState.playedCardCount+1 == currentState.playedCardCount);

    printf("should discard minion card\n");
    assert(testState.discardCount[thisPlayer] == currentState.discardCount[thisPlayer]);

    printf("should have no changes done to kingdom pile\n");
    memcpy(&testState, &currentState, sizeof(struct gameState));
    cardEffect(baron, choice1, choice2, choice3, &testState, handPos, &bonus);
    assert(playerOne[10] == playerTwo[10]);

    printf(" >>>>> MINION Test Finished <<<<<\n\n");

    return 0;
};

void assert(_Bool result){
    if (result)
        printf("    PASS\n\n");
    else
        printf("    FAIL\n\n");
}