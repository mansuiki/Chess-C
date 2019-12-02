#ifndef BASE_H_INCLUDED
#include "common.h"
#endif

void update_movable_positions(chess_piece [NUM_CHESS_PIECES], int [][12], int);
void reset(chess_piece [NUM_CHESS_PIECES],int [][12], int);
int promotion(chess_piece *,int);
int checkmate(chess_piece [NUM_CHESS_PIECES], chess_piece *, int [][12], int);
