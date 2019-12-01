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
void move_piece(chess_piece pieces[NUM_CHESS_PIECES], int check_board[12][12], int position[2][2], _Bool *turn)
{
    chess_piece *piece_in_position = malloc(sizeof(chess_piece)); //이동하고자 하는 기물
    int _tmp[2] = {position[0][0], position[0][1]};
    _Bool color_in_now_position;
    if (!get_one_piece_by_pos(_tmp, pieces, &piece_in_position))// 그곳에 유닛 있는지 체크
    {
        //만약 100번대 기물을 폰이 잡을 경우 id - 100 한게 인덱스, 그 인덱스로 기물 제거
        return;
    }

    update_movable_positions(pieces, check_board, 12);

    color_in_now_position=piece_in_position->color;
    printf("turn : %d / color : %d\n",*turn,color_in_now_position);
    if(*turn^color_in_now_position)
    {
        printf("잘못된 턴 입력, 재입력을 받습니다. \n");
        return;
    }

    for (int i = 0; i < 32; ++i)
    {
        //이동하고자 하는 위치가 이동 가능 위치에 속해있는 경우
        if (piece_in_position->movable_pos[i][0] == position[1][0] &&
            piece_in_position->movable_pos[i][1] == position[1][1])
        {
            piece_in_position->position[0] = position[1][0];
            piece_in_position->position[1] = position[1][1];
            piece_in_position->move_cnt++;
            return;
        }
    }
    *turn=*turn?0:1;
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
