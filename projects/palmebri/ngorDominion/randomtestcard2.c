#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include "rngs.h"
#include "dominion.h"

#define clear( x ) memset( & x, '\0', sizeof( x ))
#define copy( x, y ) memcpy( & x, & y, sizeof( x ))
#define range( x, y, z ) for ( x = y; x < z; x++ )
#define check( x, y ) memcmp( & x, & y, sizeof( x ))

void fuzz( struct gameState * state ) {
	int n;
	for ( n = 0; n < sizeof( struct gameState ); n++ ) {
		(( char * ) state )[ n ] = rand() % 128;
	}
}

void diff( struct gameState * pre, struct gameState * post ) {
	int i, j;
	for ( i = 0; i < sizeof( struct gameState ); i += 4 ) {
		if ( ( int )(( char * ) pre )[ i ] != ( int )(( char * ) post )[ i ] ) {
			printf( "%d :: (%d, %d)\n", i / 4, ( int )(( char * ) pre )[ i ], ( int )(( char * ) post )[ i ] );
		}
	}
}


void checkSmithy( int card, struct gameState * pre, struct gameState * post, int pos, int * bonus ) {
	int p, i;
	cardEffect( card, -1, -1, -1, post, pos, bonus );

	/* ORACLE */

	p = whoseTurn( pre );
	for ( i = 0; i < 3; i++ ) {
		drawCard( p, pre );
	}
	discardCard( pos, p, pre, 0 );
}

void catch_sigint( int signo ) {
	write( STDERR_FILENO, "\n\nCaught Segfault.\n", 20 );
	exit( 0 );
}

void catch_abort( int signo ) {
	write( STDERR_FILENO, "\n\nCaught Abort.\n", 17 );
	exit( 0 );
}

int main( void ) {
	srand( 10 );
	int kingdoms[] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	struct gameState post, pre, init;
	int r, bonus, k, p, i, j, n;

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

	r = 1;

	range( n, 0, 1000 ) {
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
			post.hand[ i ][ j ] = adventurer;
			post.handCount[ i ]++;
			post.discardCount[ i ] = rand() % ( MAX_DECK + 1 );
			range( j, 0, post.discardCount[ i ] ) {
				post.discardCount[ j ] = rand() % (treasure_map + 1);
			}
		}
		post.whoseTurn = rand() % post.numPlayers;


		clear( pre );
		clear( init );
		copy( pre, post );
		copy( init, post );
		if ( check( pre, post )) {
			fprintf( stderr, "*** ABORT: state initialization failure *** \n" );
			fprintf( stderr, "check failed\n" );
			break;
		} else {
			checkSmithy( smithy, &pre, &post, 5, &bonus );
			if ( check( pre, post )) {
				printf( "\nTEST %d FAILED\n\n", n );
				diff( &pre, &post );
				r = 0;
			}
		}


	}
	r ? printf( "\n\nRESULT: SUCCESS\n" ) : printf( "\n\nRESULT: FAILED\n" );
	return 0;
}