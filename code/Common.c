#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "AI.h"
#include "GUI.h"
#include "Common.h"
#include "DataTypes.h"


double Max(double a, double b)
{
    if (a >= b)
        return a;
    else
        return b;
}

double Min(double a, double b)
{
    if (a <= b)
        return a;
    else
        return b;
}

t_move GetBestMove(t_board board, t_castle Castle, int turn, int depth, int *wn, int *wb, int *bn, int *bb)
{
    t_coin BestMove;
    t_node top;
    double alpha = -99999;
    double beta = 99999;
    int i;

    top.Depth = -1;
    for (i = 0; i < 120; i++)
        top.Board[i] = board[i];

    if (turn == 0)
    { /* 흑색 이동 */
        BestMove = MinValue(top, Castle, alpha, beta, depth, turn, wn, wb, bn, bb);
    }
    else
    { /* 백색 이동 */
        BestMove = MaxValue(top, Castle, alpha, beta, depth, turn, wn, wb, bn, bb);
    }

    return BestMove.Move;
}

t_coin
MaxValue(t_node state, t_castle Castle, double alpha, double beta, int depth, int turn, int *WN, int *WB, int *BN,
         int *BB)
{
    t_coin poss, MinC;
    t_move_array Moves;
    t_node child = state;
    double score;
    int MoveID = 0;
    double oldAlpha = alpha;
    int i;

    state.Depth++;
    child = state;
    Moves = ExhaustMoves(state.Board, turn, Castle);
    if (state.Depth == depth)
    {
        poss.Value = EvaluatePosition(state.Board, Moves, turn, Castle);
        return poss;
    }


    for (i = 0; i < Moves.Length; i++)
    {
        child = state;
        MovePiece(child.Board, Moves.Moves[i], Castle);
        MinC = MinValue(child, Castle, alpha, beta, depth, turn == 1 ? 0 : 1, WN, WB, BN, BB);
        score = MinC.Value;
        score += EvaluateMove(state.Board, Moves.Moves[i], WN, WB, BN, BB, turn);
        alpha = Max(alpha, score);
        if (score > oldAlpha)
        {
            MoveID = i;
            oldAlpha = score;
        }
        if (alpha >= beta)
        {
            poss.Value = alpha;
            poss.Move = Moves.Moves[i];
            return poss;
        }
    }
    poss.Value = alpha;
    poss.Move = Moves.Moves[MoveID];
    return poss;
}

t_coin
MinValue(t_node state, t_castle Castle, double alpha, double beta, int depth, int turn, int *WN, int *WB, int *BN,
         int *BB)
{
    t_coin poss, MaxC;
    t_move_array Moves;
    t_node child = state;
    double score;
    int MoveID = 0;
    double oldBeta = beta;
    int i;

    state.Depth++;
    child = state;
    Moves = ExhaustMoves(state.Board, turn, Castle);
    if (state.Depth == depth)
    {
        poss.Value = EvaluatePosition(state.Board, Moves, turn, Castle);
        return poss;
    }

    for (i = 0; i < Moves.Length; i++)
    {
        child = state;
        MovePiece(child.Board, Moves.Moves[i], Castle);
        MaxC = MaxValue(child, Castle, alpha, beta, depth, turn == 0 ? 1 : 0, WN, WB, BN, BB);
        score = MaxC.Value;
        score += EvaluateMove(state.Board, Moves.Moves[i], WN, WB, BN, BB, turn);
        beta = Min(beta, score);
        if (score < oldBeta)
        {
            MoveID = i;
            oldBeta = score;
        }
        if (beta <= alpha)
        {
            poss.Value = beta;
            poss.Move = Moves.Moves[i];
            return poss;
        }
    }
    poss.Value = beta;
    poss.Move = Moves.Moves[MoveID];
    return poss;
}

void MovePiece(t_board Board, t_move Move, t_castle Castle)
{
    if (Move.PieceType == 6)
        Castle[0] = 1;
    else if (Move.PieceType == -6)
        Castle[1] = 1;
    else if (Move.PieceType == 4)
    {
        if ((two2one(Move.Start)) == 91)
            Castle[4] = 1;
        else if ((two2one(Move.Start)) == 98)
            Castle[5] = 1;
    }
    else if (Move.PieceType == -4)
    {
        if ((two2one(Move.Start)) == 21)
            Castle[2] = 1;
        else if ((two2one(Move.Start)) == 28)
            Castle[3] = 1;
    }
    Board[two2one(Move.Start)] = 0;
    Board[two2one(Move.End)] = Move.PieceType;

}

void PromotePiece(t_board board, int promotingSquare)
{
    char input[2];
    int decision;
    int validInput;

    while (1)
    {
        if (validInput == 1)
        {
            validInput = 0;
            system("clear");
            printboard(board);
            printf("\nInvalid Selection!");
        }

        printf("\n\33[1;32m[ 기물 프로모션 ]\33[0m\n");
        printf("1. 나이트\n");
        printf("2. 비숍\n");
        printf("3. 룩\n");
        printf("4. 퀸\n");
        printf("선택하세요> ");
        scanf("%s", input);
        if (input[0] > 52 || input[0] < 49)
        {
            validInput = 1;
            continue;
        }
        else
        {
            decision = input[0] - 47;
            memset(input, 0, 2);
            if (promotingSquare > 90 && promotingSquare < 99)
            {
                decision = decision * (-1);
            }
            board[promotingSquare] = decision;
        }

        break;
    }
}

int two2one(t_square Square)
{
    int one;

    one = ((10 - Square.Rank) * 10) + Square.File;

    return one;
}

