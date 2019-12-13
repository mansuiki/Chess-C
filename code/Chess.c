#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "AI.h"
#include "GUI.h"
#include "Chess.h"
#include "Common.h"
#include "ChessLog.h"
#include "DataTypes.h"

void PrintMenu();

void PrintCHESS();

int MAX = 300;
int arraynum = 0;

int main()
{
    int User = 0;
    int GameAI = 0;
    int mainmenu = 0;
    int invalidprompt = 0;
    char input[2];
    int choice1 = 0;
    int choice2 = 0;
    int choice3 = 0;
    int difficulty = 1;
    int check = 0;
    int PvP, AvA, PvA;
    int turn;
    t_board InitialBoard;
    BLIST *boardlist;
    t_castle Castle = {0, 0, 0, 0, 0, 0};
    int Black, White; /* 1 = 플레이어 0 = AI */
    int end = 0;
    int i;
    int *wN = malloc(sizeof(int));
    int *wB = malloc(sizeof(int));
    int *bN = malloc(sizeof(int));
    int *bB = malloc(sizeof(int));
    int piece[MAX], capture[MAX], special[MAX];
    char START[MAX][3], END[MAX][3];

    *wN = 0;
    *wB = 0;
    *bN = 0;
    *bB = 0;
    while (choice1 != 4)
    {
        system("clear");
        PrintCHESS();

        if (invalidprompt == 1)
        {
            invalidprompt = 0;
            printf("잘못된 선택입니다.");
        }
        else if (GameAI == 1)
        {
            GameAI = 0;
            printf("\33[0;31m게임을 시작하기 전에 게임 모드를 선택하세요.\33[0m");
        }

        PrintMenu();
        printf("옵션을 선택하세요> ");
        scanf("%s", input);
        getchar();
        /* choice1: 게임 메뉴 체크 */
        if (input[0] > 52 || input[0] < 49)
        {
            invalidprompt = 1;
            continue;/* 게임 메뉴로 돌아가기 */
        }
        else
        {
            choice1 = input[0] - 48;
            memset(input, 0, 2);
        }/* end input check:Game menu */

        while (choice1 != 3)
        { /* 게임이 시작하기전 모든 설정을 반복함 */

            switch (choice1)
            {
                case 1:
                    while (choice2 != 1 && choice2 != 2 && choice2 != 3)
                    {

                        system("clear");
                        PrintCHESS();
                        if (invalidprompt == 1)
                        {
                            invalidprompt = 0;
                            printf("Invalid Selection");
                        }

                        printf("\n\n\33[1;32m[ 게임 모드 ]\33[0m\n");
                        printf("1: 플레이어 vs 플레이어\n");
                        printf("2: 플레이어 vs AI (Beta)\n");
                        printf("3: AI vs AI (Beta)\n");

                        printf("게임 모드를 선택하세요> ");
                        scanf("%s", input);
                        /*choice2:게임모드 선택*/
                        if (input[0] > 51 || input[0] < 49)
                        {
                            invalidprompt = 1;
                            continue;/*게임 메뉴로 돌아가기*/
                        }
                        else
                        {
                            choice2 = input[0] - 48;
                            memset(input, 0, 2);
                        }

                        if (choice2 == 1)
                        {
                            PvP = 1;
                            PvA = 0;
                            AvA = 0;
                            White = 1;
                            Black = 1;
                        }

                        else if (choice2 == 2)
                        {
                            while (choice3 != 1 && choice3 != 2)
                            {
                                system("clear");
                                PrintCHESS();
                                if (invalidprompt == 1)
                                {
                                    invalidprompt = 0;
                                    printf("잘못 선택하였습니다");
                                }
                                printf("\n\n\33[1;32m[ AI 기물 ]\33[0m\n");
                                printf("1: 화이트\n");
                                printf("2: 블랙\n");

                                printf("AI의 색상을 선택하세요> ");
                                scanf("%s", input);
                                /*choice3:AI 색상 선택 메뉴*/
                                if (input[0] > 50 || input[0] < 49)
                                {
                                    invalidprompt = 1;
                                    continue;/*AI 환경 메뉴로 돌아감*/
                                }
                                else
                                {
                                    choice3 = input[0] - 48;
                                    memset(input, 0, 2);
                                }

                                if (choice3 == 1)
                                {
                                    White = 0;
                                    Black = 1;
                                }

                                else if (choice3 == 2)
                                {
                                    White = 1;
                                    Black = 0;
                                }
                            }
                            PvP = 0;
                            PvA = 1;
                            AvA = 0;
                        }

                        else if (choice2 == 3)
                        {
                            PvP = 0;
                            PvA = 0;
                            AvA = 1;
                            White = 0;
                            Black = 0;
                        }
                    }
                    choice2 = 0;
                    choice3 = 0;
                    break;
                case 2:
                    while (choice2 != 1 && choice2 != 2 && choice2 != 3 && choice2 != 4)
                    {
                        system("clear");
                        PrintCHESS();
                        if (invalidprompt == 1)
                        {
                            invalidprompt = 0;
                            printf("Invalid Selection");
                        }
                        printf("\n\33[1;32m[ AI 난이도 ]\33[0m\n");
                        printf("1: 쉬움\n");
                        printf("2: 중간\n");
                        printf("3: 어려움\n");
                        printf("4: 마스터\n");

                        printf("난이도를 선택해 주십시오> ");
                        scanf("%s", input);
                        /*choice2:AI 난이도 설정 메뉴*/
                        if (input[0] > 52 || input[0] < 49)
                        {
                            invalidprompt = 1;
                            continue;/*AI 난이도 설정 메뉴로 돌아가기*/
                        }
                        else
                        {
                            choice2 = input[0] - 48;
                            memset(input, 0, 2);
                        }

                        if (choice2 >= 1 && choice2 <= 4)
                            difficulty = choice2;
                    }
                    choice2 = 0;
                    break;
                case 4:
                    return 0;
                default:
                    break;

            }
            mainmenu = 1;
            break;
        }

        if (mainmenu == 1)
        {
            mainmenu = 0;
            continue;
        }

        for (i = 0; i < 120; i++)
        {
            InitialBoard[i] = 42;
        }

        InitialBoard[21] = -4;        /* 흑색 룩,나이트,비숍,퀸,킹 보드에 초기화 */
        InitialBoard[22] = -2;      /* -4 : 흑룩, -2 : 흑나이트, -3 : 흑비숍, -5 : 흑퀸, -6 : 흑킹*/
        InitialBoard[23] = -3;
        InitialBoard[24] = -5;
        InitialBoard[25] = -6;
        InitialBoard[26] = -3;
        InitialBoard[27] = -2;
        InitialBoard[28] = -4;

        for (i = 31; i < 39; i++)
        {    /* 흑색 폰 보드에 초기화 */
            InitialBoard[i] = -1;   /* -1 : 흑폰*/
        }

        for (i = 41; i < 79; i++)
        {    /* 중간 보드 공간 0 초기화 */
            InitialBoard[i] = 0;
        }

        InitialBoard[49] = 42;
        InitialBoard[50] = 42;
        InitialBoard[59] = 42;
        InitialBoard[60] = 42;
        InitialBoard[69] = 42;
        InitialBoard[70] = 42;
        InitialBoard[79] = 42;
        InitialBoard[80] = 42;

        for (i = 81; i < 89; i++)
        {    /* 백색 폰 보드에 초기화 */
            InitialBoard[i] = 1;    /* 1 : 백폰*/
        }

        InitialBoard[91] = 4;        /* 백색 룩,나이트,비숍,퀸,킹 보드에 초기화 */
        InitialBoard[92] = 2;       /* -4 : 백룩, -2 : 백나이트, -3 : 백비숍, -5 : 백퀸, -6 : 백킹*/
        InitialBoard[93] = 3;
        InitialBoard[94] = 5;
        InitialBoard[95] = 6;
        InitialBoard[96] = 3;
        InitialBoard[97] = 2;
        InitialBoard[98] = 4;

        boardlist = NewBoardList();
        AddBoard(&InitialBoard, boardlist);
        system("clear");
        printboard(InitialBoard); // 보드 출력

        if (PvP == 1)
        { /* PvP 모드 선택 시*/
            while (end != 1)
            {
                turn = 1;
                User = UserTurn(InitialBoard, Castle, turn, piece, START, END, capture, special, wN, wB, bN, bB);
                arraynum++;
                if (User == 1)
                {
                    arraynum = 0;
                    WriteLog(piece, START, END, capture, special);
                    break;
                }
                system("clear");
                printboard(InitialBoard);
                turn = 0;
                check = CheckCheck(InitialBoard, turn, Castle);
                if (check == 1)
                {
                    check = CheckCheckmate(InitialBoard, turn, Castle);
                }
                if (check == 2)
                {
                    WriteLog(piece, START, END, capture, special);
                    arraynum = 0;
                    printf("흰색의 승리!\n");
                    printf("Enter 를 눌러 게임을 종료하세요");
                    while (getchar() != '\n');
                    end = 1;
                }
                if (end != 1)
                {
                    turn = 0;
                    User = UserTurn(InitialBoard, Castle, turn, piece, START, END, capture, special, wN, wB, bN, bB);
                    arraynum++;
                    if (User == 1)
                    {
                        WriteLog(piece, START, END, capture, special);
                        arraynum = 0;
                        break;
                    }
                    system("clear");
                    printboard(InitialBoard);
                    check = 0;
                    turn = 1;
                    check = CheckCheck(InitialBoard, turn, Castle);
                    if (check == 1)
                    {
                        check = CheckCheckmate(InitialBoard, turn, Castle);
                    }
                    if (check == 2)
                    {
                        WriteLog(piece, START, END, capture, special);
                        arraynum = 0;
                        printf("검은색의 승리!\n");
                        printf("Enter를 눌러 게임을 종료하세요");
                        while (getchar() != '\n');
                        end = 1;
                    }
                }
                else
                    break;
            }
        }
        else if (PvA == 1 && White == 1)
        { /* PvA 모드 선택, 백색 진형 선택*/
            while (end != 1)
            {
                turn = 1;
                User = UserTurn(InitialBoard, Castle, turn, piece, START, END, capture, special, wN, wB, bN, bB);
                arraynum++;
                if (User == 1)
                {
                    WriteLog(piece, START, END, capture, special);
                    arraynum = 0;
                    break;
                }
                system("clear");
                printboard(InitialBoard);
                turn = 0;
                check = CheckCheck(InitialBoard, turn, Castle);
                if (check == 1)
                {
                    check = CheckCheckmate(InitialBoard, turn, Castle);
                }
                if (check == 2)
                {
                    WriteLog(piece, START, END, capture, special);
                    arraynum = 0;
                    printf("흰색의 승리!\n");
                    printf("Enter를 눌러 게임을 종료하세요");
                    while (getchar() != '\n');
                    end = 1;
                }
                if (end != 1)
                {
                    turn = 0;
                    AITurn(InitialBoard, Castle, turn, difficulty, piece, START, END, capture, special, wN, wB, bN, bB);
                    arraynum++;
                    system("clear");
                    printboard(InitialBoard);
                    check = 0;
                    turn = 1;
                    check = CheckCheck(InitialBoard, turn, Castle);
                    if (check == 1)
                    {
                        check = CheckCheckmate(InitialBoard, turn, Castle);
                    }
                    if (check == 2)
                    {
                        WriteLog(piece, START, END, capture, special);
                        arraynum = 0;
                        printf("Black Wins!\n");
                        printf("Enter를 눌러 게임을 종료하세요");
                        while (getchar() != '\n');
                        end = 1;
                    }
                }
                else
                    break;
            }
        }
        else if (PvA == 1 && White == 0)
        { /* PvA 모드 선택, 흑색 진형 선택*/
            while (end != 1)
            {
                turn = 1;
                AITurn(InitialBoard, Castle, turn, difficulty, piece, START, END, capture, special, wN, wB, bN, bB);
                arraynum++;
                system("clear");
                printboard(InitialBoard);
                turn = 0;
                check = CheckCheck(InitialBoard, turn, Castle);
                if (check == 1)
                {
                    check = CheckCheckmate(InitialBoard, turn, Castle);
                }
                if (check == 2)
                {
                    WriteLog(piece, START, END, capture, special);
                    arraynum = 0;
                    printf("흰색의 승리!\n");
                    printf("Enter를 눌러 게임을 종료하세요");
                    while (getchar() != '\n');
                    end = 1;
                }
                if (end != 1)
                {
                    turn = 0;
                    User = UserTurn(InitialBoard, Castle, turn, piece, START, END, capture, special, wN, wB, bN, bB);
                    arraynum++;
                    if (User == 1)
                    {
                        arraynum = 0;
                        break;
                    }
                    system("clear");
                    printboard(InitialBoard);
                    check = 0;
                    turn = 1;
                    check = CheckCheck(InitialBoard, turn, Castle);
                    if (check == 1)
                    {
                        check = CheckCheckmate(InitialBoard, turn, Castle);
                    }
                    if (check == 2)
                    {
                        WriteLog(piece, START, END, capture, special);
                        arraynum = 0;
                        printf("Black Wins!\n");
                        printf("Enter를 눌러 게임을 종료하세요");
                        while (getchar() != '\n');
                        end = 1;
                    }
                }
                else
                    break;
            }
        }
        else if (AvA == 1)
        { /* AvA 모드 선택시*/
            while (end != 1)
            {
                turn = 1;
                AITurn(InitialBoard, Castle, turn, difficulty, piece, START, END, capture, special, wN, wB, bN, bB);
                arraynum++;
                system("clear");
                printboard(InitialBoard);
                turn = 0;
                check = CheckCheck(InitialBoard, turn, Castle);
                if (check == 1)
                {
                    check = CheckCheckmate(InitialBoard, turn, Castle);
                }
                if (check == 2)
                {
                    WriteLog(piece, START, END, capture, special);
                    arraynum = 0;
                    printf("흰색의 승리!\n");
                    printf("Enter를 눌러 게임을 종료하세요");
                    while (getchar() != '\n');
                    end = 1;
                }
                if (end != 1)
                {
                    turn = 0;
                    AITurn(InitialBoard, Castle, turn, difficulty, piece, START, END, capture, special, wN, wB, bN, bB);
                    arraynum++;
                    system("clear");
                    printboard(InitialBoard);
                    turn = 1;

                    check = CheckCheck(InitialBoard, turn, Castle);
                    if (check == 1)
                    {
                        check = CheckCheckmate(InitialBoard, turn, Castle);
                    }
                    if (check == 2)
                    {
                        WriteLog(piece, START, END, capture, special);
                        arraynum = 0;
                        printf("흑 승리!\n");
                        printf("엔터키를 눌러서 계속하세요");
                        while (getchar() != '\n');
                        end = 1;
                    }
                }
                else
                    break;
            }
        }
        else
        {
            GameAI = 1;
        }
        end = 0;
        check = 0;
    }
    system("clear");
    return 0;
}

