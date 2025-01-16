#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
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

    while ((opt = getopt(argc, argv, "f:t")) != -1) {
        switch (opt) {
            case 'f':
                filepath = optarg;
                break;
            case 't':
              	start_game_tui(game);
                endwin();
                return 0;
            default:
                fprintf(stderr, "Usage: %s [-f filepath] [-t]\n", argv[0]);
                exit(EXIT_FAILURE);
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