#ifndef _BOARD_H_
#define _BOARD_H_

#include "definitions.h"


// struct for single squares of the board
typedef struct {
    int row;
    int column;
    int is_mine;
    int is_revealed;
    int is_flagged;
    int number_of_neighbour_mines;
} *Square;

// struct for the board
typedef struct {
    int size_r;
    int size_c;
    int number_of_mines;
    int time_in_minutes;
    int is_game_started;
    Square *squares;
    
} *Board;

 


// function prototypes

void set_settings(Board board);

void initialize_board(Board board);

void print_board(Board board);

void start_game(Board board);

void get_square_neighbours(Board board, Square square);

void get_number_of_square_neighbours(Board board, Square square);



#endif