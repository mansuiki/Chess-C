#include <locale.h>
#include "ui.h"
#include "rule.h"
#include "piece.h"
#include "check.h"
#include "option.h"

void init(chess_piece *);

int main()
{
    setlocale(LC_ALL, "");

    _Bool *turn = 0;

    int check_board[12][12] = {
            [0 ... 1][0 ... 11] = -1,
            [2 ... 9][0 ... 2] = -1,
            [2 ... 9][10 ... 11] = -1,
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
    int gameMode, aiLevel, playerSide;

    unsigned char coordinate[2], coord_picked[2];
    char special_cmd;
    chess_piece *picked_piece = malloc(sizeof(chess_piece));

    if (!setChessGameMode())// Player vs Player, Player vs AI 결정
    {
        gameMode = 0; // PVC
        aiLevel = askForDepthOfAI(); // 만일 AI와 할 경우, AI의 난이도를 설정
        playerSide = askForPlayerSide(); // Player의 순서 결정, 흰색일경우 0, 검은색일 경우 1으로
        // 추후 tern - if(PlayerSide == term ) 조건 추가
    }
    else {
        gameMode = 1; // PVP 일반 게임
    }
    print_board(pieces, 0, NULL);

    do
    {
        update_movable_positions(pieces, check_board, 12);

        turn ? printf("검은 말의 순서입니다\n") : printf("흰 말의 순서입니다\n");
        printf("기물을 선택해 주세요> ");
        special_cmd = input_cmd(coordinate);

        switch (special_cmd)
        {
            case 'H':
                printf("Display help\n");
                break;

            case 'S':
                printf("Save file\n");
                break;

            case 'X':
                return 0;

            case -1:
                printf("Command not found\n");
                break;

            default:
                //고른 좌표에 유닛이 있는지 체크
                get_one_piece_by_pos(coordinate, pieces, &picked_piece);
                //유닛을 고를 때까지 반복
                while (picked_piece == NULL)
                {
                    printf("빈 공간을 선택하였습니다. 다시 선택해 주세요> ");
                    input_cmd(coordinate);
                    get_one_piece_by_pos(coordinate, pieces, &picked_piece);
                }

                coord_picked[0] = coordinate[0];
                coord_picked[1] = coordinate[1];
                print_board(pieces, 1, coord_picked);

                //가고자할 좌표 입력
                printf("가고자 할 위치를 선택해 주세요> ");
                input_cmd(coordinate);

                //기물 이동
                move_piece(pieces, check_board, picked_piece, coordinate, &turn);
                print_board(pieces, 0, NULL);
                reset(pieces, check_board, 12);
                break;
        }
    }
    while (1);
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
        pieces[i].position[0] = i - 8; //x
        pieces[i].position[1] = 6; //y
        setPawn(&pieces[i], 0);
    }

    //Black rook
    pieces[i].position[0] = 7; //x
    pieces[i].position[1] = 0; //y
    setRook(&pieces[i], 1);
    i++;
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
    i++;
    pieces[i].position[0] = 1; //x
    pieces[i].position[1] = 0; //y
    setKnight(&pieces[i], 1);
    iter_row += 2;
    i++;

    //White knight
    pieces[i].position[0] = 1; //x
    pieces[i].position[1] = 7; //y
    setKnight(&pieces[i], 0);
    i++;
    pieces[i].position[0] = 6; //x
    pieces[i].position[1] = 7; //y
    setKnight(&pieces[i], 0);
    iter_row += 2;
    i++;

    //Black bishop
    pieces[i].position[0] = 5; //x
    pieces[i].position[1] = 0; //y
    setBishop(&pieces[i], 1);
    i++;
    pieces[i].position[0] = 2; //x
    pieces[i].position[1] = 0; //y
    setBishop(&pieces[i], 1);
    iter_row += 2;
    i++;

    //White bishop
    pieces[i].position[0] = 2; //x
    pieces[i].position[1] = 7; //y
    setBishop(&pieces[i], 0);
    i++;
    pieces[i].position[0] = 5; //x
    pieces[i].position[1] = 7; //y
    setBishop(&pieces[i], 0);
    i++;

    //Black king
    pieces[i].position[0] = 4; //x
    pieces[i].position[1] = 0; //y
    setKing(&pieces[i], 1);
    i++;

    //White king
    pieces[i].position[0] = 4; //x
    pieces[i].position[1] = 7; //y
    setKing(&pieces[i], 0);
    i++;

    //Black queen
    pieces[i].position[0] = 3; //x
    pieces[i].position[1] = 0; //y
    setQueen(&pieces[i], 1);
    i++;

    //White queen
    pieces[i].position[0] = 3; //x
    pieces[i].position[1] = 7; //y
    setQueen(&pieces[i], 0);

    return;
}