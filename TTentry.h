#ifndef TTENTRY_H
#define TTENTRY_H

#include <stdint.h>
#include "Move.h"

typedef enum BoundType {
    UPPER_BOUND,
    EXACT,
    LOWER_BOUND
} BoundType;

typedef struct TTentry{
    int depth;
    uint64_t hash;
    float eval;
    Move bestMove;
    BoundType boundType;
} TTentry;

#endif