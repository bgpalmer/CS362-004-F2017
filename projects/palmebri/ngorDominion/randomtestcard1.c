/* Brian Palmer - adventurer_fn() */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>
#include <stdarg.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

#include "dominion.h"
#include "rngs.h"
#define range( x, y, z ) for ( x = y; x < z; x++ )
#define clear( x ) memset( & x, '\0', sizeof( x ))
#define copy( x, y ) memcpy( & x, & y, sizeof( x ))
#define check( x, y ) memcmp( & x, & y, sizeof( x ))
#define N 25
#define NOISY 1



void fuzz( struct gameState * state ) {
	int n;
	for ( n = 0; n < sizeof( struct gameState ); n++ ) {
		( rand() % 2 ) ? \
		(( char * ) state )[ n ] = rand() % 128 : \
		(( char * ) state )[ n ] << 0;
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

int checkAdventurer( int card, struct gameState * pre, struct gameState * post, int pos, int * bonus ) {
	int k, c, t, p, i;
	cardEffect( card, -1, -1, -1, post, 5, bonus );
	/* ORACLE */
	
	t = k = 0;
	p = whoseTurn( pre );
	int tempHand[ MAX_DECK ];

	while ( k < 2 ) {
		c = drawCard( p, pre );
		if ( c == -1 ) { 
			break;
		} 
		if ( c == copper || c == silver || c == gold ) {
			k++;
		} else {
			tempHand[ t++ ] = c; 
		}
	}
	while ( t >= 0 ) {
		pre->discard[ p ][ pre->discardCount[ p ]] = tempHand[ t-- ];
		pre->discardCount[ p ]++;
	}
	return check( pre, post );
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

	srand( 24 );
	int kingdoms[] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	struct gameState post, pre;
	int bonus, i, j, p;

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

	for ( i = 0; i < 2000; i++ ) {
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
		p = post.whoseTurn = rand() % post.numPlayers;
		clear( pre );
		copy( pre, post );
		if ( checkAdventurer( adventurer, &pre, &post, 5, &bonus )) {
			printf( "\nTEST FAILED\n\n" );
			printf( "ATTRIBUTE\t\tPRE\tPOST\n");
			printf( "handCount\t\t%d\t%d\n", pre.handCount[ p ], post.handCount[ p ]);
			printf( "deckCount\t\t%d\t%d\n", pre.deckCount[ p ], post.deckCount[ p ]);
			printf( "discardCount\t\t%d\t%d\n", pre.discardCount[ p ], post.discardCount[ p ]);
		} else { 
			printf( "\nTEST PASSED\n\n" );
			printf( "ATTRIBUTE\t\tPRE\tPOST\n");
			printf( "handCount\t\t%d\t%d\n", pre.handCount[ p ], post.handCount[ p ]);
			printf( "deckCount\t\t%d\t%d\n", pre.deckCount[ p ], post.deckCount[ p ]);
			printf( "discardCount\t\t%d\t%d\n", pre.discardCount[ p ], post.discardCount[ p ]);
		}
	}

	return 0;
}