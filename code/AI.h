#ifndef AI_H
#define AI_H

#include "DataTypes.h"

/* AI 기능 관련 함수들 */

double EvaluatePosition(t_board Board, t_move_array Moves, int turn, t_castle Castle);

double EvaluateMove(t_board board, t_move Move, int *whN, int *whB, int *blN, int *blB, int turn);

int IsDoubled(t_board Board, int index);

double IsCastled(t_board Board, int turn);

int KnightOnRim(int index);

int PawnsOnBoard(t_board Board);

int CanPromote(t_board board, int index);

int IsPassed(t_board board, int index);

int BishopPair(t_board board);

int IsUndeveloped(t_board board, int index);

int CenterControl(t_board board);

unsigned char GamePhase(t_board board, int turn);

char CenterControl2(t_board board, t_move_array current_turn, int turn, t_castle Castle);

char QueenIsOut(t_board board);

void UpdateHasMoved(t_board board, int *wNi, int *wBi, int *bNi, int *bBi);

#endif