void PrintMenu()
{ /* 메뉴 출력 함수 */

    printf("\n\33[1;32m[ 게임 메뉴 ]\33[0m\n");
    printf("1: 게임 모드 선택\n");
    printf("2: AI 난이도 선택\n");
    printf("3: 게임 시작\n");
    printf("4: 나가기\n");
}

void AddBoard(t_board *board, BLIST *list)
{ /* 보드에 추가 */

    BENTRY *newentry;

    assert(list);

    newentry = (BENTRY *) malloc(sizeof(BENTRY));

    if (newentry != NULL)
    {
        newentry->List = list;
        newentry->Next = NULL;
        newentry->Prev = NULL;
        newentry->Turn = list->Turn;
        newentry->Boards = board;

        if (!list->First)
        {
            list->First = list->Last = newentry;
        }

        else
        {
            list->Last->Next = newentry;
            newentry->Prev = list->Last;
            list->Last = newentry;
        }
        list->Turn++;
    }

}

void DeleteBoard(BLIST *list)
{ /* 보드에서 제거 */

    BENTRY *entry;

    assert(list);
    assert(list->Last);

    entry = list->Last;
    list->Last = entry->Prev;
    DeleteBoard(entry->List); /* need to adjust this code */
    entry->Boards = NULL;
    free(entry);
    list->Turn--;

}

