#ifndef COMMON_H
#define COMMON_H

#include "DataTypes.h"

/* 1-D - 2-D Conversion */
/* 2 to 1D conversion */
int two2one(t_square Square);

/* 1 to 2D conversion */
t_square one2two(int oneDindex);

/* Basic Chess Functions */

void MovePiece(t_board Board, t_move Move, t_castle Castle);

void PromotePiece(t_board board, int promotingSquare);

int GetRank(int index);

int GetFile(int index);

/* AlphaBeta Algorithm Implementation */

t_move_array ExhaustMoves(t_board board, int turn, t_castle Castle);

double Max(double a, double b);

double Min(double a, double b);

t_coin
MaxValue(t_node state, t_castle Castle, double alpha, double beta, int depth, int turn, int *WN, int *WB, int *BN,
         int *BB);

t_coin
MinValue(t_node state, t_castle Castle, double alpha, double beta, int depth, int turn, int *WN, int *WB, int *BN,
         int *BB);

t_move GetBestMove(t_board board, t_castle Castle, int turn, int depth, int *wn, int *wb, int *bn, int *bb);

/* Legality */

/* Determines is a move is legal */
/* This func take a t_board that represents the board BEFORE the MOVE is made */
int IsLegal(t_board Board_in, t_move Move, int turn, t_castle Castle);

/* Checks if the move is legal and returns a certain value depending on the result */
int IsLegal_Check(t_board Board, t_move Move, int turn1, t_castle Castle);

/* Checks the game status for things like checkmate */
int CheckCheckmate(t_board board, int turn, t_castle Castle);

/* Checks if the king is in check */
int CheckCheck(t_board board, int turn, t_castle Castle);

int AmIinCheck(t_board Board, t_move Move, int turn, t_castle Castle);

#endif