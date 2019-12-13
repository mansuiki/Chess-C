#include "AI.h"
#include "Common.h"
#include "DataTypes.h"

unsigned char GamePhase(t_board board, int turn)
{
    unsigned char phase = 0;
    unsigned char count = 0;

    switch (turn)
    {
        case 0:
            count += 0 - board[22] - board[23] - board[26] - board[27];
            if (count <= 6)
                phase = 1;
            break;
        case 1:
            count += board[92] + board[93] + board[96] + board[97];
            if (count <= 6)
                phase = 1;
            break;
    }
    return phase;
}

double EvaluateMove(t_board board, t_move Move, int *whN, int *whB, int *blN, int *blB, int turn)
{
    double score = 0;

    if (GamePhase(board, turn) == 0)
    {
        switch (Move.PieceType)
        {
            case 2:
                if (*whN == 1 && Move.Start.Rank != 1)
                    score -= 1.5;
                break;
            case -2:
                if (*blN == 1 && Move.Start.Rank != 8)
                    score += 1.5;
                break;
            case 3:
                if (*whB == 1 && Move.Start.Rank != 1)
                    score -= 1.5;
                break;
            case -3:
                if (*blB == 1 && Move.Start.Rank != 8)
                    score += 1.5;
                break;
        }
    }
    return score;
}

double EvaluatePosition(t_board Board, t_move_array Moves, int turn, t_castle Castle)
{
    double score = 0;
    double open_game = 1 - ((.125 * PawnsOnBoard(Board)) / 2);
    int i;

    if (GamePhase(Board, turn) == 0)
        score += 5.0 * QueenIsOut(Board);
    turn = 0;
    score += 99999 * (turn == 1 ? 1 : -1) * (CheckCheckmate(Board, turn, Castle) == 2 ? 1 : 0);
    score += (5 * CenterControl(Board) + .125 * CenterControl2(Board, Moves, turn, Castle));
    score += 2 * BishopPair(Board);
    score += IsCastled(Board, turn);
    for (i = 21; i < 99; i++)
    {
        if (i % 10 == 9)
        {
            i++;
            continue;
        }
        else
        {
            switch (Board[i])
            {
                case -5: /* 흑색 퀸 */
                    score -= 18;
                    break;
                case -4: /* 흑색 룩 */
                    score -= 10 + open_game;
                    break;
                case -3: /* 흑색 비숍 */
                    score -= 6 + open_game - 1.5 * IsUndeveloped(Board, i);
                    break;
                case -2: /* 흑색 나이트 */
                    score -= 6 - open_game - (.5 * KnightOnRim(i)) - 1.5 * IsUndeveloped(Board, i);
                    break;
                case -1: /* 흑색 폰 */
                    score -= 2 - .1 * (IsDoubled(Board, i)) + IsPassed(Board, i) + 9 * CanPromote(Board, i) -
                             1.5 * IsUndeveloped(Board, i);
                    break;
                case 1:     /* 백색 폰 */
                    score += 2 - .1 * (IsDoubled(Board, i)) + IsPassed(Board, i) + 9 * CanPromote(Board, i) -
                             1.5 * IsUndeveloped(Board, i);
                    break;
                case 2:     /* 백색 나이트 */
                    score += 6 - open_game - (.5 * KnightOnRim(i)) - 1.5 * IsUndeveloped(Board, i);
                    break;
                case 3:     /* 백색 비숍 */
                    score += 6 + open_game - 1.5 * IsUndeveloped(Board, i);
                    break;
                case 4:     /* 백색 나이트 */
                    score += 10 + open_game;
                    break;
                case 5:     /* 백색 퀸 */
                    score += 18;
                    break;
                default:
                    score += 0;
            }
        }
    }

    return score;

}

int PawnsOnBoard(t_board Board)
{
    int pawns = 0;
    int i;
    int piece;

    for (i = 21; i < 99; i++)
    {
        if (i % 10 == 9)
        {
            i++;
            continue;
        }
        else
        {
            piece = Board[i];
            if (piece * piece == 1)
            {
                pawns++;
            }
        }
    }
    return pawns;
}

int IsDoubled(t_board Board, int index)
{
    int doubled = 0;
    int file = GetFile(index);
    int i;

    for (i = file + 20; i < 99; i += 10)
    {
        if ((Board[i] == Board[index]) && (i != index))
        {
            doubled = 1;
            break;
        }
    }

    return doubled;
}

int KnightOnRim(int index)
{
    int onRim = 0;
    int file = GetFile(index);

    if ((file == 1) || (file == 8))
    {
        onRim = 1;
    }

    return onRim;
}

double IsCastled(t_board Board, int turn)
{
    int Castled = 0;

    switch (turn)
    {
        case 1:
            if (Board[24] == 6 || Board[25] == 6 || Board[34] == 6 || Board[35] == 6 || Board[44] == 6 ||
                Board[45] == 6 || Board[54] == 6 || Board[55] == 6 || Board[64] == 6 || Board[65] == 6 ||
                Board[74] == 6 || Board[75] == 6 || Board[84] == 6 || Board[85] == 6 || Board[94] == 6 ||
                Board[95] == 6)
            {
                Castled = 0;
            }
            else
            {
                Castled = 5;
            }
            break;
        case 0:
            if (Board[24] == -6 || Board[25] == -6 || Board[34] == -6 || Board[35] == -6 || Board[44] == -6 ||
                Board[45] == -6 || Board[54] == -6 || Board[55] == -6 || Board[64] == -6 || Board[65] == -6 ||
                Board[74] == -6 || Board[75] == -6 || Board[84] == -6 || Board[85] == -6 || Board[94] == -6 ||
                Board[95] == -6)
            {
                Castled = 0;
            }
            else
            {
                Castled = -5;
            }

            break;
    }

    return Castled;
}

