#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include "board.h"
#include "ncurses.h"


int main(){
    //ncurses initialization
    setlocale(LC_ALL, "");
    initscr();
    cbreak();

    Board game;

    start_game(game);

    endwin();
    return 0;
}