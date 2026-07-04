#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <cstdint>
#include <array>

/**
 * A class used for storing the game board, and game state.
 */
class GameBoard {
    
    
    std::array<uint64_t, 12> pieces;
    
public:
    GameBoard() = default;
    std::array<uint64_t, 12> getPieces();
};

#endif // GAME_BOARD_H