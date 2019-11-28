#include <wchar.h>

typedef struct _chess_piece {
    char type; //k = King, q = Queen, r = Rook, b = Bishops, n = Knights, p = Pawns
    wchar_t unicode;
    int position[2]; //{x, y}
    _Bool color; //1 = Black, 0 = White
} chess_piece;