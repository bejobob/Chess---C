#ifndef MOVE_H
#define MOVE_H
#include "PieceType.h"
#include "Board.h"
#include <stdbool.h>

typedef enum MoveType{
    MOVE,
    CAPTURE,
    PROMOTION,
    CAPTURE_PROMOTION,
    LONG_CASTLE,
    SHORT_CASTLE
}MoveType;

typedef struct Move{
    bool white;
    int from;
    int to;
    int captureOn;
    MoveType moveType;
    PieceType pieceType;
    PieceType captureType;
    PieceType promotionType;
    bool breaksSC;
    bool breaksLC;
    int rook;
    int king;
}Move;

bool MoveEquals(Move* a, Move* b);

Move* promotion(int from, int to, bool white, MoveType moveType, Board* board);

char* printMove(Move* move);
#endif 