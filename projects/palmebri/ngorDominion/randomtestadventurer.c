#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

void SIGSEGV_handler(int signum)
{
    write(STDOUT_FILENO, "SEGFAULT, attempting to write gcov file\n", 40);
    exit(EXIT_SUCCESS);
}

void SIGHUP_handler(int signum)
{
    write(STDOUT_FILENO, "SIGHUP, attempting to write gcov file\n", 40);
    exit(EXIT_SUCCESS);
}

void sighandler(int signum)
{
    if (signum == SIGTERM)
    {
        write(STDOUT_FILENO, "SIGTERM CAUGHT, attempting to write gcov file\n", 42);    
    }
    
    if (signum == SIGHUP)
    {
        write(STDOUT_FILENO, "SIGHUP CAUGHT, attempting to write gcov file\n", 42);    
    }
    
    __gcov_flush();
    exit(EXIT_SUCCESS);
}

int main()
{
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = sighandler;
    sigaction(SIGSEGV, &act, 0);
    sigaction(SIGHUP, &act, 0);

    //signal(SIGHUP, SIGHUP_handler);
    //signal(SIGSEGV, SIGSEGV_handler);
    
    srand(time(NULL));
    int i;
	int seed = rand()%1000+1;
	int numPlayers = rand()%4+1;
	int maxBonus = 10;
	int p, r, s;
	int bonus;
	int k[10] = {adventurer, smithy, ambassador, gardens, baron, feast, mine, remodel, village, great_hall};
	struct gameState pre;
	struct gameState post;
    int maxHandCount = 5;
    
    int tempHand[MAX_HAND];
    int drawntreasureVals[] = {-2, -1, 0, 1, 2, 3, 4, 5};
    int cardDrawn;
    int zVals[] = {-2, -1, 0, 1, 2, 3};

	r = initializeGame(numPlayers, k, seed, &pre);

	// Save the state
    //memcpy(&post, &pre, sizeof(struct gameState));

    int x = 0;
    while (x<2000)
    {
        memcpy(&post, &pre, sizeof(struct gameState));

        int dVal = rand()%8;
        int zVal = rand()%6;

        int drawntreasure = drawntreasureVals[dVal];
        int z = zVals[zVal];

        int currentPlayer = rand()%numPlayers;

        printf("Drawntreasure val: %d\n", drawntreasure);
        printf("Z val: %d\n", z);

        int preDeckCount = post.deckCount[currentPlayer];
        int preHandCount = post.handCount[currentPlayer];
        int preDiscardCount = post.discardCount[currentPlayer];

        printf("DISCLAIMER: Function being tested is implemented with 2 while loops, program may freeze, exit, or segfault during testing.\n");
        printf("USING ADVENTURER\n");
        printf("START NUM CARDS IN DECK = %d\n", preDeckCount);
        printf("START NUM CARDS IN HAND = %d\n", preHandCount);
        printf("START NUM CARDS IN DISCARD = %d\n", preDiscardCount);
        
        
        useAdventurer(tempHand, drawntreasure, &post, currentPlayer, cardDrawn, z);
        post.handCount[currentPlayer]--;

        int postDeckCount = post.deckCount[currentPlayer];
        int postHandCount = post.handCount[currentPlayer];
        int postDiscardCount = post.discardCount[currentPlayer];
        
        printf("AFTER USING ADVENTURER\n");
        printf("NUM CARDS IN DECK = %d\n", postDeckCount);
        printf("NUM CARDS IN HAND = %d\n", postHandCount);
        printf("NUM CARDS IN DISCARD = %d\n", postDiscardCount);

        int rightConditions = 0;

        // At minimum 2 cards will have been taken from the deck
        if (postDeckCount <= preDeckCount-2)
        {
            rightConditions++;
        }

        // +2 for treasure, -1 for using adventure, +1 net to handcount
        if (postHandCount == preHandCount+1)
        {
            rightConditions++;
        }

        // Minimum no change, should match the difference between pre/post deckcounts
        if (postDiscardCount = (preDeckCount - postDeckCount) - 2)
        {
            rightConditions++;
        }

        if (rightConditions == 3)
        {
            printf("TEST PASSED\n");
        }
        else 
        {
            printf("TEST FAILED\n");
        }
        
        printf("\n");
        x++;
        
    }
    return 0;
}