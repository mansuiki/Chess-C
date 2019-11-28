#include <stdio.h>
#include "visual.h"

void print_board(chess_piece pieces[32])
{
    wchar_t board[8][8] = {};

    for (int i = 0; i < 32; ++i)
    {
        board[ pieces[i].position[1] ][ pieces[i].position[0] ] = pieces[i].unicode;
    }

    for (int row = 0; row < 8; ++row)
    {
        printf(
               "\33[1;35m%d\33[0m %lc %lc %lc %lc %lc %lc %lc %lc\n",
                row+1,
                board[row][0], board[row][1], board[row][2], board[row][3],
                board[row][4], board[row][5], board[row][6], board[row][7]
                );
    }
    printf("\33[1;35m  A B C D E F G H\33[0m");
}