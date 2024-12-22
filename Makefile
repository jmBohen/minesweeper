bin/minesweeper.o: bin/game.o bin/board.o
	cc -g -o bin/minesweeper.o bin/game.o bin/board.o

bin/game.o: src/game.c
	cc -g -o bin/game.o -c src/game.c

bin/board.o: src/board.c
	cc -g -o bin/board.o -c src/board.c