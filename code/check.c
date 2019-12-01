#include "piece.h"

int checkBoard[10][10];

void get_p_movable_pos(chess_piece [NUM_CHESS_PIECES], chess_piece *);
void get_n_movable_pos(chess_piece [NUM_CHESS_PIECES], chess_piece *);
void checkBishop(chess_piece [NUM_CHESS_PIECES], chess_piece *);
void checkRook(chess_piece [NUM_CHESS_PIECES], chess_piece *);
void checkQueen(chess_piece [NUM_CHESS_PIECES], chess_piece *);
void checkKing(chess_piece [NUM_CHESS_PIECES], chess_piece *);
void promotion(chess_piece *, int);

/**
 * 움직임이 수행될 때마다 이동 가능한 위치를 업데이트하는 함수
 * @param pieces 전체 기물 배열
 */
void update_movable_positions(chess_piece pieces[NUM_CHESS_PIECES])
{
    for(int i = 0; i < NUM_CHESS_PIECES; i++)
    {
        switch (pieces[i].type)
        {
            case 'p':
                get_p_movable_pos(pieces, &pieces[i]);
                break;

            case 'n':
                get_n_movable_pos(pieces, &pieces[i]);
                break;

            case 'b':
                checkBishop(pieces, &pieces[i]);
                break;

            case 'r':
                checkRook(pieces, &pieces[i]);
                break;

            case 'q':
                checkQueen(pieces, &pieces[i]);
                break;

            case 'k':
                checkKing(pieces, &pieces[i]);
                break;

            default:
                break;
        }
    }
}

/**
 * 이동가능한 폰의 위치를 pieces 배열에 저장하는 함수
 * @param pieces 전체 기물
 * @param p 저장할 대상
 */
void get_p_movable_pos(chess_piece pieces[NUM_CHESS_PIECES], chess_piece *p)
{
    move_pawn(p); // 폰의 이동 가능 방향 체크
    int tmp[2]; // 이동 가능 위치 임시 저장
    for (int i = 0; i < 4; i++)
    {
        tmp[0] = p->position[0] + p->directions[i][0];
        tmp[1] = p->position[1] + p->directions[i][1];
        if (is_piece_exists(tmp, pieces) == 0) //이동하고자 하는 위치에 기물이 없을 경우
        {
            p->movable_pos[i][0] = p->position[0] + p->directions[i][0];
            p->movable_pos[i][1] = p->position[1] + p->directions[i][1];
        }
    }
}

/**
 * 이동가능한 나이트의 위치를 pieces 배열에 저장하는 함수
 * @param pieces 전체 기물
 * @param p 저장할 대상
 */
void get_n_movable_pos(chess_piece pieces[NUM_CHESS_PIECES], chess_piece *p)
{
    int tmp[2]; // 이동 가능 위치 임시 저장
    for(int i = 0; i < 8; i++)
    {
        tmp[0] = p->position[0] + p->directions[i][0];
        tmp[1] = p->position[1] + p->directions[i][1];
        if(is_piece_exists(tmp, pieces) == 0)
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
            if(is_piece_exists(tmp,pieces) == 0)
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

            tmp[0] += p->directions[i][0];
            tmp[1] += p->directions[i][1];
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
            if(is_piece_exists(tmp, pieces) == 0)
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

            tmp[0] += p->directions[i][0];
            tmp[1] += p->directions[i][1];
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
            if(is_piece_exists(tmp, pieces) == 0)
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

            tmp[0] += p->directions[i][0];
            tmp[1] += p->directions[i][1];
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
        if(is_piece_exists(tmp, pieces) == 0)
        {
            p->movable_pos[i][0] = p->position[0] + p->directions[i][0];
            p->movable_pos[i][1] = p->position[1] + p->directions[i][1];
        }
    }
}

//현재 더 구현해야 할 것 캐슬링, 앙파상, 프로모션 특수이동