BLIST *NewBoardList(void)
{

    BLIST *newlist = (BLIST *) malloc(sizeof(BLIST));

    if (newlist != NULL)
    {
        newlist->First = NULL;
        newlist->Last = NULL;
        newlist->Turn = 0;
    }

    return newlist;
}

/**
 * 유저의 턴일 때 작동 되는 함수
 * 메인메뉴로 이동할 때 1을 리턴, 계속 진행 할 때 0을 리턴
 * 보드, 케슬링 체크, 턴, (기물, 시작점, 종료점, 잡은 기물, 특수 이동) => 로그저장에 사용, (백나이트 이동유무, 백비숍 이동유무, 흑나이트 이동유무, 흑비숍 이동유무) => AI에서 사용
 * */
int UserTurn(t_board Board, t_castle Castle, int turn, int piece[], char start[][3], char end[][3], int capture[],
             int special[], int *Wn, int *Wb, int *Bn, int *Bb)
{
    char start_rank, end_rank; // rank => 가로줄 - 숫자
    t_move Move;
    char start_file, end_file; // file => 세로줄 - 알파벳
    int validInput = 0;
    int decision;
    int i;
    char input[2];
    char startin[5], endin[3];
    static int chessboard1 = 0, chessboard2 = 0, legal = 0;

    /*유저 선택창 출력*/
    while (1)
    {
        /*이동 후 새 보드 출력*/
        if (chessboard1 != 0)
        {
            system("clear");
            printboard(Board);
        }

        chessboard1++;
/*		if(undoprompt == 2){
			undoprompt = 0;
			printf("Cannot Undo");
		}
*/
        /*선택지 입력*/
        if (validInput == 1)
        {
            validInput = 0;
            printf("Invalid Selection");
        }
        if(turn)
            printf("\n\33[1;32m [흰색의 차례입니다]\33[0m\n");
        else
            printf("\n\33[1;32m [검은색의 차례입니다]\33[0m\n");
        printf(" [1] 기물 움직이기 \n");
        printf(" [2] 메뉴로 나가기로 \n");

        printf(" 명령을 입력하세요> ");
        scanf("%s", input);
        /*선택지 판별*/
        if (input[0] > 51 || input[0] < 49)
        {
            validInput = 1;
            /*printf("Invalid Selection\n\n");*/
            continue;/*이동 메뉴로 돌아가기*/
        }
        else
        {
            decision = input[0] - 48;
            memset(input, 0, 2);
        }/*end input check:AI difficulty*/

        /*이동을 선택 했을 경우*/
        if (decision == 1)
        {
            /*파일과 랭크를 검사, 랭크 미구현*/
            while (1)
            {
                system("clear");
                printboard(Board);
                if (chessboard2 != 0)
                {
                    if (legal == 1)
                    {
                        printf("\n유효한 이동이 아닙니다.");
                        legal = 0;
                    }
                    else if (validInput != 0)
                    {
                        validInput = 0;
                        printf("\33[0;31m\n잘못된 입력입니다. 열(A~H)을 입력한 다음 행(1~8)을 입력해 주세요.\33[0m");
                    }
                }
                chessboard2++;
                printf("\n움직임을 입력하세요(선택위치 목표위치)> ");
                scanf("%s", startin);
                if (startin[3])
                {
                    start_file = startin[0];
                    start_rank = startin[1];
                    end_file = startin[2];
                    end_rank = startin[3];
                    /*logfile*/
                    start[arraynum][0] = startin[0];
                    start[arraynum][1] = startin[1];
                    end[arraynum][0] = startin[2];
                    end[arraynum][1] = startin[3];
                }
                else
                {
                    scanf("%s", endin);
                    start_file = startin[0];
                    start_rank = startin[1];
                    end_file = endin[0];
                    end_rank = endin[1];
                    /*logfile*/
                    start[arraynum][0] = startin[0];
                    start[arraynum][1] = startin[1];
                    end[arraynum][0] = endin[0];
                    end[arraynum][1] = endin[1];
                }
                getchar();

                /* 시작점, 이동점 초기화 */
                memset(startin, 0, 5);
                memset(endin, 0, 3);

                /*file 체크 => 대소문자 판별*/
                /*start_file 체크*/
                if (start_file >= 65 && start_file <= 72)
                    start_file -= 64;
                else if (start_file >= 97 && start_file <= 104)
                    start_file -= 96;
                else
                {
                    /*printf("\nInvalid start file.");*/
                    validInput++;
                }
                /*end_file 체크*/
                if (end_file >= 65 && end_file <= 72)
                    end_file -= 64;
                else if (end_file >= 97 && end_file <= 104)
                    end_file -= 96;
                else
                {
                    /*printf("\nInvalid end file.");*/
                    validInput++;
                }

                /*rank 체크*/
                if (start_rank > 56 || start_rank < 49)
                {
                    /*printf("\nInvalid start rank");*/
                    validInput++;
                }
                else
                {
                    start_rank -= 48;
                }

                if (end_rank > 56 || end_rank < 49)
                {
                    /*printf("\nInvalid end rank");*/
                    validInput++;
                }
                else
                {
                    end_rank -= 48;
                }

                if (validInput != 0)
                {
                    continue;
                }/*end if*/

                Move.Start.File = start_file;
                Move.Start.Rank = start_rank;
                Move.End.File = end_file;
                Move.End.Rank = end_rank;
                Move.PieceType = Board[two2one(Move.Start)];


                piece[arraynum] = Move.PieceType;
                capture[arraynum] = Board[two2one(Move.End)];
                special[arraynum] = 0; /*no special move*/

                if (IsLegal(Board, Move, turn, Castle) == 1)
                {
                    MovePiece(Board, Move, Castle);
                    UpdateHasMoved(Board, Wn, Wb, Bn, Bb);
                    if (turn == 1)
                    {
                        for (i = 21; i < 29; i++)
                        {
                            if (Board[i] == 1)
                            {
                                PromotePiece(Board, i);
                            }
                        }
                    }
                    else
                    {
                        for (i = 91; i < 99; i++)
                        {
                            if (Board[i] == -1)
                            {
                                PromotePiece(Board, i);
                            }
                        }
                    }

                }
                else
                {
                    /* printf("That move is not legal!\n");*/ /* Raising illegal move flag */
                    legal = 1;
                    continue;
                    /*UserTurn(Board, turn);*/
                }
                break;
            }
            break;/*유저 선택메뉴 나가기*/
        }
        else if (decision == 2)
        {/*Quit game choice*/
            chessboard1 = 0;
/*			DeleteBoardList(boardlist);
*/            return 1;
        }/*end else if:quit out of game*/

    }/*end while: user decision*/
    chessboard1 = 0;
    return 0;
}

