#ifndef BASE_H_INCLUDED
#include "common.h"
#endif

void move_piece(chess_piece [NUM_CHESS_PIECES], int [12][12], chess_piece *, unsigned char [2], _Bool *);
void castling();