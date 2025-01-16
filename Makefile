# ncurses library is required to compile this program.
install_ncurses:
	@echo "Checking for ncurses..."
	@if ! ldconfig -p | grep -q libncurses; then \
		echo "ncurses is not installed. Installing..."; \
		sudo apt-get update && sudo apt-get install -y libncurses5-dev libncursesw5-dev; \
	else \
		echo "ncurses is installed."; \
	fi

CC = cc
LDFLAGS = -lncurses

bin/minesweeper: bin/game.o bin/board.o bin/user_interface.o bin/leaderboard.o
	$(CC) -o bin/minesweeper bin/game.o bin/board.o bin/user_interface.o bin/leaderboard.o $(LDFLAGS)
	

bin/game.o: src/game.c
	$(CC) -o bin/game.o -c src/game.c

bin/board.o: src/board.c
	$(CC) -o bin/board.o -c src/board.c

bin/user_interface.o: src/user_interface.c
	$(CC) -o bin/user_interface.o -c src/user_interface.c

bin/leaderboard.o: src/leaderboard.c
	$(CC) -o bin/leaderboard.o -c src/leaderboard.c

clean:
	rm -f bin/*.o
