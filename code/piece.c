#include "piece.h"

int check_board[12][12] = {0,}; //체크용 보드판 (1:백폰,2:백나이트,3:백비숍,4:백룩,5:백퀸,6:백킹,11:흑폰)

/* color == 1일 경우 블랙으로 처리됨 */

void setQueen(chess_piece *p, _Bool color)
{
    p->type = 'q';
    p->unicode = color ? 0x265B : 0x2655;
    p->id = color ? 15 : 5;
    p->value = 9;
    p->color = color;
    p->move_cnt = 0;
    p->is_dead = 0;

    // 이동 가능 방향 초기화 퀸
    int t = 1;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (j == 0) p->directions[i][j] = t;
            else p->directions[i][j] = 1 - (2 * (i % 2));
        }
        if (i == 1) t = -1;
    }

    for (int i = 4; i < 8; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (i % 4 <= 1)
            {
                if (j == 0) p->directions[i][j] = 0;
                else p->directions[i][j] = 1 - (2 * (i % 2));
            }
            else
            {
                if (j == 1) p->directions[i][j] = 0;
                else p->directions[i][j] = 1 - (2 * (i % 2));
            }

        }
    }

}

void setBishop(chess_piece *p, _Bool color)
{
    p->type = 'b';
    p->unicode = color ? 0x265D : 0x2657;
    p->id = color ? 13 : 3;
    p->value = 3;
    p->color = color;
    p->move_cnt = 0;
    p->is_dead = 0;

    // ?? ?? ?? ??? ??
    int t = 1;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (j == 0) p->directions[i][j] = t;
            else p->directions[i][j] = 1 - (2 * (i % 2));
        }
        if (i == 1) t = -1;
    }
}

void setPawn(chess_piece *p, _Bool color)
{
    p->type = 'p';
    p->unicode = color ? 0x265F : 0x2659;
    p->id = color ? 11 : 1;
    p->value = 1;
    p->color = color;
    p->move_cnt = 0;
    p->is_dead = 0;
}

/**
 *
 * @param p
 */
void move_pawn(chess_piece *p, int board[][12], int row)//폰의 움직임 시 실행하여
{
    if (p->move_cnt == 0)
    {
        p->directions[0][1] = -1 + 2 * p->color;
        if(board[p->position[0]][p->position[1] -1 + 2 * p->color] == 0) p->directions[1][1] = -2 * (1 - 2 * p->color);
    }
    else
    {
        p->directions[0][1] = -1 + 2 * p->color;
    }

    if (board[p->position[0] + 2 + 1][p->position[0] + 2 - 1 + 2 * p->color] > 0)
    {
        p->directions[2][0] = 1;
        p->directions[2][1] = -1 + 2 * p->color;
    }

    if (board[p->position[0] + 2 - 1][p->position[0] + 2 - 1 + 2 * p->color] > 0)
    {
        p->directions[2][0] = -1;
        p->directions[2][1] = -1 + 2 * p->color;
    }
}

void setKing(chess_piece *p, _Bool color)
{
    p->type = 'k';
    p->unicode = color ? 0x265A : 0x2654;
    p->id = color ? 13 : 3;
    p->value = 100;
    p->color = color;
    p->move_cnt = 0;
    p->is_dead = 0;
    // ?? ?? ?? ??? ?
    int t = 1;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (j == 0) p->directions[i][j] = t;
            else p->directions[i][j] = 1 - (2 * (i % 2));
        }
        if (i == 1) t = -1;
    }

    for (int i = 4; i < 8; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (i % 4 <= 1)
            {
                if (j == 0) p->directions[i][j] = 0;
                else p->directions[i][j] = 1 - (2 * (i % 2));
            }
            else
            {
                if (j == 1) p->directions[i][j] = 0;
                else p->directions[i][j] = 1 - (2 * (i % 2));
            }

        }
    }

}

void check_castling(chess_piece *p, int arr[][12], int row)
{
    if (p->color == 1)
    {
        if (p->move_cnt == 0)
        {
            if (arr[2][9] == 14)
            {
                int t = 0;
                for (int i = 1; i < 4; i++)
                {
                    if (arr[2 + i][9] == 0) t++;
                }
                if (t == 3)
                {
                    p->directions[8][0] = -2;
                    p->directions[8][1] = 0;
                }
            }
            if (arr[9][9] == 14)
            {
                int t = 0;
                for (int i = 1; i < 4; i++)
                {
                    if (arr[9 - i][9] == 0) t++;
                }
                if (t == 3)
                {
                    p->directions[8][0] = 2;
                    p->directions[8][1] = 0;
                }
            }
        }
    }
    else
    {
        if (p->move_cnt == 0)
        {
            if (arr[2][2] == 4)
            {
                int t = 0;
                for (int i = 1; i < 4; i++)
                {
                    if (arr[2 + i][2] == 0) t++;
                }
                if (t == 3)
                {
                    p->directions[8][0] = -2;
                    p->directions[8][1] = 0;
                }
            }
            if (arr[9][2] == 4)
            {
                int t = 0;
                for (int i = 1; i < 4; i++)
                {
                    if (arr[9 - i][2] == 0) t++;
                }
                if (t == 3)
                {
                    p->directions[8][0] = 2;
                    p->directions[8][1] = 0;
                }
            }
        }
    }
}

void setRook(chess_piece *p, _Bool color)
{
    p->type = 'r';
    p->unicode = color ? 0x265C : 0x2656;
    p->id = color ? 14 : 4;
    p->value = 5;
    p->color = color;
    p->move_cnt = 0;
    p->is_dead = 0;
    // ?? ?? ?? ??? ?
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (i % 4 <= 1)
            {
                if (j == 0) p->directions[i][j] = 0;
                else p->directions[i][j] = 1 - (2 * (i % 2));
            }
            else
            {
                if (j == 1) p->directions[i][j] = 0;
                else p->directions[i][j] = 1 - (2 * (i % 2));
            }

        }
    }
}

void setKnight(chess_piece *p, _Bool color)
{
    p->type = 'n';
    p->unicode = color ? 0x265E : 0x2658;
    p->id = color ? 12 : 2;
    p->value = 9;
    p->color = color;
    p->move_cnt = 0;
    p->is_dead = 0;
    // ?? ?? ?? ??? ???
    int t = 1;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (i < 4)
            {
                if (j == 0) p->directions[i][j] = 2 * t;
                else p->directions[i][j] = 1 - (2 * (i % 2));
            }
            else
            {
                if (j == 1) p->directions[i][j] = 2 * t;
                else p->directions[i][j] = 1 - (2 * (i % 2));
            }
        }
        if (i % 2 == 1)
        {
            t *= -1;
        }
    }
}
