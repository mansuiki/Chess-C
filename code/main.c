#include <stdlib.h>
#include <locale.h>
#include "visual.h"

chess_piece *init(void);

int main()
{
    setlocale(LC_ALL, "");

    chess_piece *pieces = init();
    print_board(pieces);
    return 0;
}

chess_piece *init()
{
    chess_piece *pieces = (chess_piece *) calloc(32, sizeof(chess_piece));

    //Black pawn
    for (int i = 0; i < 8; ++i)
    {
        (pieces+i)->type = "pawn";
        (pieces+i)->unicode = 0x265F;
        (pieces+i)->position[0] = i; //x
        (pieces+i)->position[1] = 1; //y
        (pieces+i)->color = 1;
    }

    return pieces;
}