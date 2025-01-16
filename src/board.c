#include "board.h"
#include "definitions.h"
#include "user_interface.h"
#include "leaderboard.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <ncurses.h>
#include <string.h>


//creating empty board ready for first click; includes set settings
Board create_empty_board(){
    Board board = malloc(sizeof(*board));
    set_settings(board);
    board -> number_of_revealed_squares = 0;
    board -> squares = malloc(board -> size_c * board -> size_r * sizeof(Square));

    //Start a game timer
    board -> start_time = time(0);

    for (int i = 0; i < board -> size_c * board -> size_r; i++){
        board -> squares[i] = malloc(sizeof(Square));
        board -> squares[i] -> is_revealed = 0;
        board -> squares[i] -> is_mine = 0;
        board -> squares[i] -> is_flagged = 0;
        board -> squares[i] -> number_of_neighbour_mines = 0;
    }
    return board;
}


int** get_neighbours(Board board, int r, int c){
    //List:

    // s0 s1 s2
    // s3 rc s4
    // s5 s6 s7

    //s0 s1 s2 s3 s4 s5 s6 s7
    //r0 r1 r2 r3 r4 r5 r6 r7
    //c0 c1 c2 c3 c4 c5 c6 c7

    int **neighbours = malloc(9*sizeof(int*));
    for (int i = 0; i < 9; i++){
        neighbours[i] = malloc(2 * sizeof(int));
    }

    int neighbour_counter = 0;
    for (int r_piovt = -1; r_piovt <= 1; r_piovt++){
        for (int c_pivot = -1; c_pivot <= 1; c_pivot++){
            
            if(r_piovt == 0 && c_pivot ==0){
                continue;
            }

            if( r + r_piovt >= 0 &&
                r + r_piovt < board-> size_c &&
                c + c_pivot >= 0 &&
                c + c_pivot < board-> size_r){
                    neighbours[neighbour_counter][0] = r + r_piovt;
                    neighbours[neighbour_counter][1] = c + c_pivot;
                    neighbour_counter++;
                }
            
        }
    }
    neighbours[neighbour_counter][0] = EOF;
    neighbours[neighbour_counter][1] = EOF;

    return neighbours;
}


// setting up the game settings: board size, number of mines, time
void set_settings(Board board) {
    char symbol = '\0';
    int number = 0;
    
    while (1) {
        printw(SETTINGS_QUERY);
        refresh();

        // get char and make it upper case
        symbol = toupper(getch());

        switch (symbol) {
            case SMALL_SYMBOL:
                board->difficulty = SMALL_SYMBOL;
                board->size_c = SMALL_BOARD;
                board->size_r = SMALL_BOARD;
                board->number_of_mines = SMALL_NUMBER_OF_MINES;
                board->time_in_minutes = SMALL_TIME_MINUTES;
                refresh();
                return;

            case MEDIUM_SYMBOL:
                board->difficulty = MEDIUM_SYMBOL;
                board->size_c = MEDIUM_BOARD;
                board->size_r = MEDIUM_BOARD;
                board->number_of_mines = MEDIUM_NUMBER_OF_MINES;
                board->time_in_minutes = MEDIUM_TIME_MINUTES;
                refresh();
                return;

            case LARGE_SYMBOL:
                board->difficulty = LARGE_SYMBOL;
                board->size_c = LARGE_BOARD_C;
                board->size_r = LARGE_BOARD_R;
                board->number_of_mines = LARGE_NUMBER_OF_MINES;
                board->time_in_minutes = LARGE_TIME_MINUTES;
                refresh();
                return;

            case CUSTOM_SYMBOL:
                board->difficulty = CUSTOM_SYMBOL;

                while (1) {
                    printw(CUSTOM_SETTINGS_QUERY_R);
                    refresh();
                    if (scanw("%d", &number) != 1) {
                        printw("Invalid input. Please enter an integer.\n");
                        while (getch() != '\n');
                        refresh();
                        continue;
                    }
                    if (number < MINIMUM_SIZE || number > MAXIMUM_SIZE_R) {
                        printw("Number %d is out of range.\n", number);
                        refresh();
                        continue;
                    }
                    board->size_c = number;
                    break;
                }

                while (1) {
                    printw(CUSTOM_SETTINGS_QUERY_C);
                    refresh();
                    if (scanw("%d", &number) != 1) {
                        printw("Invalid input. Please enter an integer.\n");
                        while(getch() != '\n');  // clear invalid input
                        refresh();
                        continue;
                    }
                    if (number < MINIMUM_SIZE || number > MAXIMUM_SIZE_C) {
                        printw("Number %d is out of range.\n", number);
                        refresh();
                        continue;
                    }
                    board->size_r = number;
                    break;
                }

                board -> time_in_minutes = CUSTOM_TIME_MINUTES(board -> size_c, board -> size_r);
                board -> number_of_mines = CUSTOM_NUMBER_OF_MINES(board -> size_c, board -> size_r);
                return;

            default:
                printw("Invalid option. Please try again.\n");
                refresh();
                break;
        }
        clear();
    }
}

