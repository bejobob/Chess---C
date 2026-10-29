#include "Game.h"
#include "ArrayList.h"


void changeTurn(Game* game){
    game->whiteToMove = !game->whiteToMove;
}

void addMove(Game* game, Move* move){
    addToList(game->playedMoves, move);
}

void removeMove(Game* game, Move* move){
    removeAny(game->playedMoves, move);
}

Move* getLastMove(Game* game){
    return (game->playedMoves->last->move);
}

bool canCastleShort(Game* game, bool white){
    return white? game->wO_O : game->bO_O;
}

bool canCastleLong(Game* game, bool white){
    return white? game->wO_O_O : game->bO_O_O;
}