#ifndef BOARD_H
#define BOARD_H

#include "PieceType.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct Board{
    uint64_t whitePawns;
    uint64_t whiteKnights;
    uint64_t whiteBishops;
    uint64_t whiteRooks;
    uint64_t whiteQueens;
    uint64_t whiteKing;

    uint64_t blackPawns;
    uint64_t blackKnights;
    uint64_t blackBishops;
    uint64_t blackRooks;
    uint64_t blackQueens;
    uint64_t blackKing;

    uint64_t whitePieces;
    uint64_t blackPieces;
} Board;

uint64_t getBitBoard(Board* board, PieceType pieceType, bool white);
void setBitBoard(Board* board, PieceType PieceType, bool white, long bitBoard);

PieceType getPieceOnSquare(Board* board, int square);
char* printBoard(Board* board);
char* numToAlgebraic(int square);
bool equals(Board* a, Board* b);

#endif