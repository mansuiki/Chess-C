#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ChessLog.h"

/**
 * 지난 게임의 로그를 작성하는 함수
 */
void WriteLog(int piece[], char start[][3], char end[][3], int capture[], int special[])
{
    FILE *f;
    int j, i;
    int turn = 1;

    f = fopen("log.txt", "w+");

    if (f == NULL)
    {
        printf("파일을 만드는것에 실패하였습니다");
        exit(10);
    }

    fprintf(f,
            "============================================================================================================\n");
    fprintf(f,
            "| Turn\t\tPlayer\t\tPiece\t\tStart\t\tEnd\t\tCapture\t\tSpecial    |\n|==========================================================================================================|\n");

    for (j = 0; j < 300; j++)
    {
        if (piece[j] == 0)
            break;
        if (j % 2 == 0 || j == 0)
        {
            if (j != 0)
            {
                fprintf(f,
                        "|----------------------------------------------------------------------------------------------------------|\n");
            }
            fprintf(f, "| %d.\t\t", turn);
            turn++;
        }
        else
            fprintf(f, "|\t\t");

        /* 각 플레이어와 움직인 기물을 기록합니다 */
        switch (piece[j])
        {
            case 1:
                fprintf(f, "W\t\tPawn\t\t");
                break;
            case -1:
                fprintf(f, "B\t\tPawn\t\t");
                break;
            case 2:
                fprintf(f, "W\t\tKnight\t\t");
                break;
            case -2:
                fprintf(f, "B\t\tKnight\t\t");
                break;
            case 3:
                fprintf(f, "W\t\tBishop\t\t");
                break;
            case -3:
                fprintf(f, "B\t\tBishop\t\t");
                break;
            case 4:
                fprintf(f, "W\t\tRook\t\t");
                break;
            case -4:
                fprintf(f, "B\t\tRook\t\t");
                break;
            case 5:
                fprintf(f, "W\t\tQueen\t\t");
                break;
            case -5:
                fprintf(f, "B\t\tQueen\t\t");
                break;
            case 6:
                fprintf(f, "W\t\tKing\t\t");
                break;
            case -6:
                fprintf(f, "B\t\tKing\t\t");
                break;
            default:
                fprintf(f, "ERROR");
                break;
        }


        /* 선택했던 기물의 위치와, 움직인 위치를 기록합니다 */
        for (i = 0; i < 4; i++)
        {
            if (i < 2)
            {
                fprintf(f, "%c", start[j][i]);
            }
            else
            {
                fprintf(f, "%c", end[j][i - 2]);
            }
            if (i == 1 || i == 3)
                fprintf(f, "\t\t");
        }

        /* 기물 움직임 이후 잡힌 기물을 출력합니다 */
        switch (capture[j])
        {
            case 0:
                fprintf(f, "\t\t");
                break;
            case 1:
            case -1:
                fprintf(f, "Pawn\t\t");
                break;
            case 2:
            case -2:
                fprintf(f, "Knight\t\t");
                break;
            case 3:
            case -3:
                fprintf(f, "Bishop\t\t");
                break;
            case 4:
            case -4:
                fprintf(f, "Rook\t\t");
                break;
            case 5:
            case -5:
                fprintf(f, "Queen\t\t");
                break;
            case 6:
            case -6:
                fprintf(f, "King\t\t");
                break;
            default:
                fprintf(f, "ERROR");
                break;
        }

        /* 특수 규칙에 따른 움직임들을 기록합니다 */
        switch (special[j])
        {
            case 0:
                fprintf(f, "\t   |\n");
                break;
            case 1:
                fprintf(f, "Castling   |\n");
                break;
            case 2:
                fprintf(f, "En Passant |\n");
                break;
            default:
                fprintf(f, "ERROR");
                break;
        }


    }
    fprintf(f,
            "============================================================================================================");
    fclose(f);
}