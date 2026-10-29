#include "Brain.h"
#include "Board.h"
#include "Game.h"
#include "Zobrist.h"
#include <stdint.h>

int main(){
    uint64_t whitePawns = 0x000000000000FF00; // starting position
    uint64_t whiteRooks = 0x0000000000000081; // starting position
    uint64_t whiteKnights = 0x0000000000000042; // starting position
    uint64_t whiteBishops = 0x0000000000000024; // starting position
    uint64_t whiteQueens = 0x0000000000000008; // starting position
    uint64_t whiteKing = 0x0000000000000010; // starting position

    uint64_t blackPawns = 0x00FF000000000000; // starting position
    uint64_t blackRooks = 0x8100000000000000; // starting position
    uint64_t blackKnights = 0x4200000000000000; // starting position
    uint64_t blackBishops = 0x2400000000000000; // starting position
    uint64_t blackQueens = 0x0800000000000000; // starting position
    uint64_t blackKing = 0x1000000000000000; // starting position

    uint64_t whitePieces = whitePawns|whiteRooks|whiteKnights|whiteBishops|whiteQueens|whiteKing;
    uint64_t blackPieces = blackPawns|blackRooks|blackKnights|blackBishops|blackQueens|blackKing;

    Board board = {whitePawns, whiteKnights, whiteBishops, whiteRooks, whiteQueens, whiteKing, blackPawns, blackKnights, blackBishops, blackRooks, blackQueens, blackKing, whitePieces, blackPieces};
    ArrayList moves = {NULL, NULL, 0};
    Game game = {&moves, &board, true, true, true, true, true};
    initializeZobrist(123456789);
}