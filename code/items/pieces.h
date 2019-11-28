#include <wchar.h>

typedef struct _chess_piece {
    char *type; //rook, bishop, queen, etc...
    wchar_t unicode;
    int position[2]; //{x, y}
    _Bool color; //1 = Black, 0 = White
} chess_piece;