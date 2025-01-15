#ifndef _USER_INTERFACE_H_
#define _USER_INTERFACE_H_

#include "board.h"

// prints scoreboard
void print_scoreboard(Board board);

// prints time left
void print_time(Board board);

// prints board as matrix
void print_board(Board board);

// prints game from file summary
void print_game_from_file_summary(Board board, int total_moves);

void dev_print_board(Board board);

#endif