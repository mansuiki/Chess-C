#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>

#define NUM_CHESS_PIECES 32
#define BASE_H_INCLUDED 1

typedef struct _chess_piece {
    char type; //k = King, q = Queen, r = Rook, b = Bishops, n = Knights, p = Pawns
    wchar_t unicode         ;
    int position[2]; //{x, y}
    _Bool color; //1 = Black, 0 = White
} chess_piece;

int get_pieces_by_pos(int [][2], int, chess_piece [NUM_CHESS_PIECES], chess_piece []);
_Bool get_one_piece_by_pos(int [2], chess_piece [NUM_CHESS_PIECES], chess_piece *);
