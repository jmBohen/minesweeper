#include "board.h"
#include "user_interface.h"
#include "definitions.h"
#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

void print_scoreboard(Board board){
    int score = 0;
    score = calculate_score(board);
    printw("Score: %d\n", score);
    printw("\n");
    refresh();
}

// prints board as covered matrix
void print_board(Board board){
    clear();
    print_scoreboard(board);
    printw("\n||");
    for (int i = 0; i < board -> size_r; i++){
      printw("=");
      refresh();
    }
    printw("||\n");

    for (int y = 0; y < board -> size_c; y++){
        printw("||");
        for (int x = 0; x < board -> size_r; x++){
            Square square = board -> squares[y* board -> size_r + x];

            //if is flagged - means you cannot flag revealed square
            if (square -> is_flagged) printw("F");
            //if just unrevealed
            else if (!square -> is_revealed) addch(ACS_CKBOARD);
            //if is revealed  and mine
            else if (square -> is_mine) addch('*');
            //if revealed and has no neighbour mines
            else if (square -> number_of_neighbour_mines == 0) printw(" ");
            //if revealed and has any neighbour mines
            else printw("%d", square -> number_of_neighbour_mines);

            refresh();
        }
        printw("|\n");
    }

    printw("||");
    for (int i = 0; i < board -> size_r; i++){
      printw("=");
      refresh();
    }
    printw("||\n\n");
    refresh();
}

// prints board as uncovered matrix
void dev_print_board(Board board){
    clear();
    printw("\n\n||");
    for (int i = 0; i < board -> size_r; i++){
      printw("=");
      refresh();
    }
    printw("||\n");

    for (int y = 0; y < board -> size_c; y++){
        printw("||");
        for (int x = 0; x < board -> size_r; x++){
            Square square = board -> squares[y* board -> size_r + x];

            //if is flagged - means you cannot flag revealed square
            if (square -> is_flagged) printw("%c", FLAG_CHAR);
            //if just unrevealed
            //else if (!square -> is_revealed) printw("%c", UNREVEALED_CHAR);
            //if is revealed  and mine
            else if (square -> is_mine) printw("%c", MINE_CHAR);
            //if revealed and has no neighbour mines
            //else if (square -> number_of_neighbour_mines == 0) printw("%c", REVEALED_CLEAR_CHAR);
            //if revealed and has any neighbour mines
            else printw("%d", square -> number_of_neighbour_mines);

            refresh();
        }
        printw("||\n");
    }

    printw("||");
    for (int i = 0; i < board -> size_r; i++){
      printw("=");
      refresh();
    }
    printw("||\n");
    refresh();
}