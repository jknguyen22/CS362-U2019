CFLAGS= -Wall -fpic -coverage -lm -std=c99

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
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

unittestresults.out:
	make clean; make randomtestresults;

randomtestresults: randomtestcard1 randomtestcard2 randomtestcard3
	touch unittestresults.out

	./randomtestcard1 >> randomtestresults.out
	./randomtestcard2 >> randomtestresults.out
	./randomtestcard3 >> randomtestresults.out

	gcov -b randomtestcard1.c >> randomtestresults.out
	gcov -b randomtestcard2.c >> randomtestresults.out
	gcov -b randomtestcard3.c >> randomtestresults.out

	gcov dominion.c -b -f >> randomtestresults.out
	cat randomtestresults.out

randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)

randomtestcard3: randomtestcard3.c dominion.o rngs.o
	gcc -o randomtestcard3 -g  randomtestcard3.c dominion.o rngs.o $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player randomtestresults

clean:
	rm -f *.o playdom.exe playdom player player.exe test.exe test unittestresults *.gcov *.gcda *.gcno *.so *.out unittest1 unittest1.exe unittest2 unittest2.exe unittest3 unittest3.exe unittest4 unittest4.exe unittest5 unittest5.excardtest1 cardtest1.exe cardtest2 cardtest2.exe cardtest3 cardtest3.exe cardtest4 cardtest4.exe cardtest5 cardtest5.exe randomtestcard1.exe randomtestcard2.exe randomtestcard3.exe