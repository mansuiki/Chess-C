#ifndef BASE_H_INCLUDED
#include "common.h"
#endif

void update_movable_positions(chess_piece *pieces[NUM_CHESS_PIECES]);
void reset(chess_piece *[NUM_CHESS_PIECES],int [][12], int);
int promotion(chess_piece *,int);