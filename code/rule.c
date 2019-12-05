#include "rule.h"
#include "piece.h"
#include "check.h"

/**
 * 체스 말을 움직이는 함수
 * @param pieces 전체 체스 기물 배열
 * @param check_board 고유번호 배열
 * @param position 이동 위치
 * @param turn 턴
 */
void move_piece(chess_piece pieces[NUM_CHESS_PIECES], int check_board[12][12], chess_piece *picked_piece, unsigned char pos_to_mv[2], _Bool *turn)
{
    _Bool picked_piece_color = picked_piece->color;
    if (*turn ^ picked_piece_color)
    {
        printf("자신의 말이 아닙니다. 다시 입력해주십시오. \n");
        return;
    }

    int i;
    for (i = 0; i < 32; ++i)
    {
        //이동하고자 하는 위치가 이동 가능 위치에 속해있는 경우
        if (picked_piece->movable_pos[i][0] == pos_to_mv[0] &&
            picked_piece->movable_pos[i][1] == pos_to_mv[1])
        {
            //이동하고자 하는 좌표에 적 기물이 있을 경우 죽임
            chess_piece *piece_to_kill = malloc(sizeof(chess_piece));
            if (get_one_piece_by_pos(pos_to_mv, pieces, &piece_to_kill))
            {
                if (piece_to_kill->color != *turn)
                {
                    piece_to_kill->is_dead = 1;
                }
            }

            //기물 위치 변경
            picked_piece->position[0] = pos_to_mv[0];
            picked_piece->position[1] = pos_to_mv[1];
            picked_piece->move_cnt++;

            //턴 변경
            *turn = !*turn;

            return;
        }
    }

    if (i == 32)
    {
        printf("이동할수 없는 위치입니다. 다시 입력해주십시오\n");
        return;
    }
}

/**
 * 이동하는 기물이 킹이고 이동가능 위치가 9 혹은 10일 때 실행
 * @param k
 * @param r
 * @param pos
 */
void castling(chess_piece *k, chess_piece *r, int pos[2])
{
    int tmp;
    if (k->position[0] - pos[0] > 0)
    {
        k->position[0] = pos[0];
        r->position[0] = pos[0] - 1;
    }
    else
    {
        k->position[0] = pos[0];
        r->position[0] = pos[0] + 1;
    }
}
