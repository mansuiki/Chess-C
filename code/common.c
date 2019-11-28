#include "common.h"

int get_pieces_by_pos(int pos_arr[][2], int num_pos, chess_piece result[])
{
    int len_pieces_in_mvs;
    for (int i = 0; i < NUM_CHESS_PIECES; ++i)
    {
        for (int j = 0; j < num_pos; ++j)
        {
            if (pieces[i].position[0] == pos_arr[j][0] && pieces[i].position[1] == pos_arr[j][1])
            {
                result[i] = pieces[i];
                len_pieces_in_mvs++;
            }
        }
    }
    return len_pieces_in_mvs;
}