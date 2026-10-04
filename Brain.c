/**
 * Brain
 * finds all the legal moves in a position 
 * and identifies when an end-of-game condition has been met
 * @author Benjamin Kealey
 * @version 2026/09/29
 */

#include <stdbool.h>
#include <stdlib.h>


#include "ArrayList.h"
#include "Game.h"
#include "Board.h"
#include "CountingZeros.c";

ArrayList pseudoLegalMoves = {NULL, NULL, 0};

void masterMoves(Game* game, ArrayList* toPopulate){
    int* offsets;
    uint64_t specificPieces;
    int square, targetSquare, itter;
    bool breaksShortCastle = false;
    bool breaksLongCastle = false;
    bool white = game->whiteToMove;
    uint64_t otherPieces = white? game->board->blackPieces : game->board->whitePieces;
    uint64_t pieces = white? game->board->whitePieces : game->board->blackPieces;

    for (int pieceType = PAWN; pieceType < 7; pieceType++){
        offsets = getOffsets(pieceType);
        itter = getItter(pieceType);
        specificPieces = getBitBoard(game->board, pieceType, white);
        if (specificPieces == 0) continue;
        while (specificPieces != 0){
            square = countTrailingZeros(specificPieces);

            if (pieceType == ROOK || pieceType == KING){
                if (canCastleLong(game, white) || canCastleShort(game, white)){
                    if (pieceType == KING){
                        breaksLongCastle = canCastleLong(game, white);
                        breaksShortCastle = canCastleShort(game, white);
                    } else if (pieceType == ROOK){
                        if (square%8 == 0){
                            breaksLongCastle = canCastleLong(game, white);
                        } else if (square%8 == 7){
                            breaksShortCastle = canCastleShort(game, white);
                        }
                    }
                }
            }
            for (int offset = offsets; offset < sizeof(offsets)/sizeof(int); offset++){
                for (int i = 0; i < itter; i++){
                    targetSquare = square + offset*(i+1);
                    if (targetSquare < 0 || targetSquare > 63) break;
                    if (((1L << targetSquare) & pieces) != 0) break;
                    if (abs(((square + offset*i)%8)-(targetSquare % 8 )) > 2) break;
                    if (((1L << targetSquare) & otherPieces) != 0){
                        Move move = {white, square, targetSquare, targetSquare, CAPTURE, pieceType, getPieceOnSquare(game->board, targetSquare), NONE, breaksShortCastle, breaksLongCastle};
                        addToList(toPopulate, );
                    }
                }
            }
        }
    }

}




















ArrayList* castling(Game* game);
ArrayList* pawnMoves(Game* game);
ArrayList* enPassant(Game* game);
uint64_t getMoveSquares(Game* game, bool other);
ArrayList* getLegalMoves(Game* game);
void makeMove(Move move, Game* game);
void unMove(Move move, Game* game);
bool isCheckMate(Game* game, ArrayList* legalMoves);
bool isStaleMate(Game* game, ArrayList* legalMoves);
bool isInsufficientMaterial(Board* board);
bool isThreefoldRepetition(Game* game);
bool gameOver(Game* game);
char* printBoard(uint64_t board, char* header);
