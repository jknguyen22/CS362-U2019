#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
void assert(_Bool result);

//getWinners
int main() {
    struct gameState currentState, testState;
    int numPlayers = 2;
    int seed = 1000;
    int players[MAX_PLAYERS];
    int highScore;
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

    printf("<<<<<<<<<<<<<<< Testing getWinners >>>>>>>>>>>>>>>\n");

    printf("should run getWinners properly and return 0\n");
    memcpy(&testState, &currentState, sizeof(struct gameState));
    assert(getWinners(players, &currentState) == 0);
    highScore = players[1];
    printf("Set highest score to player 1\n");
    printf("should show player 0 losing\n");
    assert(players[0] != highScore);
    printf("should show player 1 winning\n");
    assert(players[1] == highScore);

    printf(" >>>>> getWinners Test Finished <<<<<\n\n");
}
void assert(_Bool result) {
    if (result)
        printf("    PASS\n\n");
    else
        printf("    FAIL\n\n");
}