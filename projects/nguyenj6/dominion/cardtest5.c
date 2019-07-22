#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
void assert(_Bool result);

//drawCard
int main()
{
    struct gameState currentState, testState;

    int numPlayers = 2;
    int player = 1;
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
    initializeGame(numPlayers, playerOne, seed, &testState);

    printf("<<<<<<<<<<<<<<< Testing drawCard >>>>>>>>>>>>>>>\n");
    printf("drawCard should return 0\n");
    memcpy(&testState, &currentState, sizeof(struct gameState));
    drawCard(player, &currentState);
    int firstDraw = drawCard(player, &currentState);
    drawCard(player, &testState);

    assert(firstDraw == 0);
    drawCard(player, &currentState);
    int secondDraw = drawCard(player, &currentState);

    printf("should be different from previous draw\n");
    assert(firstDraw == secondDraw);

    printf("should be different from game and testgame\n");
    assert(drawCard(player, &currentState) == drawCard(player,&testState));

    printf(" >>>>> drawCard Test Finished <<<<<\n\n");
}
void assert(_Bool result) {
    if (result)
        printf("    PASS\n\n");
    else
        printf("    FAIL\n\n");
}