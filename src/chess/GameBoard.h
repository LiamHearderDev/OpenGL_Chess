#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <cstdint>
#include <array>
#include <set>

#include <chess/ChessEnums.h>

/**
 * A structure representing each unique piece type on the board.
 * 
 * At all times, there should be only 12 instances of this 
 * structure as there are 6 unique piece types per team, and 
 * 2 teams make a total of 12.
 */
struct UniquePieceData {
    PieceNames name;
    std::set<PiecePositions> positions;
};

/**
 * A class used for storing the game board, and game state.
 */
class GameBoard {
    std::array<UniquePieceData, 12> pieces;

    void init();
    std::array<UniquePieceData, 12> get_pieces() { return pieces; }

public:
    GameBoard() { init(); }

    unsigned int get_pieces_count() { return pieces.size(); }
    UniquePieceData get_piece_data(PieceNames name) { return pieces.at(name); }

    // The following methods are used to extract data about the board state, such as the positions of pieces, and whether a square is occupied by a piece.
    bool is_square_occupied(PiecePositions position);
};


#endif // GAME_BOARD_H