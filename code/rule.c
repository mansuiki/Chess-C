#include "rule.h"
#include "pawn.h"

void move_piece(chess_piece pieces[NUM_CHESS_PIECES], int position[2][2], _Bool turn)
{
    chess_piece piece_in_position;
    int _tmp[2] = {position[1][0], position[1][1]};

    if (!get_one_piece_by_pos(_tmp, pieces))// 그곳에 유닛 있는지 체크
    {
        return;
    }

    int **coords;

    switch (piece_in_position.type)
    {
        case 'p':
        {
            int len_coords = pawn_behavior(position[0], pieces, turn, coords);
            for (int i = 0; i < len_coords; ++i)
            {
                if (coords[i][0] == position[1][0] && coords[i][1] == position[1][1])
                {
                    piece_in_position.position[0] = position[1][0];
                    piece_in_position.position[1] = position[1][1];
                }
            }
        }

    }
}