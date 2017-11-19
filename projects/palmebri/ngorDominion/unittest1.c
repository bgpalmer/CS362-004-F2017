/* Brian Palmer -- unittest1.c */

/* updateCoin() */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>
#include "dominion.h"
#include "rngs.h"
#define range( x, y, z ) for ( x = y; x < z; x++ )
#define clear( x ) memset( & x, '\0', sizeof( x ))
#define copy( x, y ) memcpy( & x, & y, sizeof( x ))

int main( int argc, char ** argv ) {
	
	srand( 5 );
	int kingdoms[] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	struct gameState state, init;
	int cp, value = 0, bonus = 10, r0, r1, card;

	clear( state );
	initializeGame( 4, kingdoms, 3, &state );
	cp = whoseTurn( &state );
	range( card, 0, MAX_HAND ) {
		state.hand[ cp ][ card ] = rand() % ( treasure_map + 1 );
		if ( state.hand[ cp ][ card ] == copper ) {
			value += 1;
		}
		else if ( state.hand[ cp ][ card ] == silver ) {
			value += 2;
		}
		else if ( state.hand[ cp ][ card ] == gold ) {
			value += 3;
		}
	}
	state.handCount[ cp ] = MAX_HAND;
	state.coins = 0;
	clear( init );
	copy( init, state );
	r0 = updateCoins( cp, &state, bonus );
	r1 = ( init.coins + value + bonus == state.coins );

	if ( r0 ) printf( "failed: updateCoins( cp, &state, bonus ) == %d\n", r0 );
	if ( ! r1 ) printf( "failed: ( init.coins + hand value + bonus == state.coins ): ( %d, %d )\n", init.coins + value + bonus, state.coins );
	( ! r0 && r1 ) ? printf( "TEST PASSED\n" ) : printf( "TEST FAILED\n" );
	return 0;
}