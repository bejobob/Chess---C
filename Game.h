#ifndef GAME_H
#define GAME_H

#include "ArrayList.h"
#include "Board.h"
#include <stdbool.h>

typedef struct Game {
    ArrayList* playedMoves;
    // TODO: create map struct
    Board* board;
    bool whiteToMove;
    bool wO_O;
    bool wO_O_O;
    bool bO_O;
    bool bO_O_O;
} Game;

void changeTurn(Game* game);

void addMove(Game* game, Move move);
void removeMove(Game* game, Move move);

Move* getLastMove(Game* game);

bool canCastleShort(Game* game, bool white);
bool canCastleLong(Game* game, bool white);

// TODO: getPositions();
// TODO: addReachedPosition();

#endif