t_square one2two(int oneDindex)
{
    t_square interSquare;

    interSquare.File = oneDindex % 10;
    interSquare.Rank = 9 - ((oneDindex - interSquare.File) / 10 - 1);

    return interSquare;
}

t_move_array ExhaustMoves(t_board board, int turn, t_castle Castle)
{
    t_move_array All_Moves;
    int num_moves = 0;
    t_square start;
    t_move Move;
    int i, j;

    for (i = 21; i < 99; i++)
    {
        if (board[i] != 42 && board[i] != 0)
        {
            if (turn == 0)
            {        /* 흑색 턴 */
                if (board[i] < 0)
                {
                    start = one2two(i);
                    Move.Start = start;
                    Move.PieceType = board[i];
                    switch (board[i])
                    {
                        case -6:
                            Move.End.Rank = Move.Start.Rank + 1;
                            Move.End.File = Move.Start.File - 1;
                            if (IsLegal(board, Move, turn, Castle) == 1)
                            {
                                All_Moves.Moves[num_moves] = Move;
                                num_moves++;
                            }
                            Move.End.File++;
                            if (IsLegal(board, Move, turn, Castle) == 1)
                            {
                                All_Moves.Moves[num_moves] = Move;
                                num_moves++;
                            }
                            Move.End.File++;
                            if (IsLegal(board, Move, turn, Castle) == 1)
                            {
                                All_Moves.Moves[num_moves] = Move;
                                num_moves++;
                            }
                            Move.End.Rank--;
                            if (IsLegal(board, Move, turn, Castle) == 1)
                            {
                                All_Moves.Moves[num_moves] = Move;
                                num_moves++;
                            }
                            Move.End.File -= 2;
                            if (IsLegal(board, Move, turn, Castle) == 1)
                            {
                                All_Moves.Moves[num_moves] = Move;
                                num_moves++;
                            }
                            Move.End.Rank--;
                            if (IsLegal(board, Move, turn, Castle) == 1)
                            {
                                All_Moves.Moves[num_moves] = Move;
                                num_moves++;
                            }
                            Move.End.File++;
                            if (IsLegal(board, Move, turn, Castle) == 1)
                            {
                                All_Moves.Moves[num_moves] = Move;
                                num_moves++;
                            }
                            Move.End.File++;
                            if (IsLegal(board, Move, turn, Castle) == 1)
                            {
                                All_Moves.Moves[num_moves] = Move;
                                num_moves++;
                            }
                            break;
                        case -5:
                            for (j = 21; j < 99; j++)
                            {
                                Move.End = one2two(j);
                                if (IsLegal(board, Move, turn, Castle) == 1)
                                {
                                    All_Moves.Moves[num_moves] = Move;
                                    num_moves++;
                                }
                            }
                            break;
                        case -4:
                            for (j = 21; j < 99; j++)
                            {
                                Move.End = one2two(j);
                                if (IsLegal(board, Move, turn, Castle) == 1)
                                {
                                    All_Moves.Moves[num_moves] = Move;
                                    num_moves++;
                                }
                            }
                            break;
                        case -3:
                            for (j = 21; j < 99; j++)
                            {
                                Move.End = one2two(j);
                                if (IsLegal(board, Move, turn, Castle) == 1)
                                {
                                    All_Moves.Moves[num_moves] = Move;
                                    num_moves++;
                                }
                            }
                            break;
                        case -2:
                            for (j = 21; j < 99; j++)
                            {
                                Move.End = one2two(j);
                                if (IsLegal(board, Move, turn, Castle) == 1)
                                {
                                    All_Moves.Moves[num_moves] = Move;
                                    num_moves++;
                                }
                            }
                            break;
                        case -1:

                            for (j = 21; j < 99; j++)
                            {
                                Move.End = one2two(j);
                                if (IsLegal(board, Move, turn, Castle) == 1)
                                {
                                    All_Moves.Moves[num_moves] = Move;
                                    num_moves++;
                                }
                            }
                            break;
                    }
                }
            }
            else
            {                /* 백색 턴 */
                if (board[i] > 0)
                {
                    start = one2two(i);
                    Move.Start = start;
                    Move.PieceType = board[i];
                    switch (board[i])
                    {
                        case 6:
                            Move.End.Rank = Move.Start.Rank + 1;
                            Move.End.File = Move.Start.File - 1;
                            if (IsLegal(board, Move, turn, Castle) == 1)
                            {
                                All_Moves.Moves[num_moves] = Move;
                                num_moves++;
                            }
                            Move.End.File++;
                            if (IsLegal(board, Move, turn, Castle) == 1)
                            {
                                All_Moves.Moves[num_moves] = Move;
                                num_moves++;
                            }
                            Move.End.File++;
                            if (IsLegal(board, Move, turn, Castle) == 1)
                            {
                                All_Moves.Moves[num_moves] = Move;
                                num_moves++;
                            }
                            Move.End.Rank--;
                            if (IsLegal(board, Move, turn, Castle) == 1)
                            {
                                All_Moves.Moves[num_moves] = Move;
                                num_moves++;
                            }
                            Move.End.File -= 2;
                            if (IsLegal(board, Move, turn, Castle) == 1)
                            {
                                All_Moves.Moves[num_moves] = Move;
                                num_moves++;
                            }
                            Move.End.Rank--;
                            if (IsLegal(board, Move, turn, Castle) == 1)
                            {
                                All_Moves.Moves[num_moves] = Move;
                                num_moves++;
                            }
                            Move.End.File++;
                            if (IsLegal(board, Move, turn, Castle) == 1)
                            {
                                All_Moves.Moves[num_moves] = Move;
                                num_moves++;
                            }
                            Move.End.File++;
                            if (IsLegal(board, Move, turn, Castle) == 1)
                            {
                                All_Moves.Moves[num_moves] = Move;
                                num_moves++;
                            }

                        case 5:
                            for (j = 21; j < 99; j++)
                            {
                                Move.End = one2two(j);
                                if (IsLegal(board, Move, turn, Castle) == 1)
                                {
                                    All_Moves.Moves[num_moves] = Move;
                                    num_moves++;
                                }
                            }
                            break;
                        case 4:
                            for (j = 21; j < 99; j++)
                            {
                                Move.End = one2two(j);
                                if (IsLegal(board, Move, turn, Castle) == 1)
                                {
                                    All_Moves.Moves[num_moves] = Move;
                                    num_moves++;
                                }
                            }
                            break;
                        case 3:
                            for (j = 21; j < 99; j++)
                            {
                                Move.End = one2two(j);
                                if (IsLegal(board, Move, turn, Castle) == 1)
                                {
                                    All_Moves.Moves[num_moves] = Move;
                                    num_moves++;
                                }
                            }
                            break;
                        case 2:
                            for (j = 21; j < 99; j++)
                            {
                                Move.End = one2two(j);
                                if (IsLegal(board, Move, turn, Castle) == 1)
                                {
                                    All_Moves.Moves[num_moves] = Move;
                                    num_moves++;
                                }
                            }
                            break;
                        case 1:
                            for (j = 21; j < 99; j++)
                            {
                                Move.End = one2two(j);
                                if (IsLegal(board, Move, turn, Castle) == 1)
                                {
                                    All_Moves.Moves[num_moves] = Move;
                                    num_moves++;
                                }
                            }
                            break;
                    }
                }
            }
        }
    }

    All_Moves.Length = num_moves;
    return All_Moves;
}

