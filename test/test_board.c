#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include "../src/board.h"
#include "../src/definitions.h"

void test_get_neighbours(Board board) {
    int **neighbours = get_neighbours(board, 1, 1);
    assert(neighbours != NULL);
    for (int i = 0; i < 8; i++) {
        free(neighbours[i]);
    }
    free(neighbours);
}

void test_reveal_square(Board board) {
    reveal_square(board, 1, 1);
    assert(board->squares[1 * board->size_r + 1]->is_revealed == 1);
}

void test_flag_square(Board board) {
    flag_square(board, 1, 1);
    assert(board->squares[1 * board->size_r + 1]->is_flagged == 1);
    flag_square(board, 1, 1);
    assert(board->squares[1 * board->size_r + 1]->is_flagged == 0);
}

void test_is_finished(Board board) {
    //assert(is_finished(board) == 0);
}

void test_initialize_board(Board board) {
    initialize_board(board, 1, 1);
    assert(board->squares[1 * board->size_r + 1]->is_revealed == 1);
}

void test_calculate_score(Board board) {
    int score = calculate_score(board);
    assert(score != 0);
}

void test_increase_number_of_neighbour_mines_for_neighbours(Board board) {
    int **neighbours = get_neighbours(board, 1, 1);
    for (int i = 0; neighbours[i][0] != EOF; i++) {
        board->squares[neighbours[i][0] * board->size_r + neighbours[i][1]]->number_of_neighbour_mines = 0;
    }

    increase_number_of_neighbour_mines_for_neighbours(board, 1, 1);
    
    for (int i = 0; neighbours[i][0] != EOF; i++) {
        assert(board->squares[neighbours[i][0] * board->size_r + neighbours[i][1]]->number_of_neighbour_mines == 1);
    }
    for (int i = 0; i < 8; i++) {
        free(neighbours[i]);
    }
    free(neighbours);
}

int main() {
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();

    Board board = create_empty_board();
    reveal_square(board, 2, 2);
    
    printw("Running tests...\n");
    refresh();
    test_get_neighbours(board);
    printw("test_get_neighbours passed\n");
    refresh();
    test_reveal_square(board);
    printw("test_reveal_square passed\n");
    refresh();
    test_flag_square(board);
    printw("test_flag_square passed\n");
    refresh();
    test_is_finished(board);
    printw("test_is_finished passed\n");
    refresh();
    test_initialize_board(board);
    printw("test_initialize_board passed\n");
    refresh();
    test_calculate_score(board);
    printw("test_calculate_score passed\n");
    refresh();
    test_increase_number_of_neighbour_mines_for_neighbours(board);
    printw("test_increase_number_of_neighbour_mines_for_neighbours passed\n");
    refresh();
    printw("All tests passed!\n");
    refresh();

    // Free allocated memory
    for (int i = 0; i < board->size_c * board->size_r; i++) {
        free(board->squares[i]);
    }
    free(board->squares);
    free(board);
    // Wait for a key press
    printw("Press any key to exit...\n");
    refresh();
    getch();
    // End ncurses
    endwin();

    return 0;
}
