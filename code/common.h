#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>

#define NUM_CHESS_PIECES 32
#define BASE_H_INCLUDED 1

typedef struct _chess_piece {
    char type; //k = King, q = Queen, r = Rook, b = Bishops, n = Knights, p = Pawns
    wchar_t unicode;
    int position[2]; //행마 현재 위치 {x, y}
    _Bool color; //1 = Black, 0 = White
    _Bool is_dead; //1 = Dead, 0 = Alive
    int value; //유닛 가치
    int id; // 식별 번호
    int move_cnt; //움직인 횟수
    int directions[10][2]; //이동 가능 방향
    int movable_pos[32][2]; //이동 가능 위치
} chess_piece;

int get_pieces_by_pos(int [][2], int, chess_piece [NUM_CHESS_PIECES], chess_piece []);
_Bool get_one_piece_by_pos(int [2], chess_piece [NUM_CHESS_PIECES], chess_piece **);
_Bool is_piece_exists(int [2], chess_piece [NUM_CHESS_PIECES]);
_Bool find_pos(int [2], chess_piece [NUM_CHESS_PIECES], int);
