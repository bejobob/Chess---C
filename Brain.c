/**
 * Brain
 * finds all the legal moves in a position 
 * and identifies when an end-of-game condition has been met
 * @author Benjamin Kealey
 * @version 2026/09/29
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


#include "ArrayList.h"
#include "Game.h"
#include "Board.h"
#include "CountingZeros.c"

ArrayList pseudoLegalMoves = {NULL, NULL, 0};
ArrayList actualLegalMoves = {NULL, NULL, 0};

void masterMoves(Game* game, ArrayList* toPopulate){
    int* offsets;
    uint64_t specificPieces;
    short unsigned int square, targetSquare, itter;
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
            for (int offsetIndex = 0; offsetIndex < sizeof(offsets)/sizeof(int); offsetIndex++){
                int offset = offsets[offsetIndex];
                for (int i = 0; i < itter; i++){
                    targetSquare = square + offset*(i+1);
                    if (targetSquare < 0 || targetSquare > 63) break;
                    if (((1L << targetSquare) & pieces) != 0) break;
                    if (abs(((square + offset*i)%8)-(targetSquare % 8 )) > 2) break;
                    if (((1L << targetSquare) & otherPieces) != 0){
                        Move move = {white, square, targetSquare, targetSquare, CAPTURE, pieceType, getPieceOnSquare(game->board, targetSquare), NONE, breaksShortCastle, breaksLongCastle};
                        addToList(toPopulate, &move);
                        break;
                    } else {
                        Move move = {white, square, targetSquare, -1, MOVE, pieceType, NONE, NONE, breaksShortCastle, breaksLongCastle};
                        addToList(toPopulate, &move);
                    }
                }
            }
            specificPieces &= ~(1L << (square));
        }
        free(offsets);
    }
}
ArrayList* pawnMoves(Game* game, ArrayList* toPopulate){
    Board* board = game->board;
    bool white = game->whiteToMove;
    uint64_t volatile pawns = board->whitePawns;
    short unsigned int startingRank = white? 1 : 6;
    short unsigned int promotionRank = white? 7 : 0;
    short forward = white? 8 : -8;
    short captureRight = white? 9 : -7;
    short captureLeft = white? 7 : -9;
    short unsigned volatile int square;
    uint64_t otherPieces = white? board->whitePieces : board->blackPieces;
    while (pawns != 0){
        square = countTrailingZeros(pawns);
        if (getPieceOnSquare(board, square) == NONE){
            if ((square/8 == startingRank)&&(getPieceOnSquare(board, square+2*forward) == NONE)){
                Move move = (Move) {white, square, square+2*forward, -1, MOVE, PAWN, NONE, NONE, false, false};
                addToList(toPopulate, &move);
            }
            if ((square+forward)/8 == promotionRank){ //TODO: do C and Java division work the same?
                Move* toAdd = promotion(square, square+forward, white, MOVE, board);
                for (int i = 0; i < 4; i++){
                    addToList(toPopulate, &toAdd[i]);
                }
            } else {
                Move move = (Move) {white, square, square+forward, -1, MOVE, PAWN, NONE, NONE, false, false};
                addToList(toPopulate, &move);
            }
        }
        if (((1L<<(square+captureRight)) & otherPieces) != 0 && (abs(square%8 - (square+captureRight)%8) == 1)){
            if ((square+captureRight)/8 == promotionRank){
                Move* toAdd = promotion(square, square+captureRight, white, CAPTURE_PROMOTION, board);
                for (int i = 0; i < 4; i++){
                    addToList(toPopulate, &toAdd[i]);
                }
            } else {
                Move move = (Move) {white, square, square+captureRight, square+captureRight, CAPTURE, PAWN, getPieceOnSquare(board, square+captureRight), NONE, false, false};
                addToList(toPopulate, &move);
            }
        }
        if (((1L<<(square+captureLeft)) & otherPieces) != 0 && (abs(square%8 - (square+captureLeft)%8) == 1)){
            if ((square+captureLeft)/8 == promotionRank){
                Move* toAdd = promotion(square, square+captureLeft, white, CAPTURE_PROMOTION, board);
                for (int i = 0; i < 4; i++){
                    addToList(toPopulate, &toAdd[i]);
                }
            } else {
                Move move = (Move) {white, square, square+captureLeft, square+captureLeft, CAPTURE, PAWN, getPieceOnSquare(board, square+captureLeft), NONE, false, false};
                addToList(toPopulate, &move);
            }
        }

        pawns &= ~(1L<<square);
    }
}
uint64_t getMoveSquares(Game* game, bool other){
    uint64_t toReturn = 0;
    if (other) changeTurn(game);
    ArrayList otherMoves = (ArrayList) {NULL, NULL, 0};
    masterMoves(game, &otherMoves);
    Node* curr = otherMoves.first;
    while (curr != NULL){
        toReturn |= 1 << curr->move->to;
        curr = curr->next;
    }
    ArrayList pawnMovesList = (ArrayList) {NULL, NULL, 0};
    pawnMoves(game, &pawnMovesList);
    curr = pawnMovesList.first;
    while (curr != NULL){
        Move move = *curr->move;
        if (move.moveType == MOVE){
            if (abs(move.to%8 - (move.to+8)%8) == 1){
                toReturn |= 1 << (move.to + (move.white? 9 : -9));
            }
            if (abs(move.to%8 - (move.to-8)%8) == 1){
                toReturn |= 1 << (move.to + (move.white? 7 : -7));
            }
        }
        curr = curr->next;
    }
    if (other) changeTurn;
    destroy(&otherMoves);
    return toReturn;
}

ArrayList* castling(Game* game, ArrayList* toPopulate){
    bool white = game->whiteToMove;
    uint64_t king = getBitBoard(game->board, KING, game->whiteToMove);
    uint64_t rooks = getBitBoard(game->board, ROOK, game->whiteToMove);
    uint64_t pieces = white? game->board->whitePieces : game->board->blackPieces;
    uint64_t otherPieces = white? game->board->blackPieces : game->board->whitePieces;
    short unsigned int square = countTrailingZeros(king);
    if ((king&getMoveSquares(game, true)) == 0){
        if (canCastleLong(game, white)){
            if (((king >> 1 | king >> 2 | king >> 3)&(pieces|otherPieces)) == 0L){
                if ((1L & rooks) != 0){
                    Move move = {white, square, square-4, -1, LONG_CASTLE, KING, NONE, NONE, true, true, square - 4, square};
                    addToList(toPopulate, &move);
                }
            }
        }
        if (canCastleShort(game, white)){
            if (((king << 1 | king << 2)&(pieces|otherPieces)) == 0L){
                if (((1L << 7) & rooks) != 0){
                    Move move = {white, square, square+3, -1, SHORT_CASTLE, KING, NONE, NONE, true, true, square + 3, square};
                    addToList(toPopulate, &move);
                }
            }
        }
    }
}



ArrayList* enPassant(Game* game, ArrayList* toPopulate){
    Board* board = game->board;
    bool white = game->whiteToMove;
    uint64_t volatile pawns = white? board->whitePawns : board->blackPawns;
    uint8_t volatile square;

    if (getLastMove(game) != NULL){
        Move lastMove = *getLastMove(game);
        if (lastMove.pieceType == PAWN){
            if (abs(lastMove.from - lastMove.to) == 16){
                if (lastMove.to/8 == (lastMove.white? 3 : 4)){
                    while (pawns != 0){
                        square = countTrailingZeros(pawns);
                        if (abs((lastMove.to%8) - (square%8)) == 1){
                            if ((lastMove.to/8) - (square/8) == 0){
                                Move move = (Move) {white, square, lastMove.to + (white? 8 : -8), lastMove.to, CAPTURE, PAWN, PAWN, NONE, false, false};
                                addToList(toPopulate, &move);
                            }
                        }
                        pawns &= ~(1L<<square);
                    }
                }
            }
        }
    }

}

void makeMove(Move* move, Game* game){
    Board* board = game->board;
    uint64_t pieces = (move->pieceType == NONE)? 0 : getBitBoard(board, move->pieceType, move->white);
    uint64_t capturedPieces;
    uint64_t promotionPieces = (move->promotionType == NONE)? 0 : getBitBoard(board, move->pieceType, move->white);

    if (move->moveType == MOVE){
        pieces &= ~(1 << move->from);
        pieces |= 1 << move->to;
        setBitBoard(board, move->pieceType, move->white, pieces);
    } else if (move->moveType == CAPTURE){
        if (move->captureType == NONE){
            // handle errors? shouldn't happen, really
        }
        capturedPieces = getBitBoard(board, move->captureType, !move->white);
        pieces &= ~(1 << move->from);
        pieces |= 1 << move->to;
        capturedPieces &= ~(1 << move->captureOn);
        setBitBoard(board, move->pieceType, move->white, pieces);
        setBitBoard(board, move->captureOn, !move->white, capturedPieces);
    } else if (move->moveType == PROMOTION){
        pieces &= ~ (1 << move->from);
        promotionPieces |= 1 << move->to;
        setBitBoard(board, move->pieceType, move->white, pieces);
        setBitBoard(board, move->promotionType, move->white, promotionPieces);
    } else if (move->moveType == CAPTURE_PROMOTION){
        capturedPieces = getBitBoard(board, move->captureType, !move->white);
        pieces &= ~(1 << move->from);
        promotionPieces |= 1 << move->to;
        capturedPieces &= ~(1 << move->to);
        setBitBoard(board, move->pieceType, move->white, pieces);
        setBitBoard(board, move->promotionType, move->white, promotionPieces);
        setBitBoard(board, move->captureType, !move->white, capturedPieces);
    } else if (move->moveType == LONG_CASTLE){ // long castle
        pieces = getBitBoard(board, KING, move->white);
        pieces &= ~(1L << move->king);
        pieces |= 1L << (move->king - 2);
        setBitBoard(board, KING, move->white, pieces); // get, remove, add, and set king
        pieces = getBitBoard(board, ROOK, move->white);
        pieces &= ~(1L << move->rook);
        pieces |= 1L << (move->rook + 3);
        setBitBoard(board, ROOK, move->white, pieces); // ditto but for the rook
    } else if (move->moveType == SHORT_CASTLE){ // shortcastle
        pieces = getBitBoard(board, KING, move->white);
        pieces &= ~(1L << move->king);
        pieces |= 1L << (move->king + 2);
        setBitBoard(board, KING, move->white, pieces);
        pieces = getBitBoard(board, ROOK, move->white);
        pieces &= ~(1L << move->rook);
        pieces |= 1L << (move->rook - 2);
        setBitBoard(board, ROOK, move->white, pieces);
    }

    if (move->breaksLC){
        if (move->white) game->wO_O_O = false; else game->bO_O_O = false;
    } 
    if (move->breaksSC){
        if (move->white) game->wO_O = false; else game->bO_O = false;
    }
    addMove(game, move);
}

void unMove(Move* move, Game* game){
    Board* board = game->board;
        long pieces = (move->pieceType == NONE)? 0L : getBitBoard(board, move->pieceType, move->white);
        long capturedPieces;
        long promotionPieces = (move->promotionType == NONE)? 0L : getBitBoard(board, move->promotionType, move->white);

        if (move->moveType == MOVE){
            pieces &= ~(1L << move->to);
            pieces |= 1L << move->from;
            setBitBoard(board, move->pieceType, move->white, pieces);
        } else if (move->moveType == CAPTURE){
            capturedPieces = getBitBoard(board, move->captureType, !move->white);
            pieces &= ~(1L << move->to);
            pieces |= 1L << move->from;
            capturedPieces |= 1L << move->captureOn;
            setBitBoard(board, move->pieceType, move->white, pieces);
            setBitBoard(board, move->captureType, !move->white, capturedPieces);
        } else if (move->moveType == PROMOTION){
            pieces |= 1L << move->from;
            promotionPieces &= ~(1L << move->to);
            setBitBoard(board, move->pieceType, move->white, pieces);
            setBitBoard(board, move->promotionType, move->white, promotionPieces);

        } else if (move->moveType == CAPTURE_PROMOTION){
            capturedPieces = getBitBoard(board, move->captureType, !move->white);
            pieces |= 1L << move->from;
            promotionPieces &= ~(1L << move->to);
            capturedPieces |= 1L << move->to;
            setBitBoard(board, move->pieceType, move->white, pieces);
            setBitBoard(board, move->promotionType, move->white, promotionPieces);
            setBitBoard(board, move->captureType, !move->white, capturedPieces);

        } else if (move->moveType == LONG_CASTLE){
            pieces = getBitBoard(board, KING, move->white);
            pieces |= 1L << move->king;
            pieces &= ~(1L << (move->king - 2));
            setBitBoard(board, KING, move->white, pieces);
            pieces = getBitBoard(board, ROOK, move->white);
            pieces |= 1L << move->rook;
            pieces &= ~(1L << (move->rook + 3));
            setBitBoard(board, ROOK, move->white, pieces);
        } else if (move->moveType == SHORT_CASTLE){
            pieces = getBitBoard(board, KING, move->white);
            pieces |= 1L << move->king;
            pieces &= ~(1L << (move->king + 2));
            setBitBoard(board, KING, move->white, pieces);
            pieces = getBitBoard(board, ROOK, move->white);
            pieces |= 1L << move->rook;
            pieces &= ~(1L << (move->rook - 2));
            setBitBoard(board, ROOK, move->white, pieces);
        }
        
        if (move->breaksLC){
            if (move->white) game->wO_O_O = true; else game->bO_O_O = true;
        } 
        if (move->breaksSC){
            if (move->white) game->wO_O = true; else game->bO_O = true;
        }
        removeMove(game, move);
}

ArrayList* getLegalMoves(Game* game){
    ArrayList captures = {NULL, NULL, 0};
    ArrayList checks = {NULL, NULL, 0};
    ArrayList promotions = {NULL, NULL, 0};
    ArrayList otherMoves = {NULL, NULL, 0};
    masterMoves(game, &pseudoLegalMoves);
    pawnMoves(game, &pseudoLegalMoves);
    enPassant(game, &pseudoLegalMoves);

    for (Node* curr = pseudoLegalMoves.first; curr != NULL; curr = curr->next){
        Move move = *curr->move;
        makeMove(&move, game);

        if ((getMoveSquares(game, true) & (getBitBoard(game->board, KING, move.white))) == 0){
            if (move.moveType == CAPTURE) {addToList(&captures, &move);
            } else if ((getMoveSquares(game, false) & getBitBoard(game->board, KING, !move.white)) != 0L) {addToList(&checks, &move);
            } else if (move.moveType == CAPTURE_PROMOTION || move.moveType == PROMOTION) {addToList(&promotions, &move);
            } else { addToList(&otherMoves, &move);
            }

        } else {
            // breakpoint line
        }
         unMove(&move, game);
    }
    castling(game, &actualLegalMoves);
    for (Node* curr = captures.first; curr != NULL; curr = curr->next){
        addToList(&captures, curr->move);
    }
    for (Node* curr = checks.first; curr != NULL; curr = curr->next){
        addToList(&checks, curr->move);
    }
    for (Node* curr = promotions.first; curr != NULL; curr = curr->next){
        addToList(&promotions, curr->move);
    }
    for (Node* curr = otherMoves.first; curr != NULL; curr = curr->next){
        addToList(&otherMoves, curr->move);
    }
    destroy(&captures);
    destroy(&checks);
    destroy(&promotions);
    destroy(&otherMoves);
    destroy(&pseudoLegalMoves);
    return &actualLegalMoves;
}


bool isCheckMate(Game* game, ArrayList* legalMoves){
    if ((getMoveSquares(game, true) & getBitBoard(game->board, KING, game->whiteToMove)) != 0){
        if (legalMoves->first == NULL){
            return true;
        }
    }
    return false;
}

bool isStaleMate(Game* game, ArrayList* legalMoves){
    if ((getMoveSquares(game, true) & getBitBoard(game->board, KING, game->whiteToMove)) == 0){
        if (legalMoves->first == NULL){
            return true;
        }
    }
    return false;
}

bool isInsufficientMaterial(Board* board){
    int blackMaterial = 0;
    int whiteMaterial = 0;
    if ((board->whitePawns | board->blackPawns) != 0) return false;
    for (int i = 0; i <= 1; i++){
        for (PieceType pieceType = PAWN; pieceType < QUEEN; pieceType++){
            uint64_t pieces = getBitBoard(board, pieceType, (i==0)? true : false);
            if (i == 0){
                whiteMaterial += __builtin_popcount(pieces) * getPieceValue(pieceType);
            } else {
                blackMaterial += __builtin_popcount(pieces) * getPieceValue(pieceType);
            }
        }
    }
    if ((whiteMaterial == 0 || whiteMaterial == 3) && (blackMaterial == 0 || blackMaterial == 3)) return true;
    return false;
}

bool isThreefoldRepetition(Game* game){
    // TODO: develop hash table
}
bool gameOver(Game* game){
    if (isCheckMate(game, getLegalMoves(game))){
        printf("Checkmakte! "); printf(game->whiteToMove? "Black wins!" : "White wins!");
        return true;
    }
    if (isStaleMate(game, getLegalMoves(game))){
        printf("Stalemate! Game is a draw.");
        return true;
    }
    if (isInsufficientMaterial(game->board)){
        printf("Insufficient material! Game is a draw.");
        return true;
    }
    if (isThreefoldRepetition(game)){
        printf("Threefold repetition. Game is a draw.");
        return true;
    }
    return false;
}