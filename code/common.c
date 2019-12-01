#include "common.h"

int get_pieces_by_pos(int pos_arr[][2], int num_pos, chess_piece pieces[NUM_CHESS_PIECES], chess_piece result[])
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

_Bool is_piece_exists(int pos_arr[2], chess_piece pieces[NUM_CHESS_PIECES])
{
    for (int i = 0; i < NUM_CHESS_PIECES; ++i)
    {
        if ((pieces[i].position[0] == pos_arr[0] && pieces[i].position[1] == pos_arr[1]) || (pos_arr[0] < 0 && pos_arr[0] > 7 && pos_arr[1] < 0 && pos_arr[1] > 7))
        {
            return 1;
        }
    }
    return 0;
}

_Bool get_one_piece_by_pos(int pos_arr[2], chess_piece pieces[NUM_CHESS_PIECES], int *result)
{
    for (int i = 0; i < NUM_CHESS_PIECES; ++i)
    {
        if ((pieces[i].position[0] == pos_arr[0] && pieces[i].position[1] == pos_arr[1]) || (pos_arr[0] < 0 && pos_arr[0] > 7 && pos_arr[1] < 0 && pos_arr[1] > 7))
        {
            *result = i;
            return 1;
        }
    }
    return 0;
}

_Bool find_pos(int pos_arr[2], chess_piece pieces[NUM_CHESS_PIECES],int color)
{
    if(pos_arr[0] < 0 && pos_arr[0] > 7 && pos_arr[1] < 0 && pos_arr[1] > 7)
    {
        return color;
    }
    for (int i = 0; i < NUM_CHESS_PIECES; ++i)
    {
        if (pieces[i].position[0] == pos_arr[0] && pieces[i].position[1] == pos_arr[1])
        {
            return pieces[i].color;
        }
    }
}