#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "MINE"

void assert(_Bool result);

int main() {
    int discarded;
    int newCards;
    int thisPlayer = 0;
    int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
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

    printf("<<<<<<<<<<<<<<< Testing MINE >>>>>>>>>>>>>>>\n");

    printf("should upgrade copper to silver\n");
    memcpy(&testState, &currentState, sizeof(struct gameState));
    cardEffect(mine, choice1, choice2, choice3, &testState, handPos, &bonus);
    int preMine01 = testState.hand[0][0];
    cardEffect(mine, copper, silver, 0, &testState, 0, 0);
    int postMine01 = testState.hand[0][0];
    assert(preMine01 == 0 && postMine01 == 3);

    printf("should upgrade silver to gold\n");
    memcpy(&testState, &currentState, sizeof(struct gameState));
    cardEffect(mine, choice1, choice2, choice3, &testState, handPos, &bonus);
    int preMine02 = testState.hand[0][0];
    cardEffect(mine, silver, gold, 0, &testState, 0, 0);
    int postMine02 = testState.hand[0][0];
    assert(preMine02 == 3 && postMine02 == 6);

    printf("should upgrade copper currency to gold\n");
    memcpy(&testState, &currentState, sizeof(struct gameState));
    cardEffect(mine, choice1, choice2, choice3, &testState, handPos, &bonus);
    int preMine03 = testState.hand[0][0];
    cardEffect(mine, copper, gold, 0, &testState, 0, 0);
    int postMine03 = testState.hand[0][0];
    assert(preMine03 == 0 && postMine03 == 6);

    printf("should not affect other player\n");
    memcpy(&testState, &currentState, sizeof(struct gameState));
    cardEffect(mine, choice1, choice2, choice3, &testState, handPos, &bonus);
    int preP2 = testState.handCount[1];
    cardEffect(mine, copper, silver, 0, &testState, 0, 0);
    int postP2 = testState.handCount[1];
    assert(preP2 == postP2);

    printf("should discard 1 card\n");
    memcpy(&testState, &currentState, sizeof(struct gameState));
    cardEffect(mine, choice1, choice2, choice3, &testState, handPos, &bonus);
    discarded = 1;
    newCards = 0;
    assert(testState.handCount[thisPlayer] == testState.handCount[thisPlayer] + newCards - discarded);

    printf("should gain 1 card\n");
    memcpy(&testState, &currentState, sizeof(struct gameState));
    choice1 = 1;
    cardEffect(mine, choice1, choice2, choice3, &testState, handPos, &bonus);
    newCards = 1;
    discarded = 1;
    assert(testState.handCount[thisPlayer] == currentState.handCount[thisPlayer] + newCards - discarded);

    printf("should have no changes done to kingdom pile\n");
    memcpy(&testState, &currentState, sizeof(struct gameState));
    cardEffect(mine, choice1, choice2, choice3, &testState, handPos, &bonus);
    assert(playerOne[10] == playerTwo[10]);

    printf(" >>>>> MINE Test Finished <<<<<\n\n");

    return 0;
};

void assert(_Bool result){
    if (result)
        printf("    PASS\n\n");
    else
        printf("    FAIL\n\n");
}