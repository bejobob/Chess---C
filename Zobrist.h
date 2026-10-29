#ifndef ZOBRIST_H
#define ZOBRIST_H

#include <stdint.h>
#include <stdlib.h>
#include "Game.h"

uint64_t pieceKeys[2][6][64];
uint64_t castlingRights[16];
uint64_t enPassanT[8];
uint64_t turn;

void initializeZobrist(void);
uint64_t hash(Game* game);

#endif