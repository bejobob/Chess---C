/**
 * Brain
 * finds all the legal moves in a position 
 * and identifies when an end-of-game condition has been met
 * @author Benjamin Kealey
 * @version 2026/09/29
 */

#include "ArrayList.h"
#include "Board.h"
#include "Move.h"
#include "PieceType.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>

ArrayList pseudoLegalMoves = {NULL, NULL, 0};

ArrayList* masterMoves(Game* game)