void check_if_game_over (Board board, int row, int column) {
    //if mine then game over
    if (board -> squares[row * board -> size_r + column] -> is_mine && !(board -> squares[row * board -> size_r + column] -> is_flagged)){
        clear();
        print_board(board);
        printw("\nGAME OVER\n");
        refresh();
        finish_game(board);
        exit(EXIT_SUCCESS);
    }

    if(is_finished(board)){
        clear();
        print_board(board);
        printw("YOU WON!\n");
        refresh();
        finish_game(board);
        exit(EXIT_SUCCESS);
    }
}

//on square click
void reveal_square(Board board, int r, int c){

    //if out of bounds abort
    if ((r < 0 || r >= board -> size_c) || (c < 0 || c >= board -> size_r)) return;
    //if already revealed abort
    if (board -> squares[r * board -> size_r + c] -> is_revealed) return;
    //do not reveal if square is flagged
    if (board -> squares[r * board -> size_r + c] -> is_flagged) return;

    //set square as revealed
    board -> squares[r * board -> size_r + c] -> is_revealed = 1;
    board -> number_of_revealed_squares++;

    //if doesnt have neighbouring mines - reveal neighbour squares
    if (!(board -> squares[r * board -> size_r + c] -> number_of_neighbour_mines) || board -> squares[r * board -> size_r + c] -> is_mine){
        int **neighbours = get_neighbours(board, r, c);
        for (int i = 0; neighbours[i][0] != EOF; i++){
            reveal_square(board, neighbours[i][0], neighbours[i][1]);
        } 
    }
}


void flag_square(Board board, int r, int c){
    //if out of bounds abort
    if ((r < 0 || r >= board -> size_c) || (c < 0 || c >= board -> size_r)) return;

    if (board -> squares[r * board -> size_r + c] -> is_flagged){
        board -> squares[r * board -> size_r + c] -> is_flagged = 0;
    } else {
        board -> squares[r * board -> size_r + c] -> is_flagged = 1;
    }
    
}


int is_finished(Board board){
    int current_time, time_left;

    //game over if time is up
    current_time = time(0);
    time_left = (board -> time_in_minutes * 60) - (current_time - board -> start_time);
    if (time_left <= 0){
        return 0;
    }

    for (int i = 0; i < board -> size_c * board -> size_r; i++){
        if( !(board -> squares[i] -> is_revealed) && !(board -> squares[i] -> is_mine)) return 0;
    }
    return 1;
}

