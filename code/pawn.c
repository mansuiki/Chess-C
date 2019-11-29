#include "pawn.h"

/**
 * 폰이 갈 수 있는 좌표를 알려주는 함수
 * @param curr_pos 현재 위치
 * @param pieces
 * @param turn
 * @param result
 * @return
 */
int pawn_behavior(int curr_pos[2], chess_piece pieces[NUM_CHESS_PIECES], _Bool turn, int **result)
{
    int moves[3][2] = {
            {curr_pos[0],     curr_pos[1] + (turn ? -1 : 1)},
            {curr_pos[0] - 1, curr_pos[1] + (turn ? -1 : 1)},
            {curr_pos[0 + 1], curr_pos[1] + (turn ? -1 : 1)},
    };
    int _tmp[3][2] = {NULL};

    chess_piece piece_nearby;
    int result_len = 0;

    if (moves[0][0] * moves[0][1] >= 0 && \
    (moves[0][0] < 8 && moves[0][1] < 8))
    {
        _tmp[0][0] = moves[0][0];
        _tmp[0][1] = moves[0][1];
        result_len++;
    }
    if (moves[1][0] * moves[1][1] >= 0 && \
    (moves[1][0] < 8 && moves[1][1] < 8))
    {
        if (get_one_piece_by_pos(moves[1], pieces, &piece_nearby) && piece_nearby.color != turn)
        {
            _tmp[1][0] = moves[1][0];
            _tmp[1][1] = moves[1][1];
            result_len++;
        }
    }
    if (moves[2][0] * moves[2][1] >= 0 && \
    (moves[2][0] < 8 && moves[2][1] < 8))
    {
        if (get_one_piece_by_pos(moves[2], pieces, &piece_nearby) && piece_nearby.color != turn)
        {
            _tmp[2][0] = moves[2][0];
            _tmp[2][1] = moves[2][1];
            result_len++;
        }
    }

    result = calloc(result_len*2, sizeof(int));

    int result_idx = 0;
    for (int i = 0; i < 3; ++i)
    {
        if (_tmp[i][0] != NULL && _tmp[i][1] != NULL)
        {
            memcpy(&result[result_idx], &_tmp[i], sizeof(int)*2);
            result_idx++;
        }
    }

    return result_len;
}