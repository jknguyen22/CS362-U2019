#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
void assert(_Bool result);

//endTurn
int main()
{
    struct gameState currentState, testState;
    int numPlayers = 2;
    int seed = 1000;
    int player = 1;
    // int handpos = 0;
    int card = 0;
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
    memcpy(&testState, &currentState, sizeof(struct gameState));

    printf("<<<<<<<<<<<<<<< Testing endTurn >>>>>>>>>>>>>>>\n");

    printf("should endTurn run properly and return 0\n");
    assert(endTurn(&currentState) == 0);

    printf("should have 0 cards in deck during turn\n");
    assert(fullDeckCount(player, card, &currentState) == 0);
    printf("should have 5 cards in deck during turn\n");
    assert(fullDeckCount(player, card, &currentState) == 5);

    printf("should have 10 cards in deck during turn\n");
    assert(fullDeckCount(player, card, &currentState) == 10);

    endTurn(&currentState);

    int playerHand = numHandCards(&currentState);
    printf("should have 0 cards in deck after turn\n");
    assert(fullDeckCount(player, card, &currentState) == 0);

    printf("should have 5 cards in deck after turn\n");
    assert(fullDeckCount(player, card, &currentState) == 5);

    printf("should have 10 cards in deck after turn\n");
    assert(fullDeckCount(player, card, &currentState) == 10);

    printf("should not have 0 cards in hand after turn\n");
    assert(playerHand != 0);

    printf("should have 5 cards in hand after turn\n");
    assert(playerHand == 5);

    printf(" >>>>> endTurn Test Finished <<<<<\n\n");
}

void assert(_Bool result){
    if (result)
        printf("    PASS\n\n");
    else
        printf("    FAIL\n\n");
}