#include <locale.h>
#include "ui.h"
#include "rule.h"

void init(chess_piece *);

chess_piece pieces[NUM_CHESS_PIECES];
int checkBoard[12][12] = {0,}; //체크용 보드판 (1:백폰,2:백나이트,3:백비숍,4:백룩,5:백퀸,6:백킹,11:흑폰)

int main()
{
    setlocale(LC_ALL, "");

    wchar_t board[8][8] = { [0 ... 7][0 ... 7] = 0xB7 }; //범위 초기화는 GCC에서만 될 수도 있음
    _Bool turn = 1;

    init(pieces);

    int coordinates[2][2];
    char special_cmd;

    print_board(pieces, board, 32);

    do {
        special_cmd = input_cmd(coordinates);

        switch (special_cmd)
        {
            case 'H':
                printf("Display help\n");
                break;

            case 'S':
                printf("Save file\n");
                break;

            case -1:
                printf("Command not found\n");
                break;

            default:
                move_piece(pieces, coordinates, turn);
                print_board(pieces, board, 32);
                break;
        }
    } while (1);

    return 0;
}

void init(chess_piece pieces[NUM_CHESS_PIECES])
{
    int i = 0, iter_row = 8;

    //Black pawn
    for (; i < iter_row; ++i)
    {
        pieces[i].type = 'p';
        pieces[i].unicode = 0x265F;
        pieces[i].position[0] = i; //x
        pieces[i].position[1] = 1; //y
        pieces[i].color = 1;
    }

    //White pawn
    iter_row += 8;
    for (; i < iter_row; ++i)
    {
        pieces[i].type = 'p';
        pieces[i].unicode = 0x2659;
        pieces[i].position[0] = i-8; //x
        pieces[i].position[1] = 6; //y
        pieces[i].color = 0;
    }

    //Black rook
    pieces[i].type = 'r';
    pieces[i].unicode = 0x265C;
    pieces[i].position[0] = 7; //x
    pieces[i].position[1] = 0; //y
    pieces[i].color = 1;
    i ++;
    pieces[i].type = 'r';
    pieces[i].unicode = 0x265C;
    pieces[i].position[0] = 0; //x
    pieces[i].position[1] = 0; //y
    pieces[i].color = 1;
    iter_row += 2;
    i++;

    //White rook
    pieces[i].type = 'r';
    pieces[i].unicode = 0x2656;
    pieces[i].position[0] = 7; //x
    pieces[i].position[1] = 7; //y
    pieces[i].color = 0;
    i++;
    pieces[i].type = 'r';
    pieces[i].unicode = 0x2656;
    pieces[i].position[0] = 0; //x
    pieces[i].position[1] = 7; //y
    pieces[i].color = 0;
    iter_row += 2;
    i++;

    //Black knight
    pieces[i].type = 'n';
    pieces[i].unicode = 0x265E;
    pieces[i].position[0] = 6; //x
    pieces[i].position[1] = 0; //y
    pieces[i].color = 1;
    i ++;
    pieces[i].type = 'n';
    pieces[i].unicode = 0x265E;
    pieces[i].position[0] = 1; //x
    pieces[i].position[1] = 0; //y
    pieces[i].color = 1;
    iter_row += 2;
    i++;

    //White knight
    pieces[i].type = 'n';
    pieces[i].unicode = 0x2658;
    pieces[i].position[0] = 1; //x
    pieces[i].position[1] = 7; //y
    pieces[i].color = 0;
    i ++;
    pieces[i].type = 'n';
    pieces[i].unicode = 0x2658;
    pieces[i].position[0] = 6; //x
    pieces[i].position[1] = 7; //y
    pieces[i].color = 0;
    iter_row += 2;
    i++;

    //Black bishop
    pieces[i].type = 'b';
    pieces[i].unicode = 0x265D;
    pieces[i].position[0] = 5; //x
    pieces[i].position[1] = 0; //y
    pieces[i].color = 1;
    i ++;
    pieces[i].type = 'b';
    pieces[i].unicode = 0x265D;
    pieces[i].position[0] = 2; //x
    pieces[i].position[1] = 0; //y
    pieces[i].color = 1;
    iter_row += 2;
    i++;

    //White bishop
    pieces[i].type = 'b';
    pieces[i].unicode = 0x2657;
    pieces[i].position[0] = 2; //x
    pieces[i].position[1] = 7; //y
    pieces[i].color = 0;
    i ++;
    pieces[i].type = 'b';
    pieces[i].unicode = 0x2657;
    pieces[i].position[0] = 5; //x
    pieces[i].position[1] = 7; //y
    pieces[i].color = 0;
    iter_row += 2;
    i++;

    //Black king
    pieces[i].type = 'k';
    pieces[i].unicode = 0x265A;
    pieces[i].position[0] = 3; //x
    pieces[i].position[1] = 0; //y
    pieces[i].color = 1;
    i ++;

    //White king
    pieces[i].type = 'k';
    pieces[i].unicode = 0x2654;
    pieces[i].position[0] = 3; //x
    pieces[i].position[1] = 7; //y
    pieces[i].color = 0;
    i ++;

    //Black queen
    pieces[i].type = 'q';
    pieces[i].unicode = 0x265B;
    pieces[i].position[0] = 4; //x
    pieces[i].position[1] = 0; //y
    pieces[i].color = 1;
    i ++;

    //White queen
    pieces[i].type = 'q';
    pieces[i].unicode = 0x2655;
    pieces[i].position[0] = 4; //x
    pieces[i].position[1] = 7; //y
    pieces[i].color = 0;

    return;
}