#include "Move.h"
#include "PieceType.h"
#include "Board.h"
#include <stdlib.h>
#include <stdio.h>

char* printMove(Move* move){
    if (move->moveType == SHORT_CASTLE) return "o-o";
    if (move->moveType == LONG_CASTLE) return "o-o-o";
    int from = move->from;
    int to = move->to;
    int captureOn = move->captureOn;
    PieceType promotionType = move->promotionType;

    char piece = getPieceLetter(move->pieceType, move->white);
    char fileFrom = (char) ('a' + from%8);
    int rankFrom = from/8 + 1;
    char moveChar = captureOn == -1? '-' : 'x';
    char fileTo =  (char) ('a' + (captureOn == -1? to : captureOn)%8);
    int rankTo = (captureOn == -1? to : captureOn) /8 + 1;
    char promotionChar = promotionType == NONE? '\0' : '=';    
    char promotionPiece = promotionType == NONE? '\0' : getPieceLetter(promotionType, move->white);
    char* result = malloc(13);
    snprintf(result, 13, "%c%c%i %c %c%i %c %c", piece, fileFrom, rankFrom, moveChar, fileTo, rankTo, promotionChar, promotionPiece);

    return (result);
}

Move* promotion(int from, int to, bool white, MoveType moveType, Board* board){
    Move* toReturn = malloc(4 * sizeof(Move));
    if (toReturn == NULL) return NULL;
    if (moveType == PROMOTION){
        for (int i = 0; i < 4; i++){
            toReturn[i] = (Move) {white, from, to, -1, PROMOTION, PAWN, NONE, i+2, false, false};
        }
    } else if (moveType == CAPTURE_PROMOTION){
        for (int i = 0; i < 4; i++){
            toReturn[i] = (Move) {white, from, to, to, CAPTURE_PROMOTION, PAWN, getPieceOnSquare(board, to), false, false};
        }
    }
    return toReturn;
}

bool MoveEquals(Move* a, Move* b){
    return a->white == b->white &&
           a->from == b->from &&
           a->to == b->to &&
           a->captureOn == b->captureOn &&
           a->moveType == b->moveType &&
           a->pieceType == b->pieceType &&
           a->captureType == b->captureType &&
           a->promotionType == b->promotionType &&
           a->breaksSC == b->breaksSC &&
           a->breaksLC == b->breaksLC;
}