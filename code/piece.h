#ifndef BASE_H_INCLUDED
#include "common.h"
#endif

void setQueen(chess_piece *);
void setBishop(chess_piece *);
void setPawn(chess_piece *);
void setKing(chess_piece *);
void setRook(chess_piece *);
void setKnight(chess_piece *);

void movePawn(chess_piece *p, int arr[][10], int col, int row);
