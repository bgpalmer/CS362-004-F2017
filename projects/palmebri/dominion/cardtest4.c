/* Brian Palmer - cardtest4.c */

/* village_fn() */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "rngs.h"
#include "dominion.h"
#define clear( x ) memset( & x, '\0', sizeof( x ))
#define range( x, y, z ) for ( x = y; x < z; x++ )
#define copy( x, y ) memcpy( & x, & y, sizeof( x ))

int main( void ) {

	int kingdoms[] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	int cp, bonus = 0, i;
	srand( 3 );
	int r1, r2;

	struct gameState init, state;
	initializeGame( 4, kingdoms, 3, &state );
	cp = state.whoseTurn;

	range( i, 0, state.handCount[ cp ] )
		state.hand[ cp ][ i ] = copper;
	state.hand[ cp ][ state.handCount[ cp ]] = village;
	state.handCount[ cp ]++;
	
	clear( init );
	copy( init, state );

	cardEffect( village, -1, -1, -1, &state, 5, &bonus );

	r1 = ( init.handCount[ cp ] == state.handCount[ cp ] ); /* Check hand */
	r2 = ( init.numActions + 2 == state.numActions ); /* Check num actions */

	if ( ! r1 ) printf( "failed: init.handCount[ cp ] == state.handCount[ cp ]: [ %d, %d ]\n",
		init.handCount[ cp ] + 1, state.handCount[ cp ] );

	if ( ! r2 ) printf( "failed: init.numActions + 2 == state.numActions: [ %d, %d ]\n",
		init.numActions + 2, state.handCount[ cp ] );

	( r1 && r2 ) ? printf( "TEST PASSED\n" ) : printf( "TEST FAILED\n" );

	return 0;
}
