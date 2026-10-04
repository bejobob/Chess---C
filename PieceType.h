#ifndef UTIL_H
#define UTIL_H
#include <stdbool.h>
typedef enum PieceType{
    NONE,
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING 
} PieceType;

int getPieceValue(PieceType pieceType);
int getPieceLetter(PieceType pieceType, bool white);
int getItter(PieceType pieceType);
int* getOffsets(PieceType pieceType);
#endif