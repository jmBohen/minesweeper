#include "board.h"
#include "definitions.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>


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
            printf("Dupa1");
            board -> size_c = SMALL_BOARD;
            board -> size_r = SMALL_BOARD;
            board -> number_of_mines = SMALL_NUMBER_OF_MINES;
            board -> time_in_minutes = SMALL_TIME_MINUTES;
            return;
        //setting up default medium board
        case MEDIUM_SYMBOL:
            printf("Dupa2");
            board -> size_c = MEDIUM_BOARD;
            board -> size_r = MEDIUM_BOARD;
            board -> number_of_mines = MEIDUM_NUMBER_OF_MINES;
            board -> time_in_minutes = MEIDUM_TIME_MINUTES;
            return;
        //setting up default large board
        case LARGE_SYMBOL:
            printf("Dupa3");
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

//creating empty board ready for first click; includes set settings
Board create_empty_board(){
    Board board = malloc(sizeof(Board));
    set_settings(board);
    board -> squares = malloc(board -> size_c * board -> size_r * sizeof(Square));
    
    for (int i = 0; i < board -> size_c * board -> size_r; i++){
        board -> squares[i] = malloc(sizeof(Square));
        board -> squares[i] -> is_revealed = 0;
        board -> squares[i] -> is_mine = 0;
        board -> squares[i] -> is_flagged = 0;
    }
    return board;
}

//sets up board after first click
void initialize_board(Board board, int r, int c){
    //marking first clicked square as revealed
    board -> squares[r * board -> size_r + c] -> is_revealed = 1;
    
    //randomly selecting mines coordinates 
    //avoiding:
    //- first clicked square
    //- setting mine twice at the same place
    int correctly_added_mines = 0;
    srand(time(0));
    int rand_r;
    int rand_c;
    while (correctly_added_mines < board -> number_of_mines){
        rand_r = rand() % (board -> size_r - 1);
        rand_c = rand() % (board -> size_c - 1);

        //skipping already set mines
        if(board -> squares[rand_r * board -> size_r + rand_c] -> is_mine) continue;
        //skipping first clicked square
        else if(rand_r == r && rand_c == c) continue;
        else{
            board -> squares[rand_r * board -> size_r + rand_c] -> is_mine = 1;
            correctly_added_mines++;
            increase_number_of_neighbour_mines_for_neighbours(board, rand_r, rand_c);
        }
    }
}

// prints board as matrix
void print_board(Board board){
    for (int y = 0; y < board -> size_c; y++){
        for (int x = 0; x < board -> size_r; x++){
            Square square = board -> squares[y* board -> size_r + x];

            //if is flagged - means you cannot flag revealed square
            if (square -> is_flagged) printf("%c", FLAG_CHAR);
            //if just unrevealed 
            else if (!square -> is_revealed) printf("%c", UNREVEALED_CHAR);
            //if is revealed  and mine
            else if (square -> is_mine) printf("%c", MINE_CHAR);
            //if revealed and has no neighbour mines
            else if (square -> number_of_neighbour_mines == 0) printf("%c", REVEALED_CLEAR_CHAR);
            //if revealed and has any neighbour mines
            else printf("%d", square -> number_of_neighbour_mines);

        }
        printf("\n");
    }
}

//starts the game
void start_game(Board board){
    board = create_empty_board();
    initialize_board(board, 2, 2);
    print_board(board);

}

void increase_number_of_neighbour_mines_for_neighbours(Board board, int r, int c){
    //List:

    // s0 s1 s2
    // s3 rc s4
    // s5 s6 s7

    //s0 s1 s2 s3 s4 s5 s6 s7
    //r0 r1 r2 r3 r4 r5 r6 r7
    int *neighbour_rows_list = malloc(8 * sizeof(int));
    //c0 c1 c2 c3 c4 c5 c6 c7
    int *neighbour_columns_list = malloc(8 * sizeof(int));

    // setting indexes
    neighbour_rows_list[0] = neighbour_rows_list[1] = neighbour_rows_list[2] = r - 1;
    neighbour_rows_list[3] = neighbour_rows_list[4] = r;
    neighbour_rows_list[5] = neighbour_rows_list[6] = neighbour_rows_list[7] = r + 1;
    neighbour_columns_list[0] = neighbour_columns_list[3] = neighbour_columns_list[5] = c - 1;
    neighbour_columns_list[1] = neighbour_columns_list[6] = c;
    neighbour_columns_list[2] = neighbour_columns_list[4] = neighbour_columns_list[7] = c + 1;

    for (int i = 0; i < 8; i++){
        //check if neighbours fit board
        if(neighbour_rows_list[i] >= 0 &&
        neighbour_rows_list[i] >= board-> size_r &&
        neighbour_columns_list[i] >= 0 &&
        neighbour_columns_list[i] >= board-> size_c){
            //increase number of neighbour mines
            board -> squares[neighbour_rows_list[i] * board -> size_r + neighbour_columns_list[i]] -> number_of_neighbour_mines += 1;
        }
    }
}

