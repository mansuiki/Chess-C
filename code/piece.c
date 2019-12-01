#include "piece.h"

/* color == 1일 경우 블랙으로 처리됨 */

void setQueen(chess_piece *p, _Bool color)
{
    p->type = 'q';
    p->unicode = color ? 0x265B : 0x2655;
    p->id = color ? 10 : 5;
    p->value = 9;
    // 이동 가능 방향 초기화 퀸
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

void setBishop(chess_piece *p, _Bool color)
{
    p->type = 'b';
    p->unicode = color ? 0x265D : 0x2657;
    p->id = color ? 10 : 3;
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

void setPawn(chess_piece *p, _Bool color)
{
    p->type = 'p';
    p->unicode = color ? 0x265F : 0x2659;
    p->id = color ? 10 : 1;
    p->value = 1;
}

/**
 *
 * @param p
 */
void move_pawn(chess_piece *p)//폰의 움직임 시 실행하여
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
}

void setKing(chess_piece *p, _Bool color)
{
    p->type = 'k';
    p->unicode = color ? 0x265A : 0x2654;
    p->id = color ? 10 : 3;
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

void setRook(chess_piece *p, _Bool color)
{
    p->type = 'r';
    p->unicode = color ? 0x265C : 0x2656;
    p->id = color ? 10 : 4;
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

void setKnight(chess_piece *p, _Bool color)
{
    p->type = 'n';
    p->unicode = color ? 0x265E : 0x2658;
    p->id = color ? 10 : 2;
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
             t*= -1;
        }
    }
}
