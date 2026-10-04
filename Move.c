#include "Move.h"
#include "PieceType.h"

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

    return ("%c%c%i %c %c%i %c %c", piece, fileFrom, rankFrom, moveChar, fileTo, rankTo, promotionChar, promotionPiece);
}

bool MoveEquals(Move a, Move b){
    return a.white == b.white &&
           a.from == b.from &&
           a.to == b.to &&
           a.captureOn == b.captureOn &&
           a.moveType == b.moveType &&
           a.pieceType == b.pieceType &&
           a.captureType == b.captureType &&
           a.promotionType == b.promotionType &&
           a.breaksSC == b.breaksSC &&
           a.breaksLC == b.breaksLC;
}