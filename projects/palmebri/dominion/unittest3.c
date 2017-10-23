/* brian palmer - unittest3.c */

/* isGameOver() */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "rngs.h"
#include "dominion.h"

#define clear( x ) memset( & x, '\0', sizeof( x ))
#define range( x, y, z ) for ( x = y; x < z; x++ )
#define intfill( x, y, z ) range( z, 0, sizeof( x ) / sizeof( int )) x[ z ] = y;

#define check( expect, actual ) ( expect == actual ) ? ( printf( "PASSED\n" )) : ( printf( "FAILED\n"))
#define YES 1
#define NO 0

int main( void ) {
	int r, z, player_k = 4;
	int kingdoms[] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	struct gameState state;
	
	/* Zero Provinces - Game is over */
	printf("Zero Provinces - Game is over: ");
	clear( state );
	initializeGame( player_k, kingdoms, 3, &state );
	state.supplyCount[ province ] = 0;
	r = isGameOver( &state );
	check( YES, r );

	/* One or More Provinces exist - no supplies equal zero */
	printf( "One or More Provinces exist - no supplies equal zero: ");
	clear( state );
	initializeGame( player_k, kingdoms, 3, &state );
	intfill( state.supplyCount, 1, z );
	r = isGameOver( &state );
	check( NO, r );

	/* Two supplies are at zero */
	printf( "Two supplies are at zero: " );
	state.supplyCount[ 0 ] = 0;
	state.supplyCount[ 1 ] = 0;
	r = isGameOver( &state );
	check( NO, r );

	/* Three supplies are at zero */
	printf( "Three supplies are at zero: " );
	state.supplyCount[ 2 ] = 0;
	r = isGameOver( &state );
	check( YES, r );

	/* All supplies are at zero */
	printf( "All supplies are at zero: " );
	intfill( state.supplyCount, 0, z );
	r = isGameOver( &state );
	check( YES, r );

	return 0;
}