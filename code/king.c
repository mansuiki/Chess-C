#include "king.h"

int *get_possible_k_mvs(int curr_pos[2], wchar_t board[8][8])
{
    int moves[][2] = {
            {curr_pos[0], curr_pos[1]+1}, //{x, y}
            {curr_pos[0], curr_pos[1]-1},
            {curr_pos[0]+1, curr_pos[1]},
            {curr_pos[0]-1, curr_pos[1]},
            {curr_pos[0]+1, curr_pos[1]+1},
            {curr_pos[0]-1, curr_pos[1]+1},
            {curr_pos[0]+1, curr_pos[1]-1},
            {curr_pos[0]-1, curr_pos[1]-1},
    };
    int **real_moves, real_mv_cnt, i;

    for (i = 0; i < 8; ++i)
    {
        //보드 밖으로 빠져나감 방치 처리
        if (moves[i][0]*moves[i][1] < 0 && \
        (moves[i][0] > 7 && moves[i][1] > 7) && \
        board[ moves[i][1] ][ moves[i][0] ] != 0xB7)
        {
            moves[i][0] = -1;
            moves[i][1] = -1;
        }
        else
        {
            real_mv_cnt++;
        }
    }

    real_moves = (int **) calloc(real_mv_cnt, 2*sizeof(int));
    for (int j = 0; j < 8; ++j)
    {
        if (moves[j][0] != -1 && moves[j][1] != -1)
        {
            real_moves[j][0] = moves[j][0];
            real_moves[j][1] = moves[j][1];
        }
    }

    return real_moves;
}