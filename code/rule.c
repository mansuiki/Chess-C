#include "rule.h"
#include "piece.h"
#include "check.h"

void move_piece(chess_piece pieces[NUM_CHESS_PIECES], int position[2][2], _Bool turn)
{
    chess_piece *piece_in_position = malloc(sizeof(chess_piece)); //이동하고자 하는 기물
    int _tmp[2] = {position[0][0], position[0][1]};

    if (!get_one_piece_by_pos(_tmp, pieces, &piece_in_position))// 그곳에 유닛 있는지 체크
    {
        return;
    }

    update_movable_positions(pieces);

    for (int i = 0; i < 32; ++i)
    {
        //이동하고자 하는 위치가 이동 가능 위치에 속해있는 경우
        if (piece_in_position->movable_pos[i][0] == position[1][0] \
         && piece_in_position->movable_pos[i][1] == position[1][1])
        {
            piece_in_position->position[0] = position[1][0];
            piece_in_position->position[1] = position[1][1];
        }
    }
}