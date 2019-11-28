#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#define BOARD_SIZE 64
#define BASE_H_INCLUDED 1

typedef struct _chess_piece {
    char type; //k = King, q = Queen, r = Rook, b = Bishops, n = Knights, p = Pawns
    wchar_t unicode;
    int position[2]; //{x, y}
    _Bool color; //1 = Black, 0 = White
} chess_piece;