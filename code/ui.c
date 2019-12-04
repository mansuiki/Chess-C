#include "ui.h"

/**
 *
 * @param pieces  체스 기물 배열
 * @param board 출력할 보드 배열
 * @param pieces_num 보드 위에 있는 체스 기물의 수
 */
void print_board(chess_piece pieces[32])
{
    wchar_t board[8][8] = { [0 ... 7][0 ... 7] = 0xB7 };
    for (int i = 0; i < NUM_CHESS_PIECES; ++i)
    {
        board[ pieces[i].position[1] ][ pieces[i].position[0] ] = pieces[i].unicode;
    }
    printf("      <<Black>>\n");
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
    printf("      <<White>>\n");
}

char input_cmd(unsigned char result[2])
{
    char cmd[4], cols[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

    scanf("%s", cmd);

    if (strcmp(cmd, "help") == 0)
    {
        return 'H';
    }
    if (strcmp(cmd, "save") == 0)
    {
        return 'S';
    }
    if (strcmp(cmd, "quit") == 0)
    {
        return 'X';
    }

    while (strlen(cmd) > 2)
    {
        printf("명령어가 너무 깁니다. 예) a2> ");
        scanf("%s", cmd);
    }

    for (int i = 0; i < 8; ++i)
    {
        if (cmd[0] == cols[i])
        {
            result[0] = (int) cmd[0] - 97;
            break;
        }
    }
    result[1] = cmd[1] - '0' - 1;

    return '\0';
}