int GetFile(int index)
{
    t_square ret;

    ret = one2two(index);

    return ret.File;
}

int GetRank(int index)
{
    t_square ret;

    ret = one2two(index);

    return ret.Rank;
}

int IsLegal(t_board Board, t_move Move, int turn, t_castle Castle)
{
    int value = 0;
    int i = 0;
    int start_index = two2one(Move.Start);
    int end_index = two2one(Move.End);
    int difference = end_index - start_index;
    int space = 0;
    int direction = 0;

    if (Board[end_index] != 42)
    {
        switch (Move.PieceType)
        {
            case -6:    /*흑 킹 판별*/
                if (turn == 1)
                {
                    value = 0;
                    break;
                }
                if (end_index < 99 && end_index > 20 && Board[end_index] >= 0)
                {
                    if (difference == -11 || difference == -10 || difference == -9 || difference == -1 ||
                        difference == 1 || difference == 9 || difference == 10 || difference == 11)
                    {
                        value = 1;
                    }
                    else if (start_index == 25 && end_index == 27)
                    {
                        if (Board[26] == 0 && Board[27] == 0 && Board[28] == -4)
                        {
                            if (Castle[1] == 1 || Castle[3] == 1)
                                break;
                            else
                            {
                                Board[26] = -4;
                                Board[28] = 0;
                                value = 1;
                            }
                        }
                    }

                    else if (start_index == 25 && end_index == 23)
                    {
                        if (Board[22] == 0 && Board[23] == 0 && Board[24] == 0 && Board[21] == -4)
                        {
                            if (Castle[1] == 1 || Castle[2] == 1)
                                break;
                            else
                            {
                                Board[24] = -4;
                                Board[21] = 0;
                                value = 1;
                            }
                        }
                    }
                }
                break;
            case -5:    /*흑 퀸 판별*/
                if (turn == 1)
                {
                    value = 0;
                    break;
                }

                if (end_index < 99 && end_index > 20 && Board[end_index] >= 0)
                {
                    if (Move.End.File == Move.Start.File)
                    {
                        if (difference > 0)
                            direction = 10;
                        else
                            direction = -10;
                    }
                    else if (Move.End.Rank == Move.Start.Rank)
                    {
                        if (difference > 0)
                            direction = 1;
                        else
                            direction = -1;
                    }
                    else if (difference % 11 == 0)
                    {
                        if (difference > 0)
                            direction = 11;
                        else
                            direction = -11;
                    }
                    else if (difference % 9 == 0)
                    {
                        if (difference > 0)
                            direction = 9;
                        else
                            direction = -9;
                    }

                    if (direction == 0)
                    {
                        value = 0;
                        break;
                    }
                    else
                    {
                        space = difference / direction;
                    }

                    if (space == 1)
                        value = 1;
                    else
                    {
                        for (i = 1; i < space; i++)
                        {
                            if (Board[start_index + (direction * i)] != 0)
                            {
                                value = 0;
                                break;
                            }
                            else
                            {
                                value = 1;
                            }
                        }
                    }
                }
                break;
            case -4:    /*흑 룩 판별*/
                if (turn == 1)
                {
                    value = 0;
                    break;
                }

                if (end_index < 99 && end_index > 20 && Board[end_index] >= 0)
                {
                    if (Move.End.File == Move.Start.File || Move.End.Rank == Move.Start.Rank)
                    {
                        if (Move.End.File == Move.Start.File)
                        {
                            if (difference > 0)
                                direction = 10;
                            else
                                direction = -10;
                        }
                        else if (Move.End.Rank == Move.Start.Rank)
                        {
                            if (difference > 0)
                                direction = 1;
                            else
                                direction = -1;
                        }

                        space = difference / direction;

                        if (space == 1)
                            value = 1;
                        else
                        {
                            for (i = 1; i < space; i++)
                            {
                                if (Board[start_index + (direction * i)] != 0)
                                {
                                    value = 0;
                                    break;
                                }
                                else
                                {
                                    value = 1;
                                }
                            }
                        }
                    }
                }
                break;
            case -3:    /*흑 비숍 판별*/
                if (turn == 1)
                {
                    value = 0;
                    break;
                }

                if (end_index < 99 && end_index > 20 && Board[end_index] >= 0)
                {
                    if (difference % 11 == 0 || difference % 9 == 0)
                    {
                        if (difference % 11 == 0)
                        {
                            if (difference > 0)
                                direction = 11;
                            else
                                direction = -11;
                        }
                        else if (difference % 9 == 0)
                        {
                            if (difference > 0)
                                direction = 9;
                            else
                                direction = -9;
                        }

                        space = difference / direction;

                        if (space == 1)
                            value = 1;
                        else
                        {
                            for (i = 1; i < space; i++)
                            {
                                if (Board[start_index + (direction * i)] != 0)
                                {
                                    value = 0;
                                    break;
                                }
                                else
                                {
                                    value = 1;
                                }
                            }
                        }
                    }
                }
                break;
            case -2:    /*흑 나이트 판별*/
                if (turn == 1)
                {
                    value = 0;
                    break;
                }

                if (end_index < 99 && end_index > 20 && Board[end_index] >= 0)
                {
                    if (difference == -21 || difference == -19 || difference == -12 || difference == -8 ||
                        difference == 8 || difference == 12 || difference == 19 || difference == 21)
                    {
                        value = 1;
                    }
                }
                break;
            case -1:    /*흑 폰 판별*/
                if (turn == 1)
                {
                    value = 0;
                    break;
                }

                if (end_index < 99 && end_index > 20)
                {
                    if (Move.Start.Rank == 7 && Board[end_index] == 0)
                    {
                        if (difference == 10)
                        {
                            value = 1;
                        }
                        else if (difference == 20 && Board[end_index] == 0)
                        {
                            if (Board[start_index + 10] != 0)
                                break;
                            else
                                value = 1;
                        }
                        else if ((difference == 11 && Board[end_index] > 0) ||
                                 (difference == 9 && Board[end_index] > 0))
                        {
                            value = 1;
                        }
                    }
                    else
                    {
                        if (difference == 10 && Board[end_index] == 0)
                            value = 1;
                        else if ((difference == 11 && Board[end_index] > 0) ||
                                 (difference == 9 && Board[end_index] > 0))
                        {
                            value = 1;
                        }

                    }
                }

                break;
            case 1:        /*백 폰 판별*/
                if (turn == 0)
                {
                    value = 0;
                    break;
                }

                if (end_index < 99 && end_index > 20)
                {
                    if (Move.Start.Rank == 2)
                    {
                        if (difference == -10 && Board[end_index] == 0)
                            value = 1;
                        else if (difference == -20 && Board[end_index] == 0)
                        {
                            if (Board[start_index - 10] != 0)
                                break;
                            else
                                value = 1;
                        }
                        else if ((difference == -11 && Board[end_index] < 0) ||
                                 (difference == -9 && Board[end_index] < 0))
                        {
                            value = 1;
                        }
                    }

                    else
                    {
                        if (difference == -10 && Board[end_index] == 0)
                            value = 1;
                        else if ((difference == -11 && Board[end_index] < 0) ||
                                 (difference == -9 && Board[end_index] < 0))
                        {
                            value = 1;
                        }

                    }
                }

                break;
            case 2:        /*백 나이트 판별*/
                if (turn == 0)
                {
                    value = 0;
                    break;
                }


                if (end_index < 99 && end_index > 20 && Board[end_index] <= 0)
                {
                    if (difference == -21 || difference == -19 || difference == -12 || difference == -8 ||
                        difference == 8 || difference == 12 || difference == 19 || difference == 21)
                    {
                        value = 1;
                    }
                }

                break;
            case 3:        /*백 비숍 판별*/
                if (turn == 0)
                {
                    value = 0;
                    break;
                }


                if (end_index < 99 && end_index > 20 && Board[end_index] <= 0)
                {
                    if (difference % 11 == 0 || difference % 9 == 0)
                    {
                        if (difference % 11 == 0)
                        {
                            if (difference > 0)
                                direction = 11;
                            else
                                direction = -11;
                        }
                        else if (difference % 9 == 0)
                        {
                            if (difference > 0)
                                direction = 9;
                            else
                                direction = -9;
                        }

                        space = difference / direction;

                        if (space == 1)
                            value = 1;
                        else
                        {
                            for (i = 1; i < space; i++)
                            {
                                if (Board[start_index + (direction * i)] != 0)
                                {
                                    value = 0;
                                    break;
                                }
                                else
                                {
                                    value = 1;
                                }
                            }
                        }
                    }
                }
                break;
            case 4:        /*백 룩 판별*/
                if (turn == 0)
                {
                    value = 0;
                    break;
                }


                if (end_index < 99 && end_index > 20 && Board[end_index] <= 0)
                {
                    if (Move.End.File == Move.Start.File || Move.End.Rank == Move.Start.Rank)
                    {
                        if (Move.End.File == Move.Start.File)
                        {
                            if (difference > 0)
                                direction = 10;
                            else
                                direction = -10;
                        }
                        else if (Move.End.Rank == Move.Start.Rank)
                        {
                            if (difference > 0)
                                direction = 1;
                            else
                                direction = -1;
                        }

                        space = difference / direction;

                        if (space == 1)
                            value = 1;
                        else
                        {
                            for (i = 1; i < space; i++)
                            {
                                if (Board[start_index + (direction * i)] != 0)
                                {
                                    value = 0;
                                    break;
                                }
                                else
                                {
                                    value = 1;
                                }
                            }
                        }
                    }
                }
                break;
            case 5:        /*백 퀸 판별*/
                if (turn == 0)
                {
                    value = 0;
                    break;
                }


                if (end_index < 99 && end_index > 20 && Board[end_index] <= 0)
                {
                    if (Move.End.File == Move.Start.File)
                    {
                        if (difference > 0)
                            direction = 10;
                        else
                            direction = -10;
                    }
                    else if (Move.End.Rank == Move.Start.Rank)
                    {
                        if (difference > 0)
                            direction = 1;
                        else
                            direction = -1;
                    }
                    else if (difference % 11 == 0)
                    {
                        if (difference > 0)
                            direction = 11;
                        else
                            direction = -11;
                    }
                    else if (difference % 9 == 0)
                    {
                        if (difference > 0)
                            direction = 9;
                        else
                            direction = -9;
                    }
                    if (direction == 0)
                    {
                        value = 0;
                        break;
                    }
                    else
                    {
                        space = difference / direction;
                    }
                    if (space == 1)
                        value = 1;
                    else
                    {
                        for (i = 1; i < space; i++)
                        {
                            if (Board[start_index + (direction * i)] != 0)
                            {
                                value = 0;
                                break;
                            }
                            else
                            {
                                value = 1;
                            }
                        }
                    }
                }

                break;
            case 6:        /* 백 퀸 판별 */
                if (turn == 0)
                {
                    value = 0;
                    break;
                }


                if (end_index < 99 && end_index > 20 && Board[end_index] <= 0)
                {
                    if (difference == -11 || difference == -10 || difference == -9 || difference == -1 ||
                        difference == 1 || difference == 9 || difference == 10 || difference == 11)
                    {
                        value = 1;
                    }
                    else if (start_index == 95 && end_index == 97)
                    {
                        if (Board[96] == 0 && Board[97] == 0 && Board[98] == 4)
                        {
                            if (Castle[0] == 1 || Castle[5] == 1)
                                break;
                            else
                            {
                                Board[96] = 4;
                                Board[98] = 0;
                                value = 1;
                            }

                        }
                    }

                    else if (start_index == 95 && end_index == 93)
                    {
                        if (Board[92] == 0 && Board[93] == 0 && Board[94] == 0 && Board[91] == 4)
                        {
                            if (Castle[0] == 1 || Castle[4] == 1)
                                break;
                            else
                            {
                                Board[94] = 4;
                                Board[91] = 0;
                                value = 1;
                            }
                        }
                    }

                }
                break;
        }
    }
    if (value == 1)
        if (AmIinCheck(Board, Move, turn, Castle) == 1)
            value = 0;
    return value;
}

