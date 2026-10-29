#include "Brain.h"
#include "Board.h"
#include "Game.h"
#include "Zobrist.h"
#include "PositionDict.h"
#include "Move.h"
#include "PieceType.h"
#include "CountingZeros.c"
#include "AlphaBetaResult.h"
#include "TTentry.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

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
    Dict transpositionTable;
    initDict(&transpositionTable, 128);
    static int nodes;
    Move toPlay;
    int initialDepth;

    while (!gameOver(game)){
        addPosition()
    }
}

float staticEval(Board* board){
    float score = 0;

    for (int i = 0; i <= 1; i++){
        for (PieceType pieceType = PAWN; pieceType < KING; pieceType++){
            uint64_t volatile pieces = getBitBoard(board, pieceType, (i==0)? true:false);
            score += __builtin_popcount(pieces)*getPieceValue(pieceType);

            while (pieces != 0){
                int square = countTrailingZeros(pieces);
                score += getPieceTable(pieceType)[square] * ((i==0)?1:-1);
                pieces &= pieces -1;
            }
        }
    }
    return score;
}

ABResult AlphaBeta(Game* game, int depth, float alpha, float beta, float maxMateEval, Dict* transpositionTable, int initialDepth){
    Move* bestMove = NULL;
    uint64_t hashval = hash(game);
    TTentry* entry = getPosition(hashval, transpositionTable);

    if (entry != NULL && entry->depth >= depth){
        if (entry->boundType == EXACT){
            return (ABResult) {entry->eval, entry->bestMove};
        }
        if (entry->boundType == LOWER_BOUND){
            alpha = MAX(alpha, entry->eval);
        }
        if (entry->boundType == UPPER_BOUND){
            beta = MIN(beta, entry->eval);
        }
        if (alpha >= beta){
            return (ABResult){entry->eval, entry->bestMove};
        }
    }
    if (isCheckMate(game, getLegalMoves(game))){
        return (ABResult){game->whiteToMove? -maxMateEval + 1000*(initialDepth - depth) : maxMateEval - 1000*(initialDepth - depth), bestMove};
    }
    if (isStaleMate(game, getLegalMoves(game)) || isInsufficientMaterial(game->board) || isThreefoldRepetition(game)){
        return (ABResult){0.0f, bestMove};
    }
    if (depth == 0){
        return (ABResult){staticEval(game->board), bestMove};
    }

    float originalAlpha = alpha;
    float originalBeta = beta;
    if (game->whiteToMove){
        float maxEval = -INFINITY;
        for (Node* n = getLegalMoves(game)->first; n != NULL; n = n->next){
            makeMove(n->move, game);
            changeTurn(game);

            ABResult search = AlphaBeta(game, depth-1, alpha, beta, maxMateEval, transpositionTable, initialDepth);
            if (search.eval > maxEval){
                maxEval = search.eval;
                bestMove = n->move;
            }
            alpha = MAX(alpha, maxEval);
            unMove(n->move, game);
            changeTurn(game);

            if (beta <= alpha){
                break;
            }
        }

        BoundType bound;
        if (maxEval <= originalAlpha){
            bound = UPPER_BOUND;
        } else if (maxEval >= originalBeta){
            bound = LOWER_BOUND;
        } else {
            bound = EXACT;
        }
        TTentry toadd = (TTentry) {depth-1, hash(game), maxEval, bestMove, bound};
        addPosition(&toadd, transpositionTable);
        return (ABResult){maxEval, bestMove};
    } else {
        float minEval = INFINITY;
        for (Node* n = getLegalMoves(game)->first; n != NULL; n = n->next){
            makeMove(n->move, game);
            changeTurn(game);

            ABResult search = AlphaBeta(game, depth-1, alpha, beta, maxMateEval, transpositionTable, initialDepth);
            if (search.eval < minEval){
                minEval = search.eval;
                bestMove = n->move;
            }
            alpha = MIN(alpha, minEval);
            unMove(n->move, game);
            changeTurn(game);

            if (beta <= alpha){
                break;
            }
        }

        BoundType bound;
        if (minEval <= originalAlpha){
            bound = UPPER_BOUND;
        } else if (minEval >= originalBeta){
            bound = LOWER_BOUND;
        } else {
            bound = EXACT;
        }
        TTentry toadd = (TTentry) {depth-1, hash(game), minEval, bestMove, bound};
        addPosition(&toadd, transpositionTable);
        return (ABResult){minEval, bestMove};
    }
}