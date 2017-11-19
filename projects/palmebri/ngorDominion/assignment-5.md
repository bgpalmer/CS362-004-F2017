#Assignment 5 - Brian Palmer
## Bug Reports

#### Adventurer
<pre><code>
	function useAdventurer called 1 returned 0% blocks executed 86%
        -:  661:void useAdventurer(int temphand[], int drawntreasure, struct gameState *state, int currentPlayer, int cardDrawn, int z)
        -:  662:{
       34:  663:	while(drawntreasure<2)
branch  0 taken 94%
branch  1 taken 6%
        -:  664:	{
       16:  665:		if (state->deckCount[currentPlayer] <1)
branch  0 taken 0%
branch  1 taken 100%
        -:  666:		{
    #####:  667:			shuffle(currentPlayer, state);
    #####:  668:		}
        -:  669:
       16:  670:		drawCard(currentPlayer, state);
        -:  671:
       16:  672:		cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];
        -:  673:
       46:  674:		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
branch  0 taken 94%
branch  1 taken 6%
branch  2 taken 100%
branch  3 taken 0%
branch  4 taken 7%
branch  5 taken 93%
        -:  675:		{
        2:  676:			drawntreasure++;
        2:  677:		}
        -:  678:		else
        -:  679:		{
       14:  680:			temphand[z]=cardDrawn;
       14:  681:			state->handCount[currentPlayer]--;
       14:  682:			z++;
        -:  683:		}
        -:  684:	}
        -:  685:
<span style="color:blue">	 5979:  686:	while(z-1>=0)
branch  0 taken 100%
branch  1 taken 0%
        -:  687:	{
     2989:  688:		state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1];
<span style="color:red">     2989:  689:		z=z+1; </span>
        -:  690:	}
    #####:  691:}  
</span>
</code></pre>

86% of the lines in useAdventurer were executed in one test, but the function did not return. The lines in blue are where the bug is hidden. The reason for this is because the path of execution never breaks away from the while loop ( takes branch 0 100% of the time ). Since the function never returns and no lines are executed after this loop, a signal must be raised here (SIGINT). The type of signal indicates that there was an invalid memory read, telling me an iterator is out of bounds ( currentPlayer, z, or  state->discardCount[currentPlayer] ). Since the loop continues until z is less than 0, z must be the culprit since it is increased after each iteration (in red), and therefore continues to satisfy the loop requirements. The program must throw a segfault then once the z iterator goes out of bounds.

#### Smithy

<pre><code>

	function useSmith called 1 returned 100% blocks executed 100%
        -:  647:void useSmith(int currentPlayer, struct gameState *state, int handPos)
        -:  648:{
        -:  649:	//+3 Card
        -:  650:	int i;
        8:  651:	for (i = 0; i < 3; i++)
branch  0 taken 75%
branch  1 taken 25%
        -:  652:	{
        3:  653:		drawCard(currentPlayer+1, state);
        3:  654:	}
        -:  655:
        -:  656:	//discard card from hand
<span style="color:blue">        1:  657:	discardCard(handPos, currentPlayer-1, state, 0); </span>
        -:  658:
        1:  659:}

</code></pre>

When I tried testing Smithy at first, my tests aborted because of a segmentation fault that test was not able to handle. I added a signal handler for SIGSEGV, allowing the program to terminate gracefully. Signal handling should have been included in this test because it would have made it more robust. When I ran the tests again, I discovered that useSmith says that it returns, but in the helper function discardCard, only 60% of the code executes and never returns.

<pre><code>

<span style="color:red">	function discardCard called 1 returned 0% blocks executed 60% </span>
        -: 1269:int discardCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag)
        -: 1270:{
        -: 1271:  //if card is not trashed, added to Played pile
        1: 1272:  if (trashFlag < 1)
branch  0 taken 100%
branch  1 taken 0%
        -: 1273:    {
        -: 1274:      //add card to played pile
        1: 1275:      state->playedCards[state->playedCardCount] = state->hand[currentPlayer][handPos];
        1: 1276:      state->playedCardCount++;
        1: 1277:    }
        -: 1278:
        -: 1279:  //set played card to -1
        1: 1280:  state->hand[currentPlayer][handPos] = -1;
        -: 1281:  //remove card from player's hand
        1: 1282:  if ( handPos == (state->handCount[currentPlayer] - 1) ) 	//last card in hand array is played
branch  0 taken 0%
branch  1 taken 100%
        -: 1283:    {
        -: 1284:      //reduce number of cards in hand
    #####: 1285:      state->handCount[currentPlayer]--;
    #####: 1286:    }
        1: 1287:  else if ( state->handCount[currentPlayer] == 1 ) //only one card in hand
branch  0 taken 0%
branch  1 taken 100%
        -: 1288:    {
        -: 1289:      //reduce number of cards in hand
    #####: 1290:      state->handCount[currentPlayer]--;
    #####: 1291:    }
        -: 1292:  else
        -: 1293:    {
        -: 1294:      //replace discarded card with last card in hand
        1: 1295:      state->hand[currentPlayer][handPos] = state->hand[currentPlayer][ (state->handCount[currentPlayer] - 1)];
        -: 1296:      //set last card to -1
        1: 1297:      state->hand[currentPlayer][state->handCount[currentPlayer] - 1] = -1;
        -: 1298:      //reduce number of cards in hand
        1: 1299:      state->handCount[currentPlayer]--;
        -: 1300:    }
<span style="color:blue">    #####: 1301:  return 0; </span>
        -: 1302:}

</code></pre>

Because only one test runs and a SIGSEGV signal is thrown, there is likely an invalid argument or a bug in the function above. Some of the executed lines could also be false positives since segmentation faults do not always cause programs to abort. The bug is identified as the current player argument. In useSmith, the current player is reduced by one before being passed to the function above, causing out of bounds references in arrays.


## Test Report

The results above using the random test cases I created last week show various bugs, both in which cause segmentation faults. In Adventurer, there is a logic guard issue that causes an iterator to go out of bounds. This error was quickly identified in dominion.c.gcov by the large number of executions of statements within the loop's scope with respect to the rest of the function. In Smithy, there isn't a problem with it's design, but it does not protect again invalid arguments. A segmentation fault was caused because the current player variable was set to an index outside the valid range of the associated array. Based on the code above, efforts should be made to rectify these bugs before dominion will be playable.

## Debugging

Since the functions under test are very long, printf debugging is a reasonable way to debug. Another way to debug though is with GDB, which provides more control over the program. GDB allows the programmer to place break points within the code and view variable values at that time point. This allows for programmers to iteratively step through the program and see where values change, and by how much.

I used GDB to debug my Smithy Function. I started GDB and provided the name of my executable on the command line( this was my randomcardtest2.c exec ). I registered a breakpoint at the functions call by entering 'break smithy_fn'. I then called 'run'.
The program stopped once smithy_fn was reached and I could see the argument values. At this point nothing looked out of place. I entered 'next' to reach the next source line in the frame. The function whoseTurn was executed automatically, but it I did not need to inspect it as the function variables did not have any odd values. I then noticed in the current line that the range in the for loop was wrong. Sure enough, this was the bug, as I was able to confirm by using step to iterate through the loop and see the players hand count increase past it's target. Step lets you enter into functions, so I was able to step through drawCard to be sure that function was working correctly.

