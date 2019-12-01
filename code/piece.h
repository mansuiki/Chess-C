#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>
#ifndef BASE_H_INCLUDED
#include "common.h"
#endif

void setBishop(chess_piece *p)
{
    p->value = 3;

    // ?? ?? ?? ??? ??
    int t = 1;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            if(j == 0) p->directions[i][j] = t;
            else p->directions[i][j] = 1 - (2 * (i % 2));
        }
        if(i == 1) t = -1;
    }
}

void setQueen(chess_piece *p)
{
    p->value = 9;
    // ?? ?? ?? ??? ?
    int t = 1;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            if(j == 0) p->directions[i][j] = t;
            else p->directions[i][j] = 1 - (2 * (i % 2));
        }
        if(i == 1) t = -1;
    }

    for(int i = 4; i < 8; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            if(i % 4 <= 1)
            {
                if(j == 0) p->directions[i][j] = 0;
                else p->directions[i][j] = 1 - (2 * (i % 2));
            }
            else
            {
                if(j == 1) p->directions[i][j] = 0;
                else p->directions[i][j] = 1 - (2 * (i % 2));
            }

        }
    }

}

void setPawn(chess_piece *p)
{
    p->value = 1;
}

void movePawn(chess_piece *p, int arr[][10], int col, int row)//?? ??? ? ????
{
    if(p->move_cnt == 0)
    {
        p->directions[0][0] = 1;
        p->directions[1][0] = 2;
    }
    else
    {
        p->directions[1][0] = 0;
    }

    if(arr[p->position[0] + 1][p->position[1] - 1 + 2 * p->color] > 0)
    {
        p->directions[2][0] = 1;
        p->directions[2][1] = -1 + 2 * p->color;
    }

    if(arr[p->position[0] - 1][p->position[1] - 1 + 2 * p->color] > 0)
    {
        p->directions[3][0] = -1;
        p->directions[3][1] = -1 + 2 * p->color;
    }
}

void setKing(chess_piece *p)
{
    p->value = 100;
    // ?? ?? ?? ??? ?
    int t = 1;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            if(j == 0) p->directions[i][j] = t;
            else p->directions[i][j] = 1 - (2 * (i % 2));
        }
        if(i == 1) t = -1;
    }

    for(int i = 4; i < 8; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            if(i % 4 <= 1)
            {
                if(j == 0) p->directions[i][j] = 0;
                else p->directions[i][j] = 1 - (2 * (i % 2));
            }
            else
            {
                if(j == 1) p->directions[i][j] = 0;
                else p->directions[i][j] = 1 - (2 * (i % 2));
            }

        }
    }

}

void castling(chess_piece *p, int arr[][12], int col, int row)
{
    //
}

void setRook(chess_piece *p)
{
    p->value = 5;
    // ?? ?? ?? ??? ?
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            if(i % 4 <= 1)
            {
                if(j == 0) p->directions[i][j] = 0;
                else p->directions[i][j] = 1 - (2 * (i % 2));
            }
            else
            {
                if(j == 1) p->directions[i][j] = 0;
                else p->directions[i][j] = 1 - (2 * (i % 2));
            }

        }
    }
}

void setKnight(chess_piece *p)
{
    p->value = 9;
    // ?? ?? ?? ??? ???
    int t = 1;

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            if(i < 4)
            {
                if(j == 0) p->directions[i][j] = 2 * t;
                else p->directions[i][j] = 1 - (2 * (i % 2));
            }
            else
            {
                if(j == 1) p->directions[i][j] = 2 * t;
                else p->directions[i][j] = 1 - (2 * (i % 2));
            }
        }
        if(i % 2 == 1)
        {
            t *= -1;
        }
    }

}
