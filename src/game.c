#include <stdlib.h>
#include <stdio.h>
#include "board.h"

int main(){
    Board board = malloc(sizeof(*board));
    set_settings(board);

    return 0;
}