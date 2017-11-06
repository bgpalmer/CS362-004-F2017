## CS362 - Assignment 3
### Brian Palmer </br></br>
### Bugs ###
The following functions were put under test:
<table border=1> 
<tr>
	<td>unittest1.c</td>
	<td>updateCoins()</td>
	<td>1. Returns the correct number of coins</td>
	<td>1. Passed</td>
</tr>
<tr>
	<td>unittest2.c</td>
	<td>fullDeckCount()</td>
	<td>1. Accurately accumulates the number of times a card appears in a players deck, discard, and hand pile</td>
	<td>1. Passed</td>
</tr>
<tr>
	<td>unittest3.c</td>
	<td>isGameOver()</td>
	<td>1. Zero provinces - Game is Over</br>2. 1+ Provinces, No supplies equal 0 - Game is not over </br>3. 1+ Provinces, 2 Supplies equal 0 - Game is not over </br>4. Three supplies are at zero - Game is over</br>5. All supplies equal zero - Game is over </td>
	<td>1. Passed</br>2. Passed </br>3. Passed</br>4. Passed</br>5. Passed</td>
</tr>
<tr>
	<td>unittest4.c</td>
	<td>handCard()</td>
	<td>1. Check that it returns the appropriate card from players hand </td>
	<td>1. Passed</td>
</tr>
</table>

The following refactored functions were put under test:

<table border=1> 
<tr>
	<td>cardtest1.c</td>
	<td>smithy_fn()</td>
	<td>1. Should increase players hand by 2 cards ( draw 3, discard smithy )</td>
	<td>1. Failed - 9 cards were in players hand when there should have been 7 </td>
</tr>
<tr>
	<td>cardtest2.c</td>
	<td>adventurer_fn()</td>
	<td>1. Cards should be removed until two treasure cards( copper, silver, gold ) are drawn. Deck count should reflect this operation</td>
	<td>1. Failed - Too many cards were drawn ( more than two of the listed treasures were drawn ).</td>
</tr>
<tr>
	<td>cardtest3.c</td>
	<td>mine_fn()</td>
	<td>1. Trashed card and mine card should be discarded, and saved treasure should be added to players hand.</td>
	<td>1. Failed - function always returns with -1 </td>
</tr>
<tr>
	<td>cardtest4.c</td>
	<td>village_fn()</td>
	<td>1. Player adds appropriate number of cards to hand</br>2. State number of actions is correct</td>
	<td>1. Passed </br>2. Failed - Too many action cards are added ( 3 too many ).</td>
</tr>
</table>

### Unit Testing ###

We passed dominion.c to gcov after executing each test case to see how our unit tests affected the execution of the functions under test. Ideally, we are looking for 100% coverage of the function under test. This means that our tests provided enough inputs to execute each line and follow every possible branch within the file. 

While we want 100% coverage, this can be difficult to accomplish.
It is difficult to identify all of the inputs neccessary to execute all lines of code in the function at least once. This requires that the tester understands how the function affects the game state, or more abstractly it's environment, and vice versa. 

Using the unittestresuts.out file, we can see how effective our unit tests were as described above by seeing exactly which lines were executed. This data will serve as a baseline to see whether we are able to make improvements on our tests, and to see how effective those improvements are.

**unittest1.c**

<pre><code>
TEST PASSED
File 'dominion.c'
Lines executed:16.64% of 565
Branches executed:16.31% of 417
Taken at least once:13.67% of 417
Calls executed:7.00% of 100
</code></pre>

Update Coins is called twice by the unittest:
1. When initializeGame() is called
2. For the actual test

The for loops run 500+ times because the players hand has 500 cards. The loops over 500 were caused by initializeGame() call.

Since the only cards that are targeted are copper, silver, and gold, the if statements were usually passed about 95% of the time. This was expected. All of the lines were executed at least once.

**unittest2.c**

<pre><code>
TEST SUCCESSUL
File 'dominion.c'
Lines executed:17.88% of 565
Branches executed:19.18% of 417
Taken at least once:16.07% of 417
Calls executed:7.00% of 100
Creating 'dominion.c.gcov'

function fullDeckCount called 1 returned 100% blocks executed 100%
</code></pre>

We achieved 100% coverage of the function under test with our test. 

**unittest3.c**

<pre><code>
Zero Provinces - Game is over: PASSED
One or More Provinces exist - no supplies equal zero: PASSED
Two supplies are at zero: PASSED
Three supplies are at zero: PASSED
All supplies are at zero: PASSED
File 'dominion.c'
Lines executed:17.70% of 565
Branches executed:18.23% of 417
Taken at least once:15.11% of 417
Calls executed:7.00% of 100
Creating 'dominion.c.gcov'

