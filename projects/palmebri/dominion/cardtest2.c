/* Brian Palmer -- cardtest2.c */

/* Adventurer Test */

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

int main( void ) {
	title( "CARDTEST2: Adventurer\n" );

	int kingdoms[] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	int cp, p, i, r0, r1, bonus = 0;
	struct gameState state, init;
	clear( state );
	initializeGame( 4, kingdoms, 3, &state );
	cp = whoseTurn( &state );
	p = 0;
	state.deck[ cp ][ p++ ] = province;
	state.deck[ cp ][ p++ ] = gold;
	state.deck[ cp ][ p++ ] = gold;
	state.deck[ cp ][ p++ ] = silver;
	state.deck[ cp ][ p++ ] = province;
	state.deck[ cp ][ p++ ] = province;
	state.deck[ cp ][ p++ ] = province;
	state.deckCount[ cp ] = p;
	range( i, 0, state.handCount[ cp ] )
		state.hand[ cp ][ i ] = silver;
	state.hand[ cp ][ state.handCount[ cp ]++ ] = adventurer;
	
	clear( init );
	copy( init, state );
	r0 = cardEffect( adventurer, -1, -1, -1, &state, 5, &bonus );
	r1 = ( init.deckCount[ cp ] - 5 == state.deckCount[ cp ] );

	if ( r0 ) printf( "failure: cardEffect( adventure, -1, -1, -1, &state, 5, &bonus ) == %d\n", r0 );
	if ( ! r1 ) printf( "failure: ( init.deckCount[ cp ] - 4 == state.deckCount[ cp ] ), [ %d, %d ]\n",init.deckCount[ cp ] - 4, state.deckCount[ cp ] );

	( r0 && r1  ) ? printf( "TEST SUCCESSFUL\n" ) : printf( "TEST FAILED\n" );
	return 0;
}