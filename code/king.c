#include "king.h"

void get_possible_k_mvs(int curr_pos[2], wchar_t board[8][8], _Bool result[8][8])
{
    int moves[8][2] = {
            {curr_pos[0], curr_pos[1]+1}, //{x, y}
            {curr_pos[0], curr_pos[1]-1},
            {curr_pos[0]+1, curr_pos[1]},
            {curr_pos[0]-1, curr_pos[1]},
            {curr_pos[0]+1, curr_pos[1]+1},
            {curr_pos[0]-1, curr_pos[1]+1},
            {curr_pos[0]+1, curr_pos[1]-1},
            {curr_pos[0]-1, curr_pos[1]-1},
    };

    //보드 밖으로 빠져나감 방
    for (int i = 0; i < 8; ++i)
    {
        if (moves[i][0]*moves[i][1] >= 0 && \
        (moves[i][0] < 8 && moves[i][1] < 8))
        {
            result[ moves[i][1] ][ moves[i][0] ] = 1;
        }
    }

    chess_piece pieces_in_moves[8];
    int len_pieces_in_mvs = get_pieces_by_pos(moves, 8, pieces_in_moves);

    //아군 기물과 겹침 방지
    for (int j = 0; j < len_pieces_in_mvs; ++j)
    {
        if (pieces_in_moves[j].color == _turn)
        {
            result[ pieces_in_moves[j].position[1] ][ pieces_in_moves[j].position[0] ] = 0;
        }
    }
}