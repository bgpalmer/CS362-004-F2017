/* Brian Palmer - unittest2.c */

/* fullDeckCount() */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "rngs.h"
#include "dominion.h"
#define clear( x ) memset( & x, '\0', sizeof( x ))
#define range( x, y, z ) for ( x = y; x < z; x++ )
#define copy( x, y ) memcpy( & x, & y, sizeof( x ));

int kCard( int card, int player, struct gameState * state ) {
	int i, k = 0;
	range( i, 0, state->deckCount[ player ] )
		k += ( state->deck[ player ][ i ] == card );
	range( i, 0, state->handCount[ player ] )
		k += ( state->hand[ player ][ i ] == card );
	range( i, 0, state->discardCount[ player ] )
		k += ( state->discard[ player ][ i ] == card );
	return k;
}

int main( void ) {

	int kingdoms[] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	struct gameState state, init;
	int cp, i, card, r1, r2;
	
	clear( state );
	initializeGame( 4, kingdoms, 3, &state );

	cp = whoseTurn( &state );
	state.deckCount[ cp ] = 500;
	state.handCount[ cp ] = 500;
	state.discardCount[ cp ] = 500;
	range( i, 0, state.deckCount[ cp ] )
		state.deck[ cp ][ i ] = rand() % ( treasure_map + 1 );
	range( i, 0, state.handCount[ cp ] )
		state.hand[ cp ][ i ] = rand() % ( treasure_map + 1 );
	range( i, 0, state.discardCount[ cp ] )
		state.discard[ cp ][ i ] = rand() % ( treasure_map + 1 );
	card = rand() % ( treasure_map + 1 );
	copy( init, state );
	r1 = kCard( card, cp, &state );
	r2 = fullDeckCount( cp, card, &state );
	if ( r1 != r2 ) printf( "failure: ( kCard( card, cp, &state ) == fullDeckCount( cp, card, &state )) : ( %d, %d )\n", r1, r2 );
	r1 ? printf( "TEST SUCCESSUL\n" ) : printf( "TEST FAILURE\n");
	return 0;
}