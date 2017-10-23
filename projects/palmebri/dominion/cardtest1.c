/* Brian Palmer -- cardtest1.c */

/* smithy_fn() */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "rngs.h"
#include "dominion.h"
#define clear( x ) memset( & x, '\0', sizeof( x ))
#define range( x, y, z ) for ( x = y; x < z; x++ )
#define title( x ) printf( x )

int main( void ) {
	title( "CARDTEST1: smithy_fn()\n");
	int kingdoms[] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	int players, result = 1, r, bonus = 0, expected_card_k;
	struct gameState state;

	range( players, 2, MAX_PLAYERS + 1 ) {
		clear( state );
		initializeGame( players, kingdoms, 3, &state );
		state.hand[ state.whoseTurn ][ 0 ] = smithy;
		expected_card_k = state.handCount[ state.whoseTurn ] + 3 - 1; // Add 3 cards, -1 for discarding smithy
		cardEffect( smithy, -1, -1, -1, &state, 0, &bonus );
		result &= r = ( state.handCount[ state.whoseTurn ] == expected_card_k );
		if ( r == 0 )
			printf( "Failed: state.handCount[ player ] == %d, should be %d.\n", state.handCount[ state.whoseTurn ], expected_card_k );
	}

	( result ) ? printf( "TEST PASS\n" ) : printf( "TEST FAILED\n" );

	return 0;
}

