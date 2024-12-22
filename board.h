#ifndef _BOARD_H_
#define _BOARD_H_

#define SMALL_BOARD 9
#define SMALL_TIME_MINUTES 10

#define MEDIUM_BOARD 16
#define SMALL_TIME_MINUTES 20

#define LARGE_BOARD_R 16
#define LARGE_BOARD_C 30
#define LARGE_TIME_MINUTES 40

// struct for the board
typedef struct {
    int size_r;
    int size_c;
    Square *squares;
    int num_mines;
    
} *Board;

typedef struct {
    int row;
    int column;
    int is_mine;
    int is_revealed;
    int is_flagged;
    int number_of_neighbour_mines;
} *Square; 


// function prototypes


#endif