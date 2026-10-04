#ifndef GAME_H
#define GAME_H

#include "ArrayList.h"
#include "Board.h"
#include <stdbool.h>

typedef struct Game {
    ArrayList* playedMoves;
    // TODO: create map struct
    Board* board;
    bool whiteToMove = true;
    bool wO_O = true;
    bool wO_O_O = true;
    bool bO_O = true;
    bool bO_O_O = true;
} Game;

void changeTurn(Game* game);

void addMove(Game* game, Move move);
void removeMove(Game* game, Move move);

Move* getLastMove(Game* game);

// TODO: getPositions();
// TODO: addReachedPosition();

#endif