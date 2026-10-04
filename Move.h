#ifndef MOVE_H
#define MOVE_H
#include "PieceType.h"
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
}Move;

char* printMove(Move* move);
#endif 