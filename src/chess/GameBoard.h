#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <cstdint>
#include <array>

/**
 * A class used for storing the game board, and game state.
 */
class GameBoard {
    
    enum Pieces {
        WHITE_PAWN, WHITE_KNIGHT, WHITE_BISHOP, WHITE_ROOK, WHITE_QUEEN, WHITE_KING,
        BLACK_PAWN, BLACK_KNIGHT, BLACK_BISHOP, BLACK_ROOK, BLACK_QUEEN, BLACK_KING
    };
    std::array<uint64_t, 12> pieces;
    
public:
    GameBoard() = default;
    std::array<uint64_t, 12> getPieces();
};

#endif // GAME_BOARD_H