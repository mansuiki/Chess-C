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

/**
 * 위치값에 기반하여 기물을 찾는 함수
 * @param pos_arr 기물을 찾고자 하는 위치
 * @param pieces 기물 전체 배열
 * @param result 찾은 기물
 * @return 기물 찾음 여부
 */
_Bool get_one_piece_by_pos(unsigned char pos_arr[2], chess_piece pieces[NUM_CHESS_PIECES], chess_piece **result)
{
    for (int i = 0; i < NUM_CHESS_PIECES; ++i)
    {
        if ((pieces[i].position[0] == pos_arr[0] && pieces[i].position[1] == pos_arr[1]))
        {
            *result = &pieces[i];
            return 1;
        }
    }
    return 0;
}

_Bool find_pos(int pos_arr[2], chess_piece pieces[NUM_CHESS_PIECES], _Bool color)
{
    if((pos_arr[0] < 0 || pos_arr[0] > 7) && pos_arr[1] < 0 && pos_arr[1] > 7)
    {
        return !color;
    }

    for (int i = 0; i < NUM_CHESS_PIECES; ++i)
    {
        if (pieces[i].position[0] == pos_arr[0] && pieces[i].position[1] == pos_arr[1])
        {
            return pieces[i].color;
        }
    }

    return !color;
}