//sets up board after first click
void initialize_board(Board board, int r, int c){
    //randomly selecting mines coordinates 
    //avoiding:
    //- first clicked square and its neighbours
    //- setting mine twice(correct at the same place
    int correctly_added_mines = 0;
    srand(time(0));
    int rand_r;
    int rand_c;
    while (correctly_added_mines < board -> number_of_mines){
        rand_c = rand() % board -> size_r;
        rand_r = rand() % board -> size_c;

        //skipping already set mines
        if(board -> squares[rand_r * board -> size_r + rand_c] -> is_mine) continue;

        //skipping first clicked square and its neighbours
        else if((rand_r == r && rand_c == c)||
                (rand_r == r - 1 && rand_c == c-1)||
                (rand_r == r - 1 && rand_c == c)||
                (rand_r == r - 1 && rand_c == c +1)||
                (rand_r == r && rand_c == c - 1)||
                (rand_r == r && rand_c == c + 1)||
                (rand_r == r + 1 && rand_c == c - 1)||
                (rand_r == r + 1 && rand_c == c)||
                (rand_r == r + 1 && rand_c == c + 1)) continue;
        else{
            board -> squares[rand_r * board -> size_r + rand_c] -> is_mine = 1;
            correctly_added_mines++;
            increase_number_of_neighbour_mines_for_neighbours(board, rand_r, rand_c);
        }
    }

    //reveal square
    reveal_square(board, r, c);
    //board -> squares[r * board -> size_r + c] -> is_revealed = 1;
}

void increase_number_of_neighbour_mines_for_neighbours(Board board, int r, int c){

    int **neighbours = get_neighbours(board, r, c);

    //increase number of surrounding mines for each neighbour
    for (int i = 0; neighbours[i][0] != EOF; i++){
        board -> squares[neighbours[i][0] * board -> size_r + neighbours[i][1]] -> number_of_neighbour_mines += 1;
    }
}

int calculate_score(Board board){
    float difficulty_factor = 0;

    switch (board -> difficulty){
        case SMALL_SYMBOL:
            difficulty_factor = 1.0;
            break;
        case MEDIUM_SYMBOL:
            difficulty_factor = 2.0;
            break;
        case LARGE_SYMBOL:
            difficulty_factor = 3.0;
            break;
        case CUSTOM_SYMBOL:
            difficulty_factor = 1.25;
            break;
    }
    int score = board -> number_of_revealed_squares * difficulty_factor;
    return score;
}

//standard input for the game ("f x y" or "r x y")
void standard_input(Board board) {
    char option;
    int row, column;

	printw(">");
   	scanw("%c %d %d", &option, &row, &column);

    switch(option) {
    	  case 'f':
			flag_square(board, row-1, column-1);
            break;
		  case 'r':
			reveal_square(board, row-1, column-1);
		    check_if_game_over(board, row-1, column-1);
            break;
          default:
            printw("Invalid input\n");
            refresh();
            break;
    }
}

// arrow control of the game
void tui_input(Board board, int *row, int *column, int *isInitialized) {
  	keypad(stdscr, TRUE);
	noecho();
	int ch = getch();
	keypad(stdscr, FALSE);
    echo();

    switch(ch) {
        case KEY_UP:
          	if (*row == 0) {
                *row = board -> size_c - 1;
            } else {
            	(*row)--;
            }
            break;
        case KEY_DOWN:
          	if (*row == board -> size_c - 1) {
                *row = 0;
            } else {
            	(*row)++;
            }
            break;
        case KEY_LEFT:
          	if (*column == 0) {
                *column = board -> size_r - 1;
            } else {
            	(*column)--;
            }
            break;
        case KEY_RIGHT:
            if (*column == board -> size_r) {
                *column = 0;
            } else {
            	(*column)++;
            }
            break;
        case 'f':
          	if (!*isInitialized) {
                printw("First move must be 'reveal'\n");
                refresh();
                break;
            }
            flag_square(board, *row, *column);
            break;
        case 'r':
            if (!*isInitialized) {
                initialize_board(board, *row, *column);
                *isInitialized = 1;
            } else {
                reveal_square(board, *row, *column);
            	check_if_game_over(board, *row, *column);
            }
            break;
        default:
            break;
    }
}

//starts the game
void start_game(Board board){
    char option;
    int row, column;
    int valid_firs_move = 0;
    board = create_empty_board();
    clear();
    print_scoreboard(board);
    print_time(board);
    print_board(board);

    do {
        printw("First click >");
        scanw("%c %d %d", &option, &row, &column);
        refresh();
        if (option == 'r') {
            valid_firs_move = 1;
        } else {
            printw("Invalid input! First move must be 'r'!\n");
            refresh();
        }
    } while (valid_firs_move == 0);

    //first click
    initialize_board(board, row-1, column-1);

    while (1){
        clear();
        print_scoreboard(board);
        print_time(board);
        print_board(board);
        standard_input(board);
    }

}

