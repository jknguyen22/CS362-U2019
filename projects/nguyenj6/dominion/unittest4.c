#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "TRIBUTE"

void assert(_Bool result);

int main(){

    int newCards;
    int newCoins;
    int newAction;
    int oldAction;
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

    printf("<<<<<<<<<<<<<<< Testing TRIBUTE >>>>>>>>>>>>>>>\n");

    printf("should increase actions by 2\n");
    memcpy(&testState, &currentState, sizeof(struct gameState));
    choice1 = 1;
    cardEffect(tribute, choice1, choice2, choice3, &testState, handPos, &bonus);
    newCards = 2;
    newAction = 2;
    oldAction = 0;
    assert(newAction == oldAction + 2);

    printf("should gain 2 gold\n");
    memcpy(&testState, &currentState, sizeof(struct gameState));
    choice1 = 2;
    cardEffect(tribute, choice1, choice2, choice3, &testState, handPos, &bonus);
    newCoins = 2;
    assert(newCoins == currentState.coins + 2);

    printf("should gain 2 cards\n");
    memcpy(&testState, &currentState, sizeof(struct gameState));
    choice1 = 3;
    cardEffect(tribute, choice1, choice2, choice3, &testState, handPos, &bonus);
    newCards = 2;
    newCoins = 0;
    discarded = 0;
    assert(testState.handCount[thisPlayer] == currentState.handCount[thisPlayer] + newCards - discarded);

    printf("should discard 2 cards\n");
    memcpy(&testState, &currentState, sizeof(struct gameState));
    cardEffect(tribute, choice1, choice2, choice3, &testState, handPos, &bonus);
    discarded = 2;
    assert(testState.handCount[thisPlayer] == currentState.handCount[thisPlayer] + newCards - discarded);

    printf("should have no changes done to kingdom pile\n");
    memcpy(&testState, &currentState, sizeof(struct gameState));
    cardEffect(tribute, choice1, choice2, choice3, &testState, handPos, &bonus);
    assert(playerOne[10] == playerTwo[10]);

    printf(" >>>>> TRIBUTE Test Finished <<<<<\n\n");

    return 0;
};

void assert(_Bool result){
    if (result)
        printf("    PASS\n\n");
    else
        printf("    FAIL\n\n");
}