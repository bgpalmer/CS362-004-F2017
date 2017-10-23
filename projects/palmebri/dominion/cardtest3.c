/* Brian Palmer -- cardtest3.c */

/* mine_fn() */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "rngs.h"
#include "dominion.h"
#define clear( x ) memset( & x, '\0', sizeof( x ))
#define range( x, y, z ) for ( x = y; x < z; x++ )
#define copy( x, y ) memcpy( & x, & y, sizeof( x ))
#define title( x ) printf( x )

int main ( void ) {

	title( "CARDTEST3: mine_fn()");

	int kingdoms[] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	int cp, bonus = 0, i;
	struct gameState init, state;
	srand( 3 );

	int r1;
	initializeGame( 4, kingdoms, 3, &state );
	cp = whoseTurn( &state );
	range( i, 0, state.handCount[ cp ] )
		state.hand[ cp ][ i ] = copper;
	state.hand[ cp ][ state.handCount[ cp ]++ ] = mine;
	copy( init, state );
	r1 = cardEffect( mine, -1, -1, -1, &state, 5, &bonus );
	if ( r1 != 0 ) printf( "cardEffect( mine, -1, -1, -1, &state, 5, &bonus ) == %d\n", r1 );
	( r1 == 0 ) ? printf( "TEST SUCCESSFUL\n" ) : printf( "TEST FAILED\n" );
	return 0;
}