// starts the game in terminal user interface mode
void start_game_tui(Board board) {
    int row = 0, column = 0;
    int isInitialized = 0;
    board = create_empty_board();

    while (1){
    	clear();
    	print_scoreboard(board);
    	print_time(board);
    	print_board_tui(board, row, column);
        tui_input(board, &row, &column, &isInitialized);
    }
}

//calculate score and get name
void finish_game(Board board){
    int score = calculate_score(board);
    char name[50];
    for (int i = 0; i < board -> size_c * board -> size_r; i++) {
        if (board -> squares[i] -> is_mine && board -> squares[i] -> is_flagged == 0) {
            board -> squares[i] -> is_revealed = 1;
        }
    }
    
    print_board(board);
    refresh();
    printw("SCORE: %d\n", score);
    refresh();

    printw("Enter your name: ");
    refresh();
    scanw("%s", name);

    save_to_leaderboard(score, name);
    print_leaderboard();
    getch();

    endwin();
}

void game_from_file(Board board, char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        printw("Error: Could not open file %s\n", filepath);
        refresh();
        exit(EXIT_FAILURE);
    }

    char line[256];
    int row_count = 0;
    int col_count = 0;

    // Read the first line to determine the number of columns
    if (fgets(line, sizeof(line), file)) {
        for (char *p = line; *p != '\0'; p++) {
            if (*p == '=') {
                col_count++;
            }
        }
    }

    // Count the number of lines starting with "||" to determine the number of rows
    while (fgets(line, sizeof(line), file)) {
        if ((strncmp(line, "||", 2) == 0) && (line[2] != '=')) {
            row_count++;
        }
    }

    // Allocate memory for the board
    board = malloc(sizeof(*board));

    // Set the board settings
    board -> number_of_mines = 0;
    board -> time_in_minutes = 99;
    board -> number_of_revealed_squares = 0;
    board -> difficulty = 'C';

    // Allocate memory for the squares
    board->size_r = col_count;
    board->size_c = row_count;
    board->squares = malloc(row_count * col_count * sizeof(Square));
    for (int i = 0; i < board -> size_c * board -> size_r; i++) {
        board -> squares[i] = malloc(sizeof(Square));
        board -> squares[i] -> is_revealed = 0;
        board -> squares[i] -> is_mine = 0;
        board -> squares[i] -> is_flagged = 0;
        board -> squares[i] -> number_of_neighbour_mines = 0;
    }

    // Reset file pointer to the beginning
    rewind(file);

    int total_moves = 0;
    int row = 0;
    while (fgets(line, sizeof(line), file)) {
        // Parse the file to initialize the board
        if ((strncmp(line, "||", 2) == 0) && (line[2] != '=')) {
            for (int col = 0; col < col_count; col++) {
                char c = line[col + 2];
                if (c == '*') {
                    board -> squares[row * col_count + col] -> is_mine = 1;
                    board -> number_of_mines++;
                }  else if (isdigit(c)) {
                    board -> squares[row * col_count + col] -> number_of_neighbour_mines = c - '0';
                }
            }
            row++;
        }

        //Execute moves in the file
        if ((strncmp(line, "r", 1) == 0) || (strncmp(line, "f", 1) == 0)) {
            char option;
            int row, column;
            sscanf(line, "%c %d %d", &option, &row, &column);
            switch(option) {
                case 'f':
                    flag_square(board, row-1, column-1);
                    total_moves++;
                    break;
                case 'r':
                    reveal_square(board, row-1, column-1);
                    total_moves++;
                    break;
                default:
                    printw("Invalid input\n");
                    refresh();
                    break;
            }
        }
    }
    fclose(file);

    clear();
    printw("Game loaded from file %s\n", filepath);
    printw("Game ended in the state below:\n\n");
    printw("Total moves: %d\n", total_moves);
    print_scoreboard(board);
    print_board(board);
    printw("Press enter to continue\n");
    refresh();

    // Wait for enter key
    while (getch() != '\n');
}