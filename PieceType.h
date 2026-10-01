#ifndef UTIL_H
#define UTIL_H
#include <stdbool.h>
typedef enum PieceType{
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING 
} PieceType;

int getPieceValue(PieceType pieceType);
int getPieceLetter(PieceType pieceType, bool white);
#endif