int checkmate(chess_piece pieces[NUM_CHESS_PIECES], chess_piece *p, int board[][12], int row) // 0: x 1: 체크 2: 체크메이트
{
    int posCheck[3][3] = {0,};
    int isCheck = 0;
    int color = (1 - 1 * p->color) * 10; // 킹이 백일 경우 10, 흑일 경우 0
    int direction1[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};//십자 축
    int direction2[4][2] = {{1,1},{1,-1},{-1,1},{-1,-1}};//대각선 축
    int pos1[8][2] = {{2,1},{2,-1},{-2,1},{-2,-1},{1,2},{1,-2},{-1,2},{-1,-2}};//나이트 이동위치
    int pos2[2][2] = {{1,1},{-1,1}};//폰 이동 위치
    for(int t = 0; t < 3; t++)
    {
        for(int j = 0; j < 3; j++)
        {
            int tmp[2] = {p->position[0] + 1 + t, p->position[1] + 1 + j};// 이동 가능 위치 임시 저장 9개
            if(board[tmp[0]][tmp[1]] == -1) continue; // 이동 불가능 위치면 넘기기
            for(int i = 0; i < 4; i++) //십자 축 체크
            {

                while(board[tmp[0]][tmp[1]] > -1)
                {
                    if(board[tmp[0]][tmp[1]] == color + 3 || board[tmp[0]][tmp[1]] == color + 5)
                    {
                        posCheck[t][j] = 1;
                        isCheck = 1;
                    }
                    else if(board[tmp[0]][tmp[1]] == 0)
                    {
                        ;
                    }
                    else
                    {
                        break;
                    }

                    tmp[0] += direction1[i][0];
                    tmp[1] += direction1[i][1];
                }
            }

            tmp[0] = p->position[0] + 1 + t;
            tmp[1] = p->position[1] + 1 + j;

            for(int i = 0; i < 4; i++) // 대각선 축 체크
            {

                while(board[tmp[0]][tmp[1]] > -1)
                {
                    if(board[tmp[0]][tmp[1]] == color + 3 || board[tmp[0]][tmp[1]] == color + 5)
                    {
                        posCheck[t][j] = 1;
                        isCheck = 1;
                    }
                    else if(board[tmp[0]][tmp[1]] == 0)
                    {
                        ;
                    }
                    else
                    {
                        break;
                    }

                    tmp[0] += direction2[i][0];
                    tmp[1] += direction2[i][1];
                }
            }

            tmp[0] = p->position[0] + 1 + t;
            tmp[1] = p->position[1] + 1 + j;

            for(int i = 0; i < 8; i++) // 나이트 위치 체크
            {
                if(board[tmp[0] + pos1[i][0]][tmp[1] + pos1[i][1]] == color + 2)
                {
                    posCheck[t][j] = 1;
                    isCheck = 1;
                }
            }

            tmp[0] = p->position[0] + 1 + t;
            tmp[1] = p->position[1] + 1 + j;

            for(int i = 0; i < 2; i++) // 폰 위치 체크
            {
                if(color == 0)
                {
                    if(board[tmp[0] + pos2[i][0]][tmp[1] + pos2[i][1]] == color + 2)
                    {
                        posCheck[t][j] = 1;
                        isCheck = 1;
                    }
                }
                else
                {
                    if(board[tmp[0] + pos2[i][0]][tmp[1] - pos2[i][1]] == color + 2)
                    {
                        posCheck[t][j] = 1;
                        isCheck = 1;
                    }
                }

            }
        }

    }

    //체크메이트 판정===========================================
    int isCheckmate = 0;

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            isCheckmate += posCheck[i][j];
        }
    }
    if(isCheckmate == 9) return 2;
    if(isCheck == 0) return 0;
    else return 1;

}

void reset(chess_piece *pieces[NUM_CHESS_PIECES],int arr[][12], int row)
{
    for(int i = 2; i < 10; i++) // 보드판 초기화
    {
        for(int j = 2; j < 10; j++)
        {
            arr[i][j] = 0;
        }
    }
    for(int i = 0; i < NUM_CHESS_PIECES; i++)
    {
        if(pieces[i]->type == 'p')
        {
            if(pieces[i]->position[0] == 0 || pieces[i]->position[0] == 7)
            {
                promotion(pieces[i],pieces[i]->color);
            }
            if(pieces[i]->position[0] == 4)
            {
                if(pieces[i]->move_cnt == 1)
                {
                    arr[7][pieces[i]->position[1] + 2] = 100 + i;
                }
            }
            if(pieces[i]->position[0] == 3)
            {
                if(pieces[i]->move_cnt == 1)
                {
                    arr[4][pieces[i]->position[1] + 2] = 100 + i;
                }
            }
        }
        arr[pieces[i]->position[0] + 2][pieces[i]->position[1] + 2] = pieces[i]->id;
        for(int j = 0; j < 28; j++)
        {
            pieces[i]->movable_pos[j][0] = 0;
            pieces[i]->movable_pos[j][1] = 0;
        }
    }
}

void promotion(chess_piece *p,int color)
{
    char t;
    int roop = 1;
    while(roop == 1)
    {
        printf("변신할 기물을 선택하시오.(b,n,r,q)");
        scanf("%c",&t);
        switch (t)
        {
            case 'b':
                setBishop(p,color);
                roop = 0;
                break;
            case 'n':
                setKnight(p,color);
                roop = 0;
                break;
            case 'r':
                setRook(p,color);
                roop = 0;
                break;
            case 'q':
                setQueen(p,color);
                roop = 0;
                break;
            default:
                printf("잘못된 입력입니다.\n");
                break;
        }
    }
}
