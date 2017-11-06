## Brian Palmer

#### Random Testing

In our last assignment, we created unit tests to check whether our functions responded as designed to inputs we expected them to receive. This provided us with assurance that externally the functions under test were working correctly. We even used gcov to be sure we were covering as much code as possible with our tests. 

Unit tests often cannot provide us with a larger picture though because they are designed to capture a targets response to pre-set criteria. The pre-set criteria is limited to how we understand what inputs the function should be receiving by design, which is a closed-box way to ensure the robustness of a function. In addition, randomized inputs can also help us find edge cases, from canonical off-by-1 errors to undesirable effects on the program state. 

To ensure that our functions work properly, we subjected them to pseudo-randomized inputs to test their robustness iteratively. Through each iteration, the game state was randomized within bounds we deemed 'sane'. In other words, the state was randomized with the domain of values that were probable. In our case, this is would be the domain of positive integers ( note: greatest value set to 128 ).

We used two identical game state structs; one for the function under test and another for the oracle. The oracle state was then compared to the game state after both completed. If there were any differences, then we could say that the function did not run as designed, as specified by the oracle. The oracle was tested for accuracy ( the randomized input was mutated appropiately ) before being used in tests.

The members that were expected to change ( as specified by the oracle ) were retrieved when the function did not pass the test case. These values were compared to provide some clue where the error occurred. Any differences would be considered an instance of the function failing, and the saved results and input could be used to inform us about problem. Since both game states were compared entirely, there was also the possiblity that the game state was changed outside of the observed domain. In this case, the function received inputs that changed the game state in a way that we did not expected. Consequently, our the first method was not always enough to inform us about the bug and required that we print out the entire state structure to view differences.

As a result of random testing, we were able to uncover faults that could not be reached in our unit tests. Our coverage did not change (100% for both unit tests and random testing ); however, random testing is expected to provide more coverage as the complexity of the function under test increases because it becomes harder for testers to find all necessary inputs. 

#### Code Coverage

I. Adventurer </br>

<pre><code>

	File 'dominion.c'
	Lines executed:13.10% of 565
	Branches executed:12.71% of 417
	Taken at least once:7.67% of 417
	Calls executed:8.00% of 100

	function adventurer_fn called 42 returned 98% blocks executed 100%

</code></pre>

Enough randomized inputs were generated to cause the adventure_fn to use all paths. 98% of calls returned because there was eventually a segmentation fault caused by certain inputs. The amount of time before the seg fault was < 1 second. 

II. Smithy </br>

<pre><code>

	RESULT: FAILED
	File 'dominion.c'
	Lines executed:12.92% of 565
	Branches executed:11.75% of 417
	Taken at least once:6.24% of 417
	Calls executed:8.00% of 100
	Creating 'dominion.c.gcov'

	function smithy_fn called 1000 returned 100% blocks executed 100%

</code></pre>

Enough randomized inputs were generated to execute all lines within smithy, without any faults. Every single test failed, showing differences between the oracle state and test function state in members that we were tracking. 

III. Village </br>

<pre><code>

	File 'dominion.c'
	Lines executed:12.74% of 565
	Branches executed:11.27% of 417
	Taken at least once:5.52% of 417
	Calls executed:8.00% of 100
	Creating 'dominion.c.gcov'

	function village_fn called 2000 returned 100% blocks executed 100%

</code></pre>

All lines in Smithy were executed in 2000 tests, and all tests returned. 

#### Unit Vs Random

In terms of coverage, both random and unit tests were able to achieve 100% coverage. I would expect that creating enough inputs to acheive 100% coverage of unit tests becomes increasingly difficult as the function under test grows in complexity, though. Our functions under test were relatively simple in design and complete coverage could be obtained with not many inputs. For larger, more complex functions, the tester could probably acheieve 100% more coverage more easily using random testing. In fact, the tester would probably need to break the complex function down into smaller parts and create unit tests for each.

Random testing was much better at finding faults. For example, the adventurer unit test failed to find the segmentation fault that the random tester found because the inputs provided were not sufficient to trigger the fault. After further analysis, the fault could be acheived if the users deck and discard pile did not have 2 target cards ( coppers, silvers, or golds). The unit tests always had these cards in the players deck. This case would have been much harder to discover with regular unit testing.
