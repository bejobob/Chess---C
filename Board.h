#ifndef BOARD_H
#define BOARD_H

#include "PieceType.h"
#include <stdbool.h>
typedef struct Board{
    long whitePawns;
    long whiteKnights;
    long whiteBishops;
    long whiteRooks;
    long whiteQueens;
    long whiteKing;

    long blackPawns;
    long blackKnights;
    long blackBishops;
    long blackRooks;
    long blackQueens;
    long blackKing;

    long whitePieces;
    long blackPieces;
} Board;

long getBitBoard(PieceType pieceType, bool white);
void setBitBoard(Board* board, PieceType PieceType, bool white, long bitBoard);

PieceType getPieceOnSquare(int square);
char* printBoard(Board* board);
char* numToAlgebraic(int square);
bool equals(Board* a, Board* b);

#endif