/* AI 턴 함수 */
void AITurn(t_board Board, t_castle Castle, int turn, int difficulty, int piece[], char start[][3], char end[][3],
            int capture[], int special[], int *Wn, int *Wb, int *Bn, int *Bb)
{
    t_move Best = GetBestMove(Board, Castle, turn, difficulty, Wn, Wb, Bn, Bb);

    /*logfile*/
    piece[arraynum] = Best.PieceType;
    switch (Best.Start.File)
    {
        case 1:
            start[arraynum][0] = 'a';
            break;
        case 2:
            start[arraynum][0] = 'b';
            break;
        case 3:
            start[arraynum][0] = 'c';
            break;
        case 4:
            start[arraynum][0] = 'd';
            break;
        case 5:
            start[arraynum][0] = 'e';
            break;
        case 6:
            start[arraynum][0] = 'f';
            break;
        case 7:
            start[arraynum][0] = 'g';
            break;
        case 8:
            start[arraynum][0] = 'h';
            break;
        default:
            start[arraynum][0] = 'X';
    }/*end switch: start file*/
    switch (Best.Start.Rank)
    {
        case 1:
            start[arraynum][1] = '1';
            break;
        case 2:
            start[arraynum][1] = '2';
            break;
        case 3:
            start[arraynum][1] = '3';
            break;
        case 4:
            start[arraynum][1] = '4';
            break;
        case 5:
            start[arraynum][1] = '5';
            break;
        case 6:
            start[arraynum][1] = '6';
            break;
        case 7:
            start[arraynum][1] = '7';
            break;
        case 8:
            start[arraynum][1] = '8';
            break;
        default:
            start[arraynum][1] = 'X';
    }/*end switch: start file*/
    switch (Best.End.File)
    {
        case 1:
            end[arraynum][0] = 'a';
            break;
        case 2:
            end[arraynum][0] = 'b';
            break;
        case 3:
            end[arraynum][0] = 'c';
            break;
        case 4:
            end[arraynum][0] = 'd';
            break;
        case 5:
            end[arraynum][0] = 'e';
            break;
        case 6:
            end[arraynum][0] = 'f';
            break;
        case 7:
            end[arraynum][0] = 'g';
            break;
        case 8:
            end[arraynum][0] = 'h';
            break;
        default:
            end[arraynum][0] = 'X';
    }/*end switch: start file*/
    switch (Best.End.Rank)
    {
        case 1:
            end[arraynum][1] = '1';
            break;
        case 2:
            end[arraynum][1] = '2';
            break;
        case 3:
            end[arraynum][1] = '3';
            break;
        case 4:
            end[arraynum][1] = '4';
            break;
        case 5:
            end[arraynum][1] = '5';
            break;
        case 6:
            end[arraynum][1] = '6';
            break;
        case 7:
            end[arraynum][1] = '7';
            break;
        case 8:
            end[arraynum][1] = '8';
            break;
        default:
            end[arraynum][1] = 'X';
    }/*end switch: start file*/
    capture[arraynum] = Board[two2one(Best.End)];
    special[arraynum] = 0;/*for special move*/

/*	sleep(2);
*/    MovePiece(Board, Best, Castle);
    UpdateHasMoved(Board, Wn, Wb, Bn, Bb);

}

