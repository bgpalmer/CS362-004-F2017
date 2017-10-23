/* brian palmer - unittest4.c */

/* handCard() */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "rngs.h"
#include "dominion.h"

#define clear( x ) memset( & x, '\0', sizeof( x ))
#define range( x, y, z ) for ( x = y; x < z; x++ )

int main( void ) {
	srand( 3 );
	int players, player, hand, pos, turn, result = 1, c;
	int kingdoms[] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	struct gameState state;
	
	int players_hand_copy[ MAX_PLAYERS ][ MAX_HAND ];

	range( players, 2, MAX_PLAYERS ) {
		clear( state );
		initializeGame( players, kingdoms, 3, &state );
		range( player, 0, players ) {
			state.handCount[ player ] = rand() % ( MAX_HAND + 1 );
			range( hand, 0, state.handCount[ player ] ) {
				players_hand_copy[ player ][ hand ] = state.hand[ player ][ hand ] = rand() % ( treasure_map + 1 );
			}
		}
		range( turn, 0, players ) {
			range( pos, 0, state.handCount[ state.whoseTurn ] ) {
				c = 1;
				result &= c &= ( state.hand[ state.whoseTurn ][ pos ] == handCard( pos, &state ));
				if ( ! c ) printf( "ERROR: players_hand_copy[ player ][ hand ]: %d\n", players_hand_copy[ player ][ hand ] );
			}
			if ( ( ++state.whoseTurn ) >= players ) state.whoseTurn = 0;
		}
	}
	( result ) ? printf( "SUCCESS\n" ) : printf( "FAILURE\n") ;
	return 0;
}
