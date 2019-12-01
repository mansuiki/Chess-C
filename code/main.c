#include <locale.h>
#include "ui.h"
#include "rule.h"
#include "piece.h"

void init(chess_piece *);

int main()
{
    setlocale(LC_ALL, "");

    _Bool turn = 1;

    int check_board[12][12] = {
        [0 ... 2][0 ... 11] = -1,
        [3 ... 9][0 ... 2] = -1,
        [3 ... 9][9 ... 11] = -1,
        [10 ... 11][0 ... 11] = -1
    };
    chess_piece pieces[NUM_CHESS_PIECES];
    for (int i = 0; i < NUM_CHESS_PIECES; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            pieces[i].directions[j][0] = 0;
            pieces[i].directions[j][1] = 0;
        }
    }
    init(pieces);

    int coordinates[2][2];
    char special_cmd;

    print_board(pieces);

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
                move_piece(pieces, check_board, coordinates, turn);
                print_board(pieces);
                break;
        }
    } while (1);

    return 0;
}

/**
 * 첫 실행 시 체스 말을 생성하는 함수
 * @param pieces 활성화할 체스 말 배열
 */
void init(chess_piece pieces[NUM_CHESS_PIECES])
{
    int i = 0, iter_row = 8;

    //Black pawn
    for (; i < iter_row; ++i)
    {
        pieces[i].position[0] = i; //x
        pieces[i].position[1] = 1; //y
        setPawn(&pieces[i], 1);
    }

    //White pawn
    iter_row += 8;
    for (; i < iter_row; ++i)
    {
        pieces[i].position[0] = i-8; //x
        pieces[i].position[1] = 6; //y
        setPawn(&pieces[i], 0);
    }

    //Black rook
    pieces[i].position[0] = 7; //x
    pieces[i].position[1] = 0; //y
    setRook(&pieces[i], 1);
    i ++;
    pieces[i].position[0] = 0; //x
    pieces[i].position[1] = 0; //y
    setRook(&pieces[i], 1);
    iter_row += 2;
    i++;

    //White rook
    pieces[i].position[0] = 7; //x
    pieces[i].position[1] = 7; //y
    setRook(&pieces[i], 0);
    i++;
    pieces[i].position[0] = 0; //x
    pieces[i].position[1] = 7; //y
    setRook(&pieces[i], 0);
    iter_row += 2;
    i++;

    //Black knight
    pieces[i].position[0] = 6; //x
    pieces[i].position[1] = 0; //y
    setKnight(&pieces[i], 1);
    i ++;
    pieces[i].position[0] = 1; //x
    pieces[i].position[1] = 0; //y
    setKnight(&pieces[i], 1);
    iter_row += 2;
    i++;

    //White knight
    pieces[i].position[0] = 1; //x
    pieces[i].position[1] = 7; //y
    setKnight(&pieces[i], 0);
    i ++;
    pieces[i].position[0] = 6; //x
    pieces[i].position[1] = 7; //y
    setKnight(&pieces[i], 0);
    iter_row += 2;
    i++;

    //Black bishop
    pieces[i].position[0] = 5; //x
    pieces[i].position[1] = 0; //y
    setBishop(&pieces[i], 1);
    i ++;
    pieces[i].position[0] = 2; //x
    pieces[i].position[1] = 0; //y
    setBishop(&pieces[i], 1);
    iter_row += 2;
    i++;

    //White bishop
    pieces[i].position[0] = 2; //x
    pieces[i].position[1] = 7; //y
    setBishop(&pieces[i], 0);
    i ++;
    pieces[i].position[0] = 5; //x
    pieces[i].position[1] = 7; //y
    setBishop(&pieces[i], 0);
    i++;

    //Black king
    pieces[i].position[0] = 3; //x
    pieces[i].position[1] = 0; //y
    setKing(&pieces[i], 1);
    i ++;

    //White king
    pieces[i].position[0] = 3; //x
    pieces[i].position[1] = 7; //y
    setKing(&pieces[i], 0);
    i ++;

    //Black queen
    pieces[i].position[0] = 4; //x
    pieces[i].position[1] = 0; //y
    setQueen(&pieces[i], 1);
    i ++;

    //White queen
    pieces[i].position[0] = 4; //x
    pieces[i].position[1] = 7; //y
    setQueen(&pieces[i], 0);

    return;
}