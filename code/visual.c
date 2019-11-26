#include <stdio.h>
#include "visual.h"

void print_board(chess_piece pieces[32])
{
    wchar_t board[8][8] = {'\0'};

    for (int i = 0; i < 32; ++i)
    {
        board[ pieces[i].position[1] ][ pieces[i].position[0] ] = pieces[i].unicode;
    }

    for (int row = 0; row < 8; ++row)
    {
        printf("%-2d", row + 1);
        for (int col = 0; col < 8; ++col)
        {
            if (board[row][col] != NULL)
            {
                printf(" %lc", board[row][col]);
            }
            else
            {
                if ((row + col)%2 != 0)
                {
                    printf("\33[1;35m \u2588\33[0m");
                }
                else
                {
                    printf("\33[1;33m \u2588\33[0m");
                }
            }
        }
        printf("\n");
    }
}