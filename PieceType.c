#include "PieceType.h"
#include <stdlib.h>

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

int getItter(PieceType pieceType){
    if (pieceType == KNIGHT || pieceType == KING){
        return 1;
    } else {
        return 7;
    }
}


int* getOffsets(PieceType pieceType){
    int* arr;
    switch (pieceType){
        case KNIGHT:
            arr = malloc(8 * sizeof(int));
            if (arr == NULL) return NULL;
            arr[0] = 17; arr[1] = 10; arr[2] = -6; arr[3] = -15; arr[4] = -17; arr[5] = -10; arr[6] = 6; arr[7] = 15;
            break;
        case BISHOP:
            arr = malloc(4*sizeof(int));
            arr[0] = 9; arr[1] = 7; arr[2] = -7; arr[3] = -9;
            break;
        case ROOK:
            arr = malloc(4*sizeof(int));
            arr[0] = 8; arr[1] = 1; arr[2] = -1; arr[3] = -8;
            break;
        case QUEEN || KING:
            arr = malloc(8*sizeof(int));
            arr[0] = 8; arr[1] = 1; arr[2] = -1; arr[3] = -8; arr[4] = -9; arr[5] = -7; arr[6] = -7; arr[7] = -9;
        default:
            break;
    }
    return arr;
}