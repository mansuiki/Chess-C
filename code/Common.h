#ifndef COMMON_H
#define COMMON_H

#include "DataTypes.h"


/** 이차원을 계산을 위해 일차원으로 변환해주는 함수 **/
int two2one(t_square Square);
/** 일차원으로 변환된 값을 다시 이차원으로 변환해주는 함수 **/
/** 일차원 : 함수 내부 계산을 위해, 이차원 : 체스피스의 프린트를 위해 **/
t_square one2two(int oneDindex);

/** 기물 이동 함수, 캐슬링용 로그 변경 함수 **/
void MovePiece(t_board Board, t_move Move, t_castle Castle);

/** 프로모션 **/
void PromotePiece(t_board board, int promotingSquare);


/** 체스의 가로세로 위치를 얻는 함수 **/
int GetRank(int index);

int GetFile(int index);

t_move_array ExhaustMoves(t_board board, int turn, t_castle Castle);

/**
 * Max 와 Min 값을 반환 해주는 함수
 * @param a : 입력값 1
 * @param b : 입력값 2
 * @return 둘중 작은값 반환
 */
double Max(double a, double b);

double Min(double a, double b);

t_coin
MaxValue(t_node state, t_castle Castle, double alpha, double beta, int depth, int turn, int *WN, int *WB, int *BN,
         int *BB);

t_coin
MinValue(t_node state, t_castle Castle, double alpha, double beta, int depth, int turn, int *WN, int *WB, int *BN,
         int *BB);

/**
 * 최선의 이동을 반환해주는 함수
 * @return 가장 최선의 결과를 가져오는 이동을 반환
 */
t_move GetBestMove(t_board board, t_castle Castle, int turn, int depth, int *wn, int *wb, int *bn, int *bb);

/**
 * 유효한 움직임인지 확인하는 함수들
 */

/** 모든 체스 말 움직임 가능 여부 판별 **/
int IsLegal(t_board Board_in, t_move Move, int turn, t_castle Castle);

/** 그 움직임이 유효한지 판별하고 결과에 따라서 값을 반환함 **/
int IsLegal_Check(t_board Board, t_move Move, int turn1, t_castle Castle);

/** 기물의 이동이 상대 진영의 킹을 체크 했을때 판별 **/
int CheckCheckmate(t_board board, int turn, t_castle Castle);

/** 이동이 완료된 후 체크상태인지 판별 **/
int CheckCheck(t_board board, int turn, t_castle Castle);

/** 체크상태에 돌입했음을 판변하는 함수 **/
int AmIinCheck(t_board Board, t_move Move, int turn, t_castle Castle);

#endif