int CanPromote(t_board board, int index)
{
    int can = 0;
    t_square loc = one2two(index);

    switch (board[index])
    {
        case 1:
            if (loc.Rank == 7)
                can = 1;
            break;
        case -1:
            if (loc.Rank == 2)
                can = 1;
            break;
    }
    return can;
}

int IsPassed(t_board board, int index)
{
    int passed = 1;
    t_square loc = one2two(index);
    int i = loc.Rank;

    switch (board[index])
    {
        case 1:
            for (i++; i < 9; i++)
            {
                loc.Rank = i;
                if (board[two2one(loc)] == -1)
                {
                    passed = 0;
                    break;
                }
            }
            break;
        case -1:
            for (i--; i > -1; i--)
            {
                loc.Rank = i;
                if (board[two2one(loc)] == 1)
                {
                    passed = 0;
                    break;
                }
            }
            break;
    }
    return passed;
}

int BishopPair(t_board board)
{
    int pair = 0;
    int i;

    for (i = 20; i < 99; i++)
    {
        if (board[i] == 3)
            pair++;
        else if (board[i] == -3)
            pair--;

    }
    pair = pair > 0 ? 1 : pair < 0 ? -1 : 0;
    return pair;

}

int IsUndeveloped(t_board board, int index)
{
    int isnot = 0;
    t_square loc = one2two(index);

    if (board[index] == 1)
    {
        if (loc.Rank == 2)
            isnot = 1;
    }
    else if (board[index] == -1)
    {
        if (loc.Rank == 7)
            isnot = 1;
    }
    else
    {
        if (board[index] > 0)
        {
            if (loc.Rank == 1)
                isnot = 1;
        }
        else
        {
            if (loc.Rank == 8)
                isnot = 1;
        }
    }
    return isnot;
}

int CenterControl(t_board board)
{
    int center;
    double score = 0;
    int i;

    for (i = 43; i < 47; i++)
    {
        if (board[i] == -1)
            score -= .2;
    }

    for (i = 53; i < 57; i += 3)
    {
        if (board[i] == -1)
        {
            score -= .1;
            break;
        }
    }

    for (i = 54; i < 56; i++)
    {
        if (board[i] == -1)
            score -= .5;
    }

    for (i = 73; i < 77; i++)
    {
        if (board[i] == 1)
            score += .2;
    }

    for (i = 63; i < 67; i += 3)
    {
        if (board[i] == 1)
        {
            score += .1;
            break;
        }
    }

    for (i = 64; i < 66; i++)
    {
        if (board[i] == 1)
            score += .5;
    }

    center = score > 0 ? 1 : score < 0 ? -1 : 0;
    return center;

}

char CenterControl2(t_board board, t_move_array current_turn, int turn, t_castle Castle)
{
    char score;
    int i;
    t_square End;
    t_move_array next_turn = ExhaustMoves(board, turn == 1 ? 0 : 1, Castle);

    for (i = 0; i < current_turn.Length; i++)
    {
        End = current_turn.Moves[i].End;
        if ((End.File == 4 || End.File == 5) && (End.Rank == 4 || End.Rank == 5))
        {
            if (turn == 1)
                if (current_turn.Moves[i].PieceType == 1)
                    score += 2;
                else
                    score++;
            else if (current_turn.Moves[i].PieceType == -1)
                score -= 2;
            else
                score--;
        }
    }

    for (i = 0; i < next_turn.Length; i++)
    {
        End = next_turn.Moves[i].End;
        if ((End.File == 4 || End.File == 5) && (End.Rank == 4 || End.Rank == 5))
        {
            if (turn == 1)
                if (next_turn.Moves[i].PieceType == -1)
                    score -= 2;
                else
                    score--;
            else if (next_turn.Moves[i].PieceType == 1)
                score += 2;
            else
                score++;
        }
    }

    score = score > 0 ? 1 : score < 0 ? -1 : 0;
    return score;
}

void UpdateHasMoved(t_board board, int *wNi, int *wBi, int *bNi, int *bBi)
{

    if (board[22] == 0 || board[27] == 0)
        *bNi = 1;
    if (board[23] == 0 || board[26] == 0)
        *bBi = 1;
    if (board[92] == 0 || board[97] == 0)
        *wNi = 1;
    if (board[93] == 0 || board[96] == 0)
        *wBi = 1;
}

char QueenIsOut(t_board board)
{
    char out = 0;
    unsigned int i;

    for (i = 21; i < 99; i++)
    {
        if (board[i] == 5 && one2two(i).Rank > 2)
            out++;
        else if (board[i] == -5 && one2two(i).Rank < 7)
            out--;
    }

    return out;
}
