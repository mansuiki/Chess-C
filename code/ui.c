#include "ui.h"

/**
 *
 * @param pieces  체스 기물 배열
 * @param board 출력할 보드 배열
 * @param pieces_num 보드 위에 있는 체스 기물의 수
 */
void print_board(chess_piece pieces[32], wchar_t board[8][8], int pieces_num)
{
    for (int i = 0; i < pieces_num; ++i)
    {
        board[ pieces[i].position[1] ][ pieces[i].position[0] ] = pieces[i].unicode;
    }

    for (int row = 0; row < 8; ++row)
    {
        printf(
               "\33[1;35m%d\33[0m %lc %lc %lc %lc %lc %lc %lc %lc\n",
                row+1,
                board[row][0], board[row][1], board[row][2], board[row][3],
                board[row][4], board[row][5], board[row][6], board[row][7]
                );
    }
    printf("\33[1;35m  A B C D E F G H\33[0m\n");
}

char input_cmd(int result[2][2])
{
    char *cmd = (char *) calloc(4, sizeof(char));
    char cols[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

    scanf("%s", cmd);

    if (cmd[0] == 'H' || cmd[0] == 'S')
    {
        return cmd[0];
    }

    for (int i = 0; i < 8; ++i)
    {
        if (cmd[0] == cols[i])
        {
            result[0][0] = (int)(*cmd - 97);
        }
        if (cmd[2] == cols[i])
        {
            result[1][0] = (int)(*(cmd+2) - 97);
        }
    }
    result[0][1] = *(cmd+1) - '0';
    result[1][1] = *(cmd+3) - '0';

    return '\0';
}