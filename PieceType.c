#include "PieceType.h"

int getPieceValue(PieceType pieceType){
    switch (pieceType){
        case PAWN:
            return 1;
        case KNIGHT:
            return 3;
        case BISHOP:
            return 3;
        case ROOK:
            return 5;
        case QUEEN:
            return 9;
        case KING:
            return 0;
        default:
            return -1;
    };
}

char getPieceLetter(PieceType pieceType, bool white){
    switch (pieceType){
        case PAWN:
            return white? 'P' : 'p';
        case KNIGHT:
            return white? 'N' : 'n';
        case BISHOP:
            return white? 'B' : 'b';
        case ROOK:
            return white? 'R' : 'r';
        case QUEEN:
            return white? 'Q' : 'q';
        case KING:
            return white? 'K' : 'k';
        default:
            return 'e';
    };
}