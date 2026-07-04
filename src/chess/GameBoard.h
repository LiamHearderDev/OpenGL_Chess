#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <cstdint>
#include <array>
#include <chess/ChessEnums.h>

/**
 * A class used for storing the game board, and game state.
 */
class GameBoard {
    std::array<uint64_t, 12> pieces;

    void init();

protected:
    std::array<uint64_t, 12> get_pieces() { return pieces; }    

public:
    GameBoard() { init(); }

    unsigned int get_pieces_count() { return pieces.size(); }
    uint64_t get_piece(PieceNames name) { return pieces[name]; }

    
};


#endif // GAME_BOARD_H