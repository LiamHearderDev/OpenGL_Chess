#include "GameBoard.h"

void GameBoard::init()
{
    pieces.fill(UniquePieceData{});
    for (int i = 0; i < 12; i++){
        pieces[i].name = static_cast<PieceNames>(i);
    }

    pieces[WHITE_PAWN].positions = {A2, B2, C2, D2, E2, F2, G2, H2};
    pieces[WHITE_KNIGHT].positions = {B1, G1};
    pieces[WHITE_BISHOP].positions = {C1, F1};
    pieces[WHITE_ROOK].positions = {A1, H1};
    pieces[WHITE_QUEEN].positions = {D1};
    pieces[WHITE_KING].positions = {E1};

    pieces[BLACK_PAWN].positions = {A7, B7, C7, D7, E7, F7, G7, H7};
    pieces[BLACK_KNIGHT].positions = {B8, G8};
    pieces[BLACK_BISHOP].positions = {C8, F8};
    pieces[BLACK_ROOK].positions = {A8, H8};
    pieces[BLACK_QUEEN].positions = {D8};
    pieces[BLACK_KING].positions = {E8};
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
