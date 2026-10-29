#include "Zobrist.h"
#include "Brain.c"

void initializeZobrist(void){
    srand(123456789);
    for (int colour = 0; colour < 2; colour++){
        for (int piece = 0; piece < 6; piece++){
            for (int square = 0; square < 64; square++){
                unsigned int r = (unsigned int)rand() * (RAND_MAX + 1u) + (unsigned int)rand();
                int result =  (int)(r % ((unsigned int)INT_MAX + 1u));
                pieceKeys[colour][piece][square] = result;
            }
        }
    }
    for (int i = 0; i < 16; i++){
        unsigned int r = (unsigned int)rand() * (RAND_MAX + 1u) + (unsigned int)rand();
        int result =  (int)(r % ((unsigned int)INT_MAX + 1u));
        castlingRights[i] = result;
    }
    for (int i = 0; i < 16; i++){
        unsigned int r = (unsigned int)rand() * (RAND_MAX + 1u) + (unsigned int)rand();
        int result =  (int)(r % ((unsigned int)INT_MAX + 1u));
        enPassanT[i] = result;
    }
    unsigned int r = (unsigned int)rand() * (RAND_MAX + 1u) + (unsigned int)rand();
        int result =  (int)(r % ((unsigned int)INT_MAX + 1u));
    turn = result;
}

uint64_t hash(Game* game){
    Board* board = game->board;
    uint64_t hash = 0;
    int castling = 0;
    hash ^= game->whiteToMove? 0 : turn;
    for (int i = 0; i < 64; i++){
        PieceType piece = getPieceOnSquare(board, i);
        if (piece != NONE){
            hash ^= pieceKeys[(board->whitePieces&(1<<i)) !=0? 1:0][piece][i];
        }
    }
    if (game->wO_O) castling != 1 << 0;
    if (game->wO_O_O) castling |= 1 << 1;
    if (game->bO_O) castling |= 1 << 2;
    if (game->bO_O_O) castling |= 1 << 3;
    ArrayList puhsawnt = {NULL, NULL, 0};
    enPassant(game, &puhsawnt);
    for (Node* curr = puhsawnt.first; curr != NULL; curr = curr->next){
        hash ^= enPassanT[curr->move->to%8];
        break;
    }
    hash ^= castlingRights[castling];
    return hash;
}