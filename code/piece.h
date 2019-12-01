#ifndef BASE_H_INCLUDED
#include "common.h"
#endif

void setQueen(chess_piece *, _Bool);
void setBishop(chess_piece *, _Bool);
void setPawn(chess_piece *l, _Bool);
void setKing(chess_piece *, _Bool);
void setRook(chess_piece *, _Bool);
void setKnight(chess_piece *, _Bool);

void move_pawn(chess_piece *p);

void check_castling(chess_piece *, int [][12], int);