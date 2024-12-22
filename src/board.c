#include "board.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

// setting up the game settings: board size, number of mines, time
void set_settings(Board board){
    char symbol;
    while(1){
        printf(SETTINGS_QUERY);
        
        // get char and make it upper case
        switch (toupper(symbol = getchar()))
        {
        //setting up default small board
        case SMALL_SYMBOL:
            board -> size_c = SMALL_BOARD;
            board -> size_r = SMALL_BOARD;
            board -> number_of_mines = SMALL_NUMBER_OF_MINES;
            board -> time_in_minutes = SMALL_TIME_MINUTES;
            return;
        //setting up default medium board
        case MEDIUM_SYMBOL:
            board -> size_c = MEDIUM_BOARD;
            board -> size_r = MEDIUM_BOARD;
            board -> number_of_mines = MEIDUM_NUMBER_OF_MINES;
            board -> time_in_minutes = MEIDUM_TIME_MINUTES;
            return;
        //setting up default large board
        case LARGE_SYMBOL:
            board -> size_c = LARGE_BOARD_C;
            board -> size_r = LARGE_BOARD_R;
            board -> number_of_mines = LARGE_NUMBER_OF_MINES;
            board -> time_in_minutes = LARGE_TIME_MINUTES;
            return;

        //setting up custom board
        case CUSTOM_SYMBOL:
            int number;
            while(1){
                printf(CUSTOM_SETTINGS_QUERY_R);
                if(scanf("%d", &number) != 1) {
                    while(getchar() != '\n'); // clear invalid input
                    printf("Invalid input. Please enter an integer.\n");
                    continue;
                }
                if(!(number >= MINIMUM_SIZE && number <= MAXIMUM_SIZE_R)) {
                    printf("Number %d is not in range\n", number);
                    while(getchar() != '\n');
                }
                else {
                    break;
                }
            }
            board -> size_r = number;
            
            while(1){
                printf(CUSTOM_SETTINGS_QUERY_C);
                if(scanf("%d", &number) != 1) {
                    while(getchar() != '\n'); // clear invalid input
                    printf("Invalid input. Please enter an integer.\n");
                    continue;
                }if(scanf("%d", &number)) {
                    while(getchar() != '\n');
                    printf("Invalid input. Please enter an integer.\n");
                    continue;
                }
                if(!(number >= MINIMUM_SIZE && number <= MAXIMUM_SIZE_C)) {
                    printf("Number %d is not in range\n", number);
                    while(getchar() != '\n');
                }
                else {
                    break;
                }
            }// clear invalid input
            board -> size_c = number;
            
            board -> time_in_minutes = CUSTOM_TIME_MINUTES(board -> size_c, board -> size_r);
            board -> number_of_mines = CUSTOM_NUMBER_OF_MINES(board -> size_c, board -> size_r);
            return;

        default:
            printf("Please enter correct input!\n");
            break;
        }
    }
    
}

void initialize_board(Board board){}

void print_board(Board board){}

void start_game(Board board){}

void get_square_neighbours(Board board, Square square){}

void get_number_of_square_neighbours(Board board, Square square){}
