#include "GUI.h"
#include <stdio.h>
#include <string.h>


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

        for (int i = boardnum; i < boardnum+8; i++)
        {
            int tmp=i;
            convertPieceType(board[tmp], piecetype);
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
        case (1): /*백폰*/
        {
            strcpy(piece, "♙");
            break;
        }
        case (-1):/*흑폰*/
        {
            strcpy(piece, "♟");
            break;
        }
        case (2):/*백나이트*/
        {
            strcpy(piece, "♘");
            break;
        }
        case (-2):/*흑나이트*/
        {
            strcpy(piece, "♞");
            break;
        }
        case (3):/*백비숍*/
        {
            strcpy(piece, "♗");
            break;
        }
        case (-3):/*흑비숍*/
        {
            strcpy(piece, "♝");
            break;
        }
        case (4):/*백룩*/
        {
            strcpy(piece, "♖");
            break;
        }
        case (-4):/*흑룩*/
        {
            strcpy(piece, "♜");
            break;
        }
        case (5):/*백퀸*/
        {
            strcpy(piece, "♕");
            break;
        }
        case (-5):/*흑퀸*/
        {
            strcpy(piece, "♛");
            break;
        }
        case (6):/*백킹*/
        {
            strcpy(piece, "♔");
            break;
        }
        case (-6):/*흑킹*/
        {
            strcpy(piece, "♚");
            break;
        }
        default:/*기물 없는 체스 판*/
        {
            strcpy(piece, "·");
            break;
        }
    }
}
