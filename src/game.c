#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "board.h"
#include "ncurses.h"

int main(int argc, char *argv[]){
    //ncurses initialization
    initscr();
    cbreak();
    start_color();

    int opt;
    char *filepath = NULL;
    Board game;

    while ((opt = getopt(argc, argv, "f:")) != -1) {
        if (opt == 'f') {
            filepath = optarg;
        }
    }

    if (filepath != NULL) {
        game_from_file(game, filepath);
    } else {
        start_game(game);
    }

    endwin();
    return 0;
}