int IsLegal_Check(t_board Board, t_move Move, int turn, t_castle Castle)
{
    int value = 0;
    int i = 0;
    int start_index = two2one(Move.Start);
    int end_index = two2one(Move.End);
    int difference = end_index - start_index;
    int space = 0;
    int direction = 0;

    if (Board[end_index] != 42)
    {
        switch (Move.PieceType)
        {
            case -6:    /*흑색 킹 판별*/
                if (turn == 0)
                {
                    value = 0;
                    break;
                }


                if (end_index < 99 && end_index > 20 && Board[end_index] >= 0)
                {
                    if (difference == -11 || difference == -10 || difference == -9 || difference == -1 ||
                        difference == 1 || difference == 9 || difference == 10 || difference == 11)
                    {
                        value = 1;
                    }
                    else if (start_index == 25 && end_index == 27)
                    {
                        if (Board[26] == 0 && Board[27] == 0 && Board[28] == -4)
                        {
                            if (Castle[1] == 1 || Castle[3] == 1)
                                break;
                            else
                            {
                                Board[26] = -4;
                                Board[28] = 0;
                                value = 1;
                            }
                        }
                    }

                    else if (start_index == 25 && end_index == 23)
                    {
                        if (Board[22] == 0 && Board[23] == 0 && Board[24] == 0 && Board[21] == -4)
                        {
                            if (Castle[1] == 1 || Castle[2] == 1)
                                break;
                            else
                            {
                                Board[24] = -4;
                                Board[21] = 0;
                                value = 1;
                            }
                        }
                    }
                }
                break;
            case -5:    /*흑색 퀸 판별*/
                if (turn == 0)
                {
                    value = 0;
                    break;
                }

                if (end_index < 99 && end_index > 20 && Board[end_index] >= 0)
                {
                    if (Move.End.File == Move.Start.File)
                    {
                        if (difference > 0)
                            direction = 10;
                        else
                            direction = -10;
                    }
                    else if (Move.End.Rank == Move.Start.Rank)
                    {
                        if (difference > 0)
                            direction = 1;
                        else
                            direction = -1;
                    }
                    if (difference % 11 == 0)
                    {
                        if (difference > 0)
                            direction = 11;
                        else
                            direction = -11;
                    }
                    else if (difference % 9 == 0)
                    {
                        if (difference > 0)
                            direction = 9;
                        else
                            direction = -9;
                    }
                    if (direction == 0)
                    {
                        value = 0;
                        break;
                    }
                    else
                    {
                        space = difference / direction;
                    }
                    if (space == 1)
                        value = 1;
                    else
                    {
                        for (i = 1; i < space; i++)
                        {
                            if (Board[start_index + (direction * i)] != 0)
                            {
                                value = 0;
                                break;
                            }
                            else
                            {
                                value = 1;
                            }
                        }
                    }
                }
                break;
            case -4:    /*흑색 룩 판별*/
                if (turn == 0)
                {
                    value = 0;
                    break;
                }

                if (end_index < 99 && end_index > 20 && Board[end_index] >= 0)
                {
                    if (Move.End.File == Move.Start.File || Move.End.Rank == Move.Start.Rank)
                    {
                        if (Move.End.File == Move.Start.File)
                        {
                            if (difference > 0)
                                direction = 10;
                            else
                                direction = -10;
                        }
                        else if (Move.End.Rank == Move.Start.Rank)
                        {
                            if (difference > 0)
                                direction = 1;
                            else
                                direction = -1;
                        }

                        space = difference / direction;

                        if (space == 1)
                            value = 1;
                        else
                        {
                            for (i = 1; i < space; i++)
                            {
                                if (Board[start_index + (direction * i)] != 0)
                                {
                                    value = 0;
                                    break;
                                }
                                else
                                {
                                    value = 1;
                                }
                            }
                        }
                    }
                }
                break;
            case -3:    /*흑색 비숍 판별*/
                if (turn == 0)
                {
                    value = 0;
                    break;
                }

                if (end_index < 99 && end_index > 20 && Board[end_index] >= 0)
                {
                    if (difference % 11 == 0 || difference % 9 == 0)
                    {
                        if (difference % 11 == 0)
                        {
                            if (difference > 0)
                                direction = 11;
                            else
                                direction = -11;
                        }
                        else if (difference % 9 == 0)
                        {
                            if (difference > 0)
                                direction = 9;
                            else
                                direction = -9;
                        }

                        space = difference / direction;

                        if (space == 1)
                            value = 1;
                        else
                        {
                            for (i = 1; i < space; i++)
                            {
                                if (Board[start_index + (direction * i)] != 0)
                                {
                                    value = 0;
                                    break;
                                }
                                else
                                {
                                    value = 1;
                                }
                            }
                        }
                    }
                }
                break;
            case -2:    /*흑색 나이트 판별*/
                if (turn == 0)
                {
                    value = 0;
                    break;
                }

                if (end_index < 99 && end_index > 20 && Board[end_index] >= 0)
                {
                    if (difference == -21 || difference == -19 || difference == -12 || difference == -8 ||
                        difference == 8 || difference == 12 || difference == 19 || difference == 21)
                    {
                        value = 1;
                    }
                }
                break;
            case -1:    /*흑색 폰 판별*/
                if (turn == 0)
                {
                    value = 0;
                    break;
                }

                if (end_index < 99 && end_index > 20)
                {
                    if (Move.Start.Rank == 7 && Board[end_index] == 0)
                    {
                        if (difference == 10)
                        {
                            value = 1;
                        }
                        else if (difference == 20 && Board[end_index] == 0)
                        {
                            if (Board[start_index + 10] != 0)
                                break;
                            else
                                value = 1;
                        }
                        else if ((difference == 11 && Board[end_index] > 0) ||
                                 (difference == 9 && Board[end_index] > 0))
                        {
                            value = 1;
                        }
                    }
                    else
                    {
                        if (difference == 10 && Board[end_index] == 0)
                            value = 1;
                        else if ((difference == 11 && Board[end_index] > 0) ||
                                 (difference == 9 && Board[end_index] > 0))
                        {
                            value = 1;
                        }

                    }
                }

                break;
            case 1:        /*백색 폰 판별*/
                if (turn == 1)
                {
                    value = 0;
                    break;
                }

                if (end_index < 99 && end_index > 20)
                {
                    if (Move.Start.Rank == 2)
                    {
                        if (difference == -10 && Board[end_index] == 0)
                            value = 1;
                        else if (difference == -20 && Board[end_index] == 0)
                        {
                            if (Board[start_index - 10] != 0)
                                break;
                            else
                                value = 1;
                        }
                        else if ((difference == -11 && Board[end_index] < 0) ||
                                 (difference == -9 && Board[end_index] < 0))
                        {
                            value = 1;
                        }
                    }

                    else
                    {
                        if (difference == -10 && Board[end_index] == 0)
                            value = 1;
                        else if ((difference == -11 && Board[end_index] < 0) ||
                                 (difference == -9 && Board[end_index] < 0))
                        {
                            value = 1;
                        }

                    }
                }

                break;
            case 2:        /*백색 나이트 판별*/
                if (turn == 1)
                {
                    value = 0;
                    break;
                }

                if (end_index < 99 && end_index > 20 && Board[end_index] <= 0)
                {
                    if (difference == -21 || difference == -19 || difference == -12 || difference == -8 ||
                        difference == 8 || difference == 12 || difference == 19 || difference == 21)
                    {
                        value = 1;
                    }
                }

                break;
            case 3:        /*백색 비숍 판별*/
                if (turn == 1)
                {
                    value = 0;
                    break;
                }

                if (end_index < 99 && end_index > 20 && Board[end_index] <= 0)
                {
                    if (difference % 11 == 0 || difference % 9 == 0)
                    {
                        if (difference % 11 == 0)
                        {
                            if (difference > 0)
                                direction = 11;
                            else
                                direction = -11;
                        }
                        else if (difference % 9 == 0)
                        {
                            if (difference > 0)
                                direction = 9;
                            else
                                direction = -9;
                        }

                        space = difference / direction;

                        if (space == 1)
                            value = 1;
                        else
                        {
                            for (i = 1; i < space; i++)
                            {
                                if (Board[start_index + (direction * i)] != 0)
                                {
                                    value = 0;
                                    break;
                                }
                                else
                                {
                                    value = 1;
                                }
                            }
                        }
                    }
                }
                break;
            case 4:        /*백색 룩 판별*/
                if (turn == 1)
                {
                    value = 0;
                    break;
                }

                if (end_index < 99 && end_index > 20 && Board[end_index] <= 0)
                {
                    if (Move.End.File == Move.Start.File || Move.End.Rank == Move.Start.Rank)
                    {
                        if (Move.End.File == Move.Start.File)
                        {
                            if (difference > 0)
                                direction = 10;
                            else
                                direction = -10;
                        }
                        else if (Move.End.Rank == Move.Start.Rank)
                        {
                            if (difference > 0)
                                direction = 1;
                            else
                                direction = -1;
                        }

                        space = difference / direction;

                        if (space == 1)
                            value = 1;
                        else
                        {
                            for (i = 1; i < space; i++)
                            {
                                if (Board[start_index + (direction * i)] != 0)
                                {
                                    value = 0;
                                    break;
                                }
                                else
                                {
                                    value = 1;
                                }
                            }
                        }
                    }
                }
                break;
            case 5:        /*백색 퀸 판별*/
                if (turn == 1)
                {
                    value = 0;
                    break;
                }

                if (end_index < 99 && end_index > 20 && Board[end_index] <= 0)
                {
                    if (Move.End.File == Move.Start.File)
                    {
                        if (difference > 0)
                            direction = 10;
                        else
                            direction = -10;
                    }
                    else if (Move.End.Rank == Move.Start.Rank)
                    {
                        if (difference > 0)
                            direction = 1;
                        else
                            direction = -1;
                    }
                    else if (difference % 11 == 0)
                    {
                        if (difference > 0)
                            direction = 11;
                        else
                            direction = -11;
                    }
                    else if (difference % 9 == 0)
                    {
                        if (difference > 0)
                            direction = 9;
                        else
                            direction = -9;
                    }
                    if (direction == 0)
                    {
                        value = 0;
                        break;
                    }
                    else
                    {
                        space = difference / direction;
                    }
                    if (space == 1)
                        value = 1;
                    else
                    {
                        for (i = 1; i < space; i++)
                        {
                            if (Board[start_index + (direction * i)] != 0)
                            {
                                value = 0;
                                break;
                            }
                            else
                            {
                                value = 1;
                            }
                        }
                    }
                }

                break;
            case 6:        /* 백색 킹 판별 */
                if (turn == 1)
                {
                    value = 0;
                    break;
                }

                if (end_index < 99 && end_index > 20 && Board[end_index] <= 0)
                {
                    if (difference == -11 || difference == -10 || difference == -9 || difference == -1 ||
                        difference == 1 || difference == 9 || difference == 10 || difference == 11)
                    {
                        value = 1;
                    }
                    else if (start_index == 95 && end_index == 97)
                    {
                        if (Board[96] == 0 && Board[97] == 0 && Board[98] == 4)
                        {
                            if (Castle[0] == 1 || Castle[5] == 1)
                                break;
                            else
                            {
                                Board[96] = 4;
                                Board[98] = 0;
                                value = 1;
                            }

                        }
                    }

                    else if (start_index == 95 && end_index == 93)
                    {
                        if (Board[92] == 0 && Board[93] == 0 && Board[94] == 0 && Board[91] == 4)
                        {
                            if (Castle[0] == 1 || Castle[4] == 1)
                                break;
                            else
                            {
                                Board[94] = 4;
                                Board[91] = 0;
                                value = 1;
                            }
                        }
                    }
                }
                break;
        }
    }

    return value;
}

int AmIinCheck(t_board Board, t_move Move, int turn, t_castle Castle)
{
    int check1;
    int i, j;
    t_board Board_Copy;
    t_move MoveTest;
    t_square Nsquare, Ksquare;
    for (i = 0; i < 120; i++)
    {
        Board_Copy[i] = Board[i];
    }
    MovePiece(Board_Copy, Move, Castle);
    if (turn == 1) /* 백색 턴 */
    {
        /* 백색 킹이 움직일 수 있는 위치  */
        for (i = 1; i < 9; i++)
        {
            for (j = 1; j < 9; j++)
            {
                Ksquare.Rank = i;
                Ksquare.File = j;
                check1 = two2one(Ksquare);
                if (Board_Copy[check1] == 6)
                    break;
            }
            if (Board_Copy[check1] == 6)
                break;
        }
        /* 백색 킹을 흑색 기물이 잡을 수 있는 지 판별 */
        for (i = 1; i < 9; i++)
            for (j = 1; j < 9; j++)
            {
                Nsquare.Rank = i;
                Nsquare.File = j;
                check1 = two2one(Nsquare);
                if (Board_Copy[check1] < 0)
                {
                    MoveTest.Start = Nsquare;
                    MoveTest.End = Ksquare;
                    MoveTest.PieceType = Board_Copy[check1];
                    if (IsLegal_Check(Board_Copy, MoveTest, turn, Castle) == 1)
                        return 1;
                }
            }

        return 0;
    }
    else /* 흑색 턴 */
    {
        /* 흑색 킹이 움직일 수 있는 위치  */
        for (i = 1; i < 9; i++)
        {
            for (j = 1; j < 9; j++)
            {
                Ksquare.Rank = i;
                Ksquare.File = j;
                check1 = two2one(Ksquare);
                if (Board_Copy[check1] == -6)
                    break;
            }
            if (Board_Copy[check1] == -6)
                break;
        }
        /* 흑색 킹을 백색 기물이 잡을 수 있는 지 판별 */
        for (i = 1; i < 9; i++)
            for (j = 1; j < 9; j++)
            {
                Nsquare.Rank = i;
                Nsquare.File = j;
                check1 = two2one(Nsquare);
                if (Board_Copy[check1] > 0 && Board_Copy[check1] != 42)
                {
                    MoveTest.Start = Nsquare;
                    MoveTest.End = Ksquare;
                    MoveTest.PieceType = Board_Copy[check1];
                    if (IsLegal_Check(Board_Copy, MoveTest, turn, Castle) == 1)
                        return 1;
                }
            }

        return 0;
    }
}

int CheckCheck(t_board Board, int turn, t_castle Castle)
{
    int check1;
    int i, j;
    t_move MoveTest;
    t_square Nsquare, Ksquare;

    if (turn == 1) /* 흑색 기물이 이동을 마친 후 체크가 되는 지 */
    {
        /* 백색 킹이 움직일 수 있는 위치  */
        for (i = 1; i < 9; i++)
        {
            for (j = 1; j < 9; j++)
            {
                Ksquare.Rank = i;
                Ksquare.File = j;
                check1 = two2one(Ksquare);
                if (Board[check1] == 6)
                    break;
            }
            if (Board[check1] == 6)
                break;
        }
        /* 흑색 말이 백색 킹쪽으로 움직이는게 유효한지 확인 */
        for (i = 1; i < 9; i++)
            for (j = 1; j < 9; j++)
            {
                Nsquare.Rank = i;
                Nsquare.File = j;
                check1 = two2one(Nsquare);
                if (Board[check1] < 0)
                {
                    MoveTest.Start = Nsquare;
                    MoveTest.End = Ksquare;
                    MoveTest.PieceType = Board[check1];
                    if (IsLegal_Check(Board, MoveTest, turn, Castle) == 1)
                        return 1;
                }
            }

        return 0;
    }
    else /* 흑색 기물이 이동을 마친 후 체크가 되는 지 */
    {
        /* 흑색 킹이 움직일 수 있는 위치  */
        for (i = 1; i < 9; i++)
        {
            for (j = 1; j < 9; j++)
            {
                Ksquare.Rank = i;
                Ksquare.File = j;
                check1 = two2one(Ksquare);
                if (Board[check1] == -6)
                    break;
            }
            if (Board[check1] == -6)
                break;
        }
        /* 백색 말이 흑색 킹쪽으로 움직이는게 유효한지 확인 */
        for (i = 1; i < 9; i++)
            for (j = 1; j < 9; j++)
            {
                Nsquare.Rank = i;
                Nsquare.File = j;
                check1 = two2one(Nsquare);
                if (Board[check1] > 0 && Board[check1] != 42)
                {
                    MoveTest.Start = Nsquare;
                    MoveTest.End = Ksquare;
                    MoveTest.PieceType = Board[check1];
                    if (IsLegal_Check(Board, MoveTest, turn, Castle) == 1)
                        return 1;
                }
            }

        return 0;
    }
}

int CheckCheckmate(t_board Board, int turn, t_castle Castle)
{
    int check1;
    int i, j;
    int a, b;
/*	t_board Board_Copy;	*/
    t_move MoveTest;
    t_square Ssquare, Esquare;
    if (turn == 0) // 백색 기물이 이동했을 때 흑색 체크메이트 날 경우
    {
        for (i = 1; i < 9; i++)
        {
            for (j = 1; j < 9; j++)
            {
                Ssquare.Rank = i;
                Ssquare.File = j;
                check1 = two2one(Ssquare);
                if (Board[check1] < 0 && Board[check1] != 42)
                {
                    for (a = 1; a < 9; a++)
                    {
                        for (b = 1; b < 9; b++)
                        {
                            Esquare.Rank = a;
                            Esquare.File = b;
                            MoveTest.Start = Ssquare;
                            MoveTest.End = Esquare;
                            MoveTest.PieceType = Board[check1];
                            if (IsLegal(Board, MoveTest, turn, Castle) == 1)
                                return 1;
                            else
                                continue;
                        }
                    }
                }
                else  /*board[check1]가 흑색 기물이 아닐경우*/
                    continue;

            }
        }
    }
        /* 흑색 기물이 이동했을 때 백색 체크메이트 날 경우 */
    else
    {
        for (i = 1; i < 9; i++)
        {
            for (j = 1; j < 9; j++)
            {
                Ssquare.Rank = i;
                Ssquare.File = j;
                check1 = two2one(Ssquare);
                if (Board[check1] > 0 && Board[check1] != 42)
                {
                    for (a = 1; a < 9; a++)
                    {
                        for (b = 1; b < 9; b++)
                        {
                            Esquare.Rank = a;
                            Esquare.File = b;
                            MoveTest.Start = Ssquare;
                            MoveTest.End = Esquare;
                            MoveTest.PieceType = Board[check1];
                            if (IsLegal(Board, MoveTest, turn, Castle) == 1)
                                return 1;
                            else
                                continue;
                        }
                    }
                }
                else /* board[check1] 가 백색 기물이 아닐 경우*/
                    continue;

            }
        }
    }
    return 2;
}
