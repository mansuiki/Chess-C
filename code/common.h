#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#define NUM_CHESS_PIECES 32
#define BASE_H_INCLUDED 1

typedef struct _chess_piece {
    char type; //k = King, q = Queen, r = Rook, b = Bishops, n = Knights, p = Pawns
    wchar_t unicode;
    int position[2]; //{x, y}
    _Bool color; //1 = Black, 0 = White
} chess_piece;

chess_piece pieces[NUM_CHESS_PIECES];
_Bool _turn;

int get_piece_by_pos(int pos_arr[2], int num_pos, chess_piece *result);