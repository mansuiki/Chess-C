#include <stdio.h>
#include <string.h>

#include "GUI.h"

/**
 * 보드를 출력하는 함수
 * @param board 숫자로 이루어진 판 배열
 */
void printboard(t_board board)
{
    int boardnum = 21;
    int line = 8;
    char piecetype[3];

    printf("\n");
    /* number => piecetype*/
    for (int row = 0; row < 8; row++)
    {
        printf("\33[1;35m%d \33[0m", 8 - row);

        for (int i = boardnum; i < (boardnum + 8); i++)
        {
            convertPieceType(board[i], piecetype);
            printf("%s ", piecetype);
        }

        boardnum += 10;
        printf("\n");
        line--;
    }
    printf(" \33[1;35m A B C D E F G H\33[0m\n");
}


/**
 * 숫자를 기물로 변경하는 함수
 * @param num 기물 번호
 * @param piece 출력할 기물
 */
void convertPieceType(int num, char piece[3])
{

    switch (num)
    {
        case (1):
        {
            strcpy(piece, "♙");
            break;
        }
        case (-1):
        {
            strcpy(piece, "♟");
            break;
        }
        case (2):
        {
            strcpy(piece, "♘");
            break;
        }
        case (-2):
        {
            strcpy(piece, "♞");
            break;
        }
        case (3):
        {
            strcpy(piece, "♗");
            break;
        }
        case (-3):
        {
            strcpy(piece, "♝");
            break;
        }
        case (4):
        {
            strcpy(piece, "♖");
            break;
        }
        case (-4):
        {
            strcpy(piece, "♜");
            break;
        }
        case (5):
        {
            strcpy(piece, "♕");
            break;
        }
        case (-5):
        {
            strcpy(piece, "♛");
            break;
        }
        case (6):
        {
            strcpy(piece, "♔");
            break;
        }
        case (-6):
        {
            strcpy(piece, "♚");
            break;
        }
        default:
        {
            strcpy(piece, "·");
            break;
        }
    }
}