/*체스의 감-성을 더해줄 로고*/
void PrintCHESS()
{
    printf("\n          --------------------------------------------------  \n"); // 13칸 공백
    printf("               e88~-_   888                                     \n");
    printf("              d888   \\  888-~88e   e88~~8e    d88~\\   d88~    \n");
    printf("              8888      888  888  d888  88b  C888    C888       \n");
    printf("              8888      888  888  8888__888   Y88b    Y88b      \n");
    printf("              Y888   /  888  888  Y888    ,    888D    888D     \n");
    printf("               \"88_-~   888  888   \"88___/   \\_88P   \\_88P  \n");
    printf("\n          --------------------------------------------------  \n");
}

/*******************************/
/* 체스 판 구상도 */
/*		___________________________
 *  	8	| 21 22 23 24 25 26 27 28 |	BLACK
 *  	7	| 31 32 33 34 35 36 37 38 |
 *  R	6	| 41 42 43 44 45 46 47 48 |
 *  A	5	| 51 52 53 54 55 56 57 58 |
 *  N	4	| 61 62 63 64 65 66 67 68 |
 *  K	3	| 71 72 73 74 75 76 77 78 |
 *  	2	| 81 82 83 84 85 86 87 88 |
 *  	1	| 91 92 93 94 95 96 97 98 |	WHITE
 *  		__________________________
 *		  a  b  c  d  e  f  g  h
 *	          1  2  3  4  5  6  7  8
 *			   FILE
 *
 */