function isGameOver called 5 returned 100% blocks executed 100%
</code></pre>

This function was called 5 times because we tested it 5 times in sequence.

We received 100% coverage with all tests passing. Therefore, we can be confident that we provided comprehensive inputs and that the function outputs appropriately as described by in it's purpose.

**unittest4.c**

<pre><code>
SUCCESS
File 'dominion.c'
Lines executed:17.70% of 565
Branches executed:16.31% of 417
Taken at least once:13.91% of 417
Calls executed:8.00% of 100
Creating 'dominion.c.gcov'

function handCard called 1252 returned 100% blocks executed 100%
</code></pre>

This function was called more often than probably neccessary. We still received 100% coverage though with out unit tests passing. 

**cardtest1.c**

<pre><code>
CARDTEST1: smithy_fn()
Failed: state.handCount[ player ] == 9, should be 7.
Failed: state.handCount[ player ] == 9, should be 7.
Failed: state.handCount[ player ] == 9, should be 7.
TEST FAILED
File 'dominion.c'
Lines executed:23.72% of 565
Branches executed:24.70% of 417
Taken at least once:16.79% of 417
Calls executed:13.00% of 100
Creating 'dominion.c.gcov'


function smithy_fn called 3 returned 100% blocks executed 100%
</code></pre>

Our unit test was able to call 100% of the lines within smithy_fn() so we can be confident that the unit test covers the function. This function did not pass our test case because it changed the environment in unexpected ways. Given that the test case was designed to check the change in game state appropriately, there must be a bug causing the players hand count to be larger than expected. 

**cardtest2.c**

<pre><code>
CARDTEST2: Adventurer
failure: ( init.deckCount[ cp ] - 4 == state.deckCount[ cp ] ), [ 3, 1 ]
TEST FAILED
File 'dominion.c'
Lines executed:20.88% of 565
Branches executed:24.22% of 417
Taken at least once:15.59% of 417
Calls executed:11.00% of 100
Creating 'dominion.c.gcov'

function adventurer_fn called 1 returned 100% blocks executed 
</code></pre>

There were a few branches that were missed. For example:
<pre><code>
	//if the deck is empty we need to shuffle discard and add to deck
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####: 1336:      shuffle(currentPlayer, state);
call    0 never executed
</code></pre>

This function called from adventurer affects the game state. Therefore, it should be run just to be sure all lines are covered.

**cardtest3.c**

<pre><code>
CARDTEST3: mine_fn()
cardEffect( mine, -1, -1, -1, &state, 5, &bonus ) == -1
TEST FAILED
File 'dominion.c'
Lines executed:18.76% of 565
Branches executed:22.30% of 417
Taken at least once:13.91% of 417
Calls executed:10.00% of 100
Creating 'dominion.c.gcov'

function mine_fn called 1 returned 100% blocks executed 19%
</code></pre>

Based on the low execution percentage, there is either a problem with the unit test, a bug with the function, or both. Looking at unittestresults.out, executions end after this line:

<pre><code>
	    1: 1225:  if (state->hand[currentPlayer][choice1] < copper || state->hand[currentPlayer][choice1] > gold)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
branch  2 never executed
branch  3 never executed
        -: 1226:  {
        1: 1227:    return -1;
        -: 1228:  }
</code></pre>

The function terminates because the players choice is not a copper, silver, or gold. The code above suggests that the inputs for the function did not meet the requirements for the card effect and the unit test should be re-evaluated.

**cardtest4.c**

<pre><code>
failed: init.numActions + 2 == state.numActions: [ 3, 6 ]
TEST FAILED
File 'dominion.c'
Lines executed:20.88% of 565
Branches executed:23.26% of 417
Taken at least once:14.39% of 417
Calls executed:12.00% of 100
Creating 'dominion.c.gcov'

function village_fn called 1 returned 100% blocks executed 100%
</code></pre>

This function was called one time and executed each line of code. The test case failed because the function did not alter the environment as expected. Therefore, we are lead to believe there is a problem with the function. 

### Unit Testing Efforts ###

My approach for creating unit tests always started with analyzing how the function affected the game state. To do this, I reread the purpose of each function ( sometimes referring back to the card descriptions online ) and totaled the number of possible branches the function could possibly take. I then added the set of preconditions for that branch to my list of inputs to test. When executing that particular test, at the end of the function, I compared the initial game state with the post state and tested whether the post-state had appropriate results.

This approach seemed to be successful. For all the unit tests (see above), the unit tests that I created using the aformentioned process always passed. No bugs were introducted to these functions so it was expected they would pass. The cardtest functions under test all had bugs introduced to them, which caused failures in all of my unit tests (with the exception of cardtest3.c). This was desirable because these functions implementations were clearly not satisfying the function's objective.


