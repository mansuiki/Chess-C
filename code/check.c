#include "common.h"
#include "piece.h"

int checkBoard[10][10];

void checkPawn(chess_piece [NUM_CHESS_PIECES], chess_piece *);
void checkKnight(chess_piece [NUM_CHESS_PIECES], chess_piece *);
void checkBishop(chess_piece [NUM_CHESS_PIECES], chess_piece *);
void checkRook(chess_piece [NUM_CHESS_PIECES], chess_piece *);
void checkQueen(chess_piece [NUM_CHESS_PIECES], chess_piece *);
void checkKing(chess_piece [NUM_CHESS_PIECES], chess_piece *);

void checkMove(chess_piece *pieces[NUM_CHESS_PIECES])
{
    for(int i = 0; i < NUM_CHESS_PIECES; i++)
    {
        switch (pieces[i]->type)
        {
            case 'p':
                checkPawn(pieces,pieces[i]);
                break;
            case 'n':
                checkKnight(pieces,pieces[i]);
                break;
            case 'b':
                checkBishop(pieces,pieces[i]);
                break;
            case 'r':
                checkRook(pieces,pieces[i]);
                break;
            case 'q':
                checkQueen(pieces,pieces[i]);
                break;
            case 'k':
                checkKing(pieces,pieces[i]);
                break;
            default:
                break;
        }
    }
}

void checkPawn(chess_piece pieces[NUM_CHESS_PIECES], chess_piece *p)
{
    movePawn(p,checkBoard,10,10); // 폰의 이동 가능 방향 체크
    int tmp[2]; // 이동 가능 위치 임시 저장
    for(int i = 0; i < 4; i++)
    {
        tmp[0] = p->position[0] + p->directions[i][0];
        tmp[1] = p->position[1] + p->directions[i][1];
        if(get_one_piece_by_pos(tmp, pieces) == 0)
        {
            p->movable_pos[i][0] = p->position[0] + p->directions[i][0];
            p->movable_pos[i][1] = p->position[1] + p->directions[i][1];
        }
    }
}

void checkKnight(chess_piece pieces[NUM_CHESS_PIECES], chess_piece *p)
{
    int tmp[2]; // 이동 가능 위치 임시 저장
    for(int i = 0; i < 8; i++)
    {
        tmp[0] = p->position[0] + p->directions[i][0];
        tmp[1] = p->position[1] + p->directions[i][1];
        if(get_one_piece_by_pos(tmp, pieces) == 0)
        {
            p->movable_pos[i][0] = p->position[0] + p->directions[i][0];
            p->movable_pos[i][1] = p->position[1] + p->directions[i][1];
        }
    }
}

void checkBishop(chess_piece pieces[NUM_CHESS_PIECES], chess_piece *p)
{
    int index = 0;
    for(int i = 0; i < 4; i++)
    {
        int tmp[2] = {p->position[0],p->position[1]}; // 이동 가능 위치 임시 저장
        while(tmp[0] > 0 && tmp[0] < 9 && tmp[1] > 0 && tmp[1] < 9)
        {
            if(get_one_piece_by_pos(tmp,pieces) == 0)
            {
                p->movable_pos[index][0] = tmp[0];
                p->movable_pos[index][0] = tmp[1];
            }
            else if(tmp[0] == p->position[0] && tmp[1] == p->position[1])
            {
                ;
            }
            else
            {
                if(find_pos(tmp,pieces,p->color) == p->color) break;
                else
                {
                    p->movable_pos[index][0] = tmp[0];
                    p->movable_pos[index][1] = tmp[1];
                    index++;
                    break;
                }
            }

            tmp[0] =+ p->directions[i][0];
            tmp[1] =+ p->directions[i][1];
            index++;
        }
    }
}

void checkRook(chess_piece pieces[NUM_CHESS_PIECES], chess_piece *p)
{
    int index = 0;
    for(int i = 0; i < 4; i++)
    {
        int tmp[2] = {p->position[0],p->position[1]}; // 이동 가능 위치 임시 저장
        while(tmp[0] > 0 && tmp[0] < 9 && tmp[1] > 0 && tmp[1] < 9)
        {
            if(get_one_piece_by_pos(tmp,pieces) == 0)
            {
                p->movable_pos[index][0] = tmp[0];
                p->movable_pos[index][0] = tmp[1];
            }
            else if(tmp[0] == p->position[0] && tmp[1] == p->position[1])
            {
                ;
            }
            else
            {
                if((tmp,pieces,p->color) == p->color) break;
                else
                {
                    p->movable_pos[index][0] = tmp[0];
                    p->movable_pos[index][1] = tmp[1];
                    index++;
                    break;
                }
            }

            tmp[0] =+ p->directions[i][0];
            tmp[1] =+ p->directions[i][1];
            index++;
        }
    }
}

void checkQueen(chess_piece pieces[NUM_CHESS_PIECES], chess_piece *p)
{
    int index = 0;
    for(int i = 0; i < 8; i++)
    {
        int tmp[2] = {p->position[0],p->position[1]}; // 이동 가능 위치 임시 저장
        while(tmp[0] > 0 && tmp[0] < 9 && tmp[1] > 0 && tmp[1] < 9)
        {
            if(get_one_piece_by_pos(tmp,pieces) == 0)
            {
                p->movable_pos[index][0] = tmp[0];
                p->movable_pos[index][0] = tmp[1];
            }
            else if(tmp[0] == p->position[0] && tmp[1] == p->position[1])
            {
                ;
            }
            else
            {
                if(find_pos(tmp,pieces,p->color) == p->color) break;
                else
                {
                    p->movable_pos[index][0] = tmp[0];
                    p->movable_pos[index][1] = tmp[1];
                    index++;
                    break;
                }
            }

            tmp[0] =+ p->directions[i][0];
            tmp[1] =+ p->directions[i][1];
            index++;
        }
    }
}

void checkKing(chess_piece pieces[NUM_CHESS_PIECES], chess_piece *p)
{
    int tmp[2]; // 이동 가능 위치 임시 저장
    for(int i = 0; i < 4; i++)
    {
        tmp[0] = p->position[0] + p->directions[i][0];
        tmp[1] = p->position[1] + p->directions[i][1];
        if(get_one_piece_by_pos(tmp, pieces) == 0)
        {
            p->movable_pos[i][0] = p->position[0] + p->directions[i][0];
            p->movable_pos[i][1] = p->position[1] + p->directions[i][1];
        }
    }
}

//현재 더 구현해야 할 것 캐슬링, 앙파상, 프로모션 특수이동

int checkmate(chess_piece pieces[NUM_CHESS_PIECES], chess_piece *p, int board[][12], int row) // 0: x 1: 체크 2: 체크메이트
{
    int posCheck[9] = {0,};
    int isCheck = 0;
    for(int i = 2; i < 10; i++)
    {
        int color = (1 - 1 * p->color) * 10; // 킹이 백일 경우 10, 흑일 경우 0
        int tmp[2] = {p->position[0],p->position[1]}; // 이동 가능 위치 임시 저장
        if(board[i][p->position[1]+2] == color + 4 || board[i][p->position[1]+2] == color + 5)
        {
            posCheck[0] = 1;
            isCheck = 1;
        }
        if(board[p->position[0]+2][i] == color + 4 || board[i][p->position[1]+2] == color + 5)
        {
            posCheck[0] = 1;
            isCheck = 1;
        }
    }
}

