/* Brian Palmer - village_fn() */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "rngs.h"
#include "dominion.h"

#define clear( x ) memset( & x, '\0', sizeof( x ))
#define copy( x, y ) memcpy( & x, & y, sizeof( x ))
#define range( x, y, z ) for ( x = y; x < z; x++ )
#define check( x, y ) memcmp( & x, & y, sizeof( x ))
#define NUMT 2000

void fuzz( struct gameState * state ) {
	int n;
	for ( n = 0; n < sizeof( struct gameState ); n++ ) {
		(( char * ) state )[ n ] = rand() % 128;
	}
}

void comp( struct gameState * pre, struct gameState * post ) {
	int i;
	for ( i = 0; i < sizeof( struct gameState ); i++ ) {
		if ((( char * ) pre )[ i ] != (( char * ) post )[ i ] ) {
			printf( "%d :: (%c, %c)\n", i , (( char * ) pre )[ i ], (( char * ) post )[ i ] );
		}
	}
	return;
}

int diff( struct gameState * pre, struct gameState * post ) {
	int i, j = 0;
	for ( i = 0; i < sizeof( struct gameState ); i++ ) {
		if ((( char * ) pre )[ i ] != (( char * ) post )[ i ] ) {
			j++;
		}
	}
	return j;
}

int checkVillage( int card, struct gameState * pre, struct gameState * post, int pos, int * bonus ) {
	int p = whoseTurn( pre );
	cardEffect( card, -1, -1, -1, post, 5, bonus );
	drawCard( p, pre );
	pre->numActions += 2;
	discardCard( pos, p, pre, 0 );

	return diff( pre, post );
}
void catch_sigint( int signo ) {
	write( STDOUT_FILENO, "\n\nCaught Segfault.\n", 20 );
	exit( 0 );
}

void catch_abort( int signo ) {
	write( STDOUT_FILENO, "\n\nCaught Abort.\n", 17 );
	exit( 0 );
}
int main( void ) {

	srand( 10 );
	int kingdoms[] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	struct gameState post, pre;
	int bonus, i, j, p, n;

	struct sigaction sigseg_action = { 0 };
	sigseg_action.sa_handler = catch_sigint;
	sigfillset( &sigseg_action.sa_mask );
	sigseg_action.sa_flags = 0;

	sigaction( SIGSEGV, &sigseg_action, NULL );

	struct sigaction abort_action = { 0 };
	abort_action.sa_handler = catch_abort;
	sigfillset( &abort_action.sa_mask );
	abort_action.sa_flags = 0;

	sigaction( SIGABRT, &abort_action, NULL );

	for ( n = 0; n < 2000; n++ ) {
		clear( post );
		fuzz( &post );
		bonus = rand() % 100 + 1;
		post.numPlayers = rand() % 4 + 1;
		range( i, 0, post.numPlayers ) {
			post.deckCount[ i ] = rand() % ( MAX_DECK + 1 );
			range( j, 0, post.deckCount[ i ] ) {
				post.deck[ i ][ j ] = rand() % (treasure_map + 1);
			}
			post.handCount[ i ] = rand() % ( MAX_HAND );
			range( j, 0, post.handCount[ i ] ) {
				post.hand[ i ][ j ] = rand() % ( treasure_map + 1 );
			}
			post.playedCardCount = rand() % 128;
			range( j, 0, post.playedCardCount ) {
				post.playedCards[ j ] = rand() % ( treasure_map + 1 );
			}
			post.hand[ i ][ j ] = village;
			post.handCount[ i ]++;
			post.discardCount[ i ] = rand() % ( MAX_DECK + 1 );

			range( j, 0, post.discardCount[ i ] ) {
				post.discardCount[ j ] = rand() % (treasure_map + 1);
			}
		}
		p = post.whoseTurn = rand() % post.numPlayers;
		post.numActions = rand() % 100;
		clear( pre );
		copy( pre, post );
		int r = checkVillage( village, &pre, &post, 5, &bonus );
		if ( r ) {
			printf( "ERROR (%d): %d\n", n, r );
			printf( "pre->numActions: %d\tpost->numAction: %d\n", pre.numActions, post.numActions );
			printf( "pre->deckCount: %d\tpost->deckCount: %d\n", pre.deckCount[ p ], post.deckCount[ p ] );
			printf( "pre->handCount: %d\tpost->handCount: %d\n", pre.handCount[ p ], post.handCount[ p ] );
			printf( "pre->discardCount: %d\tpost->discardCount: %d\n", pre.discardCount[ p ], post.discardCount[ p ] );
			compare( &pre, &post );
		}
	}

	return 0;
}