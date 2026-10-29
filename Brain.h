#include "ArrayList.h"
#include "Board.h"
#include "Move.h"
#include "Game.h"

#include <stdbool.h>
#include <stdint.h>

ArrayList* masterMoves(Game* game, ArrayList* toPopulate);
ArrayList* castling(Game* game, ArrayList* toPopulate);
ArrayList* pawnMoves(Game* game, ArrayList* toPopulate);
ArrayList* enPassant(Game* game, ArrayList* toPopulate);
uint64_t getMoveSquares(Game* game, bool other);
ArrayList* getLegalMoves(Game* game);
void makeMove(Move* move, Game* game);
void unMove(Move* move, Game* game);
bool isCheckMate(Game* game, ArrayList* legalMoves);
bool isStaleMate(Game* game, ArrayList* legalMoves);
bool isInsufficientMaterial(Board* board);
bool isThreefoldRepetition(Game* game);
bool gameOver(Game* game);
char* printBoard(uint64_t board, char* header);