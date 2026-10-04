#include "Game.h"
#include "ArrayList.h"


void changeTurn(Game* game){
    game->whiteToMove = !game->whiteToMove;
}

void addMove(Game* game, Move move){
    add(game->playedMoves, move);
}

void removeMove(Game* game, Move move){
    removeMove
}

Move* getLastMove(Game* game);