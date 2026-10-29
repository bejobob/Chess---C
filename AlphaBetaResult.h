#ifndef ALPHA_BETA_H
#define ALPHA_BETA_H

#include "Move.h"

typedef struct AlphaBetaResult{
    float eval;
    Move bestMove;
} ABResult;

#endif