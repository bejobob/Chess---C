#include "Board.h"
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

uint64_t getBitBoard(Board* board, PieceType pieceType, bool white){
    switch(pieceType){
        case PAWN:
            return white? board->whitePawns : board->blackPawns;
        case KNIGHT:
            return white? board->whiteKnights : board->blackKnights;
        case BISHOP:
            return white? board->whiteBishops : board->blackBishops;
        case ROOK:
            return white? board->whiteRooks : board->blackRooks;
        case QUEEN:
            return white? board->whiteQueens : board->blackQueens;
        case KING:
            return white? board->whiteKing : board->blackKing;
        default:
            return 0L;
    }
}

void setBitBoard(Board* board, PieceType pieceType, bool white, long bitBoard){
    switch(pieceType) {
            case PAWN:
                if (white){board->whitePawns = bitBoard;} else {board->blackPawns = bitBoard;}
                break;
            case KNIGHT:
                if (white){board->whiteKnights = bitBoard;} else {board->blackKnights = bitBoard;}
                break;
            case BISHOP:
                if (white){board->whiteBishops = bitBoard;} else {board->blackBishops = bitBoard;}
                break;
            case ROOK:
                if (white){board->whiteRooks = bitBoard;} else {board->blackRooks = bitBoard;}
                break;
            case QUEEN:
                if (white){board->whiteQueens = bitBoard;} else {board->blackQueens = bitBoard;}
                break;
            case KING:
                if (white){board->whiteKing = bitBoard;} else {board->blackKing = bitBoard;}
                break;
            default:
                break;
        }
        board->whitePieces = board->whitePawns | board->whiteKnights | board->whiteBishops | board->whiteRooks | board->whiteQueens | board->whiteKing;
        board->blackPieces = board->blackPawns | board->blackKnights | board->blackBishops | board->blackRooks | board->blackQueens | board->blackKing; // we need to update the collective board at the end, otherwise the two won't match
    }
PieceType getPieceOnSquare(Board* board, int square){
    if (((1L << square) & (board->whitePawns | board->blackPawns)) != 0){ // because the piecetype is independant of the colour, we don't need a separate case for white/black
        return PAWN; // we just and the square with each piecetype until we find the one that isn't 0, that's the type on the square
    } else if (((1L << square) & (board->whiteKnights | board->blackKnights)) != 0) {
        return KNIGHT;
    } else if (((1L << square) & (board->whiteBishops | board->blackBishops)) != 0) {
        return BISHOP;
    } else if (((1L << square) & (board->whiteRooks | board->blackRooks)) != 0) {
        return ROOK;
    } else if (((1L << square) & (board->whiteQueens | board->blackQueens)) != 0) {
        return QUEEN;
    } else if (((1L << square) & (board->whiteKing | board->blackKing)) != 0) {
        return KING;
    } else {
        return NONE; // default case, this will only trigger if the square is empty
    }

}
char* printBoard(Board* board){
    char *toReturn = malloc(256);
    
    if (toReturn == NULL) return NULL;

    int pos = 0;
    pos += snprintf(toReturn + pos, 256 - pos, "  +-----------------+\n");

    for (int rank = 7; rank >= 0; rank--) {
        pos += snprintf(toReturn + pos, 256 - pos, "%d | ", rank + 1);

        for (int file = 0; file < 8; file++) {
            int square = rank * 8 + file;
            uint64_t bit = 1ULL << square;
            char piece = '.';

            // White pieces
            if (board->whitePawns & bit) {
                piece = 'P';
            } else if (board->whiteKnights & bit) {
                piece = 'N';
            } else if (board->whiteBishops & bit) {
                piece = 'B';
            } else if (board->whiteRooks & bit) {
                piece = 'R';
            } else if (board->whiteQueens & bit) {
                piece = 'Q';
            } else if (board->whiteKing & bit) {
                piece = 'K';
            }

            // Black pieces
            else if (board->blackPawns & bit) {
                piece = 'p';
            } else if (board->blackKnights & bit) {
                piece = 'n';
            } else if (board->blackBishops & bit) {
                piece = 'b';
            } else if (board->blackRooks & bit) {
                piece = 'r';
            } else if (board->blackQueens & bit) {
                piece = 'q';
            } else if (board->blackKing & bit) {
                piece = 'k';
            }

            pos += snprintf(toReturn + pos, 256 - pos, "%c ", piece);
        }

        pos += snprintf(toReturn + pos, 256 - pos, "|\n");
    }

    pos += snprintf(toReturn + pos, 256 - pos, "  +-----------------+\n");
    pos += snprintf(toReturn + pos, 256 - pos, "    a b c d e f g h\n");
    return toReturn;
}

char* numToAlgebraic(int square){
    char file = (char) ('a' + square%8);
    int rank = square/8 + 1;
    return ("%c%i", file, rank);
}
bool equals(Board* a, Board* b){
    if (a == b){
            return true;
        }
        if (a == NULL || b == NULL){
            return false;
        }

        return (
            a->whitePawns == b->whitePawns &&
            a->whiteKnights == b->whiteKnights &&
            a->whiteBishops == b->whiteBishops &&
            a->whiteRooks == b->whiteRooks &&
            a->whiteQueens == b->whiteQueens &&
            a->whiteKing == b->whiteKing &&
            a->blackPawns == b->blackPawns &&
            a->blackKnights == b->blackKnights &&
            a->blackBishops == b->blackBishops &&
            a->blackRooks == b->blackRooks &&
            a->blackQueens == b->blackQueens &&
            a->blackKing == b->blackKing
        );
}