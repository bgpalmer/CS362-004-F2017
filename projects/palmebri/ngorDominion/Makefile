CFLAGS = -Wall -fpic -coverage -lm -fprofile-arcs -ftest-coverage

file = "unittestresults.out"

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

unittest1: unittest1.o dominion.o
	gcc -o unittest1 unittest1.o dominion.o rngs.o -g $(CFLAGS)

unittest1.o: unittest1.c
	gcc -c unittest1.c -g $(CFLAGS)

unittest2: unittest2.o dominion.o rngs.o
	gcc -o unittest2 unittest2.o dominion.o rngs.o -g $(CFLAGS)

unittest2.o: unittest2.c
	gcc -c unittest2.c -g $(CFLAGS)

unittest3: unittest3.o dominion.o rngs.o
	gcc -o unittest3 unittest3.o dominion.o rngs.o -g $(CFLAGS)

unittest3.o: unittest3.c
	gcc -c unittest3.c -g $(CFLAGS)

unittest4: unittest4.o dominion.o rngs.o
	gcc -o unittest4 unittest4.o dominion.o rngs.o -g $(CFLAGS)

unittest4.o: unittest4.c
	gcc -c unittest4.c -g $(CFLAGS)

cardtest1: cardtest1.o dominion.o rngs.o
	gcc -o cardtest1 cardtest1.o dominion.o rngs.o -g $(CFLAGS)

cardtest1.o: cardtest1.c
	gcc -c cardtest1.c -g $(CFLAGS)

cardtest2: cardtest2.o dominion.o rngs.o
	gcc -o cardtest2 cardtest2.o dominion.o rngs.o -g $(CFLAGS)

cardtest2.o: cardtest2.c
	gcc -c cardtest2.c -g $(CFLAGS)

cardtest3: cardtest3.o dominion.o rngs.o
	gcc -o cardtest3 cardtest3.o dominion.o rngs.o -g $(CFLAGS)

cardtest3.o: cardtest3.c
	gcc -c cardtest3.c -g $(CFLAGS)

cardtest4: cardtest4.o dominion.o rngs.o
	gcc -o cardtest4 cardtest4.o dominion.o rngs.o -g $(CFLAGS)

cardtest4.o: cardtest4.c
	gcc -c cardtest4.c -g $(CFLAGS)

randomtestcard1: randomtestcard1.o dominion.o rngs.o
	gcc -o randomtestcard1 randomtestcard1.o dominion.o rngs.o -g $(CFLAGS)

randomtestcard1.o: randomtestcard1.c
	gcc -c randomtestcard1.c -g $(CFLAGS)

randomtestcard2: randomtestcard2.o dominion.o rngs.o
	gcc -o randomtestcard2 randomtestcard2.o dominion.o rngs.o -g $(CFLAGS)

randomtestcard2.o: randomtestcard2.c
	gcc -c randomtestcard2.c -g $(CFLAGS)

randomtestcard3: randomtestcard3.o dominion.o rngs.o
	gcc -o randomtestcard3 randomtestcard3.o dominion.o rngs.o -g $(CFLAGS)

randomtestcard3.o: randomtestcard3.c
	gcc -c randomtestcard3.c -g $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

randomtestadventurer.out: randomtestcard1
	./$^ > $@
	gcov -b dominion.c >> $@
	cat dominion.c.gcov >> $@
	rm -f dominion.gcda

randomtestcard1.out: randomtestcard2
	./$^ > $@
	gcov -b dominion.c >> $@
	cat dominion.c.gcov >> $@
	rm -f dominion.gcda

randomtestcard2.out: randomtestcard3
	./$^ > $@
	gcov -b dominion.c >> $@
	cat dominion.c.gcov >> $@
	rm -f dominion.gcda

unittestresults.out: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	./unittest1 > ${file}
	gcov -b dominion.c >> ${file}
	cat dominion.c.gcov >> ${file}
	rm -f dominion.gcda

	./unittest2 >> ${file}
	gcov -b dominion.c >> ${file}
	cat dominion.c.gcov >> ${file}
	rm -f dominion.gcda

	./unittest3 >> ${file}
	gcov -b dominion.c >> ${file}
	cat dominion.c.gcov >> ${file}
	rm -f dominion.gcda

	./unittest4 >> ${file}
	gcov -b dominion.c >> ${file}
	cat dominion.c.gcov >> ${file}
	rm -f dominion.gcda

	./cardtest1 >> ${file}
	gcov -b dominion.c >> ${file}
	cat dominion.c.gcov >> ${file}
	rm -f dominion.gcda

	./cardtest2 >> ${file}
	gcov -b dominion.c >> ${file}
	cat dominion.c.gcov >> ${file}
	rm -f dominion.gcda

	./cardtest3 >> ${file}
	gcov -b dominion.c >> ${file}
	cat dominion.c.gcov >> ${file}
	rm -f dominion.gcda

	./cardtest4 >> ${file}
	gcov -b dominion.c >> ${file}
	cat dominion.c.gcov >> ${file}
	rm -f dominion.gcda

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
