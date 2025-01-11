#ifndef _BOARD_H_
#define _BOARD_H_

typedef struct {
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
    Square *squares;
    int num_mines;
    int number_of_revealed_squares;
    char difficulty;

} *Board;

//creating empty board ready for first click; includes set settings
Board create_empty_board();

// setting up the game settings: board size, number of mines, time
void set_settings(Board board);

//reveal clicked square
void reveal_square(Board board, int r, int c);

void flag_square(Board board, int r, int c);

//sets up board after first click
void initialize_board(Board board, int r, int c);

// prints board as matrix
void print_board(Board board);

void dev_print_board(Board board);

//checks if you won the game and unreaveld all clear squares
int is_finished(Board board);

//standard input for the game ("f x y" or "r x y")
void standard_input(Board board);

//starts the game
void start_game(Board board);

// function pvoid increase_number_of_neighbour_mines_for_neighbours(Board board, int r, int c)rototypes
void increase_number_of_neighbour_mines_for_neighbours(Board board, int r, int c);

//get list of neighbours for coordinates
int** get_neighbours(Board board, int r, int c);

void finish_game(Board board);

#endif