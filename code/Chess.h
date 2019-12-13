#ifndef CHESS_H
#define CHESS_H

#include <assert.h>
#include "AI.h"
#include "DataTypes.h"

/** 체스판 출력 관련 함수들 **/
void PrintMenu();

void AddBoard(t_board *board, BLIST *list);

void DeleteBoard(BLIST *list);

BLIST *NewBoardList();

/** 플레이어턴의 진행을 위한 변수 선언과 함수 진행이 정의된 함수 **/
int UserTurn(t_board Board, t_castle Castle, int turn, int piece[], char start[][3], char end[][3], int capture[],
             int special[], int *Wn, int *Wb, int *Bn, int *Bb);

/** AI턴의 진행을 위한 변수 선언과 함수 진행이 정의된 함수 **/
void AITurn(t_board Board, t_castle Castle, int turn, int difficulty, int piece[], char start[][3], char end[][3],
            int capture[], int special[], int *Wn, int *Wb, int *Bn, int *Bb);

#endif
