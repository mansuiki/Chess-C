#include <locale.h>
#include "visual.h"

void init(chess_piece *);

int main()
{
    setlocale(LC_ALL, "");

    chess_piece pieces[32];
    wchar_t board[8][8] = { [0 ... 7][0 ... 7] = 0xB7 }; //범위 초기화는 GCC에서만 될 수도 있음

    init(pieces);
    print_board(pieces, board, 32);

    return 0;
}

void init(chess_piece pieces[32])
{
    int i = 0, iter_row = 8;

    //Black pawn
    for (; i < iter_row; ++i)
    {
        pieces[i].type = "pawn";
        pieces[i].unicode = 0x265F;
        pieces[i].position[0] = i; //x
        pieces[i].position[1] = 1; //y
        pieces[i].color = 1;
    }

    //White pawn
    iter_row += 8;
    for (; i < iter_row; ++i)
    {
        pieces[i].type = "pawn";
        pieces[i].unicode = 0x2659;
        pieces[i].position[0] = i; //x
        pieces[i].position[1] = 5; //y
        pieces[i].color = 0;
    }

    //Black rook
    pieces[i].type = "rook";
    pieces[i].unicode = 0x265C;
    pieces[i].position[0] = 7; //x
    pieces[i].position[1] = 0; //y
    pieces[i].color = 1;
    i ++;
    pieces[i].type = "rook";
    pieces[i].unicode = 0x265C;
    pieces[i].position[0] = 0; //x
    pieces[i].position[1] = 0; //y
    pieces[i].color = 1;
    iter_row += 2;
    i++;

    //White rook
    pieces[i].type = "rook";
    pieces[i].unicode = 0x2656;
    pieces[i].position[0] = 7; //x
    pieces[i].position[1] = 7; //y
    pieces[i].color = 0;
    i++;
    pieces[i].type = "rook";
    pieces[i].unicode = 0x2656;
    pieces[i].position[0] = 0; //x
    pieces[i].position[1] = 7; //y
    pieces[i].color = 0;
    iter_row += 2;
    i++;

    //Black knight
    pieces[i].type = "knight";
    pieces[i].unicode = 0x265E;
    pieces[i].position[0] = 6; //x
    pieces[i].position[1] = 0; //y
    pieces[i].color = 1;
    i ++;
    pieces[i].type = "knight";
    pieces[i].unicode = 0x265E;
    pieces[i].position[0] = 1; //x
    pieces[i].position[1] = 0; //y
    pieces[i].color = 1;
    iter_row += 2;
    i++;

    //White knight
    pieces[i].type = "knight";
    pieces[i].unicode = 0x2658;
    pieces[i].position[0] = 1; //x
    pieces[i].position[1] = 7; //y
    pieces[i].color = 0;
    i ++;
    pieces[i].type = "knight";
    pieces[i].unicode = 0x2658;
    pieces[i].position[0] = 6; //x
    pieces[i].position[1] = 7; //y
    pieces[i].color = 0;
    iter_row += 2;
    i++;

    //Black bishop
    pieces[i].type = "bishop";
    pieces[i].unicode = 0x265D;
    pieces[i].position[0] = 5; //x
    pieces[i].position[1] = 0; //y
    pieces[i].color = 1;
    i ++;
    pieces[i].type = "bishop";
    pieces[i].unicode = 0x265D;
    pieces[i].position[0] = 2; //x
    pieces[i].position[1] = 0; //y
    pieces[i].color = 1;
    iter_row += 2;
    i++;

    //White bishop
    pieces[i].type = "bishop";
    pieces[i].unicode = 0x2657;
    pieces[i].position[0] = 2; //x
    pieces[i].position[1] = 7; //y
    pieces[i].color = 0;
    i ++;
    pieces[i].type = "bishop";
    pieces[i].unicode = 0x2657;
    pieces[i].position[0] = 5; //x
    pieces[i].position[1] = 7; //y
    pieces[i].color = 0;
    iter_row += 2;
    i++;

    //Black king
    pieces[i].type = "king";
    pieces[i].unicode = 0x265A;
    pieces[i].position[0] = 3; //x
    pieces[i].position[1] = 0; //y
    pieces[i].color = 1;
    i ++;

    //White king
    pieces[i].type = "king";
    pieces[i].unicode = 0x2654;
    pieces[i].position[0] = 3; //x
    pieces[i].position[1] = 7; //y
    pieces[i].color = 0;
    i ++;

    //Black queen
    pieces[i].type = "queen";
    pieces[i].unicode = 0x265B;
    pieces[i].position[0] = 4; //x
    pieces[i].position[1] = 0; //y
    pieces[i].color = 1;
    i ++;

    //White queen
    pieces[i].type = "queen";
    pieces[i].unicode = 0x2655;
    pieces[i].position[0] = 4; //x
    pieces[i].position[1] = 7; //y
    pieces[i].color = 0;

    return;
}