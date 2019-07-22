#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

void assert(_Bool result);

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

    printf("<<<<<<<<<<<<<<< Testing shuffle >>>>>>>>>>>>>>>\n");

    printf("Should return 0 for proper shuffle\n");
    memcpy(&testState, &currentState, sizeof(struct gameState));
    shuffle(player, &currentState);
    shuffle(player, &testState);
    assert(shuffle(player, &currentState) == 0);

    printf(" >>>>> shuffle Test Finished <<<<<\n\n");
}

void assert(_Bool result){
    if (result)
        printf("    PASS\n\n");
    else
        printf("    FAIL\n\n");
}