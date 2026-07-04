#include "GameBoard.h"

void GameBoard::init()
{
    pieces.fill(0);

    // The following sets every piece to its starting position on the board. 
    // The board is represented as a 64-bit integer, where each bit corresponds to a square on the chessboard. 
    // A bit set to 1 indicates that a piece of that type is present on that square.
    pieces[PieceNames::WHITE_PAWN] = 0x000000000000FF00;
    pieces[PieceNames::WHITE_KNIGHT] = 0x0000000000000042;
    pieces[PieceNames::WHITE_BISHOP] = 0x0000000000000024;
    pieces[PieceNames::WHITE_ROOK] = 0x0000000000000081;
    pieces[PieceNames::WHITE_QUEEN] = 0x0000000000000008;
    pieces[PieceNames::WHITE_KING] = 0x0000000000000010;

    pieces[PieceNames::BLACK_PAWN] = 0x00FF000000000000;
    pieces[PieceNames::BLACK_KNIGHT] = 0x4200000000000000;
    pieces[PieceNames::BLACK_BISHOP] = 0x2400000000000000;
    pieces[PieceNames::BLACK_ROOK] = 0x8100000000000000;
    pieces[PieceNames::BLACK_QUEEN] = 0x0800000000000000;
    pieces[PieceNames::BLACK_KING] = 0x1000000000000000;
}

bool GameBoard::is_square_occupied(PiecePositions position)
{
    unsigned int row = position / 8;
    unsigned int col = position % 8;

    uint64_t mask = 1ULL << (row * 8 + col);

    for (const auto& piece : pieces) {
        if (piece & mask) {
            return true; // Square is occupied
        }
    }
    return false; // Square is not occupied
}
