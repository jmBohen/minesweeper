#ifndef _USER_INTERFACE_H_
#define _USER_INTERFACE_H_

#include "board.h"

// prints scoreboard
void print_scoreboard(Board board);

// prints time left
void print_time(Board board);

// prints board as matrix
void print_board(Board board);

// print board with active field
void print_board_tui(Board board, int row, int column);

// prints game from file summary
void print_game_from_file_summary(Board board, int total_moves);

void dev_print_board(Board board);

#endif