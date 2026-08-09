#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <cstdint>
#include <array>
#include <set>
#include <vector>

#include <chess/ChessEnums.h>
#include <engine/EngineContext.h>

#include "delegates/MulticastDelegate.h"

/**
 * A structure representing each unique piece type on the board.
 * 
 * At all times, there should be only 12 instances of this 
 * structure as there are 6 unique piece types per team, and 
 * 2 teams make a total of 12.
 */
struct UniquePieceData {
    PieceNames name;
    std::vector<PiecePositions> positions;
    int dragged_piece_id = -1;
};

/**
 * A class used for storing the game board, and game state.
 */
class GameBoard {
    EngineContext engine;
    std::array<UniquePieceData, 12> pieces;

public:
    GameBoard() {}
    ~GameBoard() {}

    /** A delegate that is triggered when the game board is updated. */
    DECLARE_MULTICAST_DELEGATE(on_update, PieceNames /* piece_updated */);

    void init();

    unsigned int get_pieces_count() { return pieces.size(); }
    UniquePieceData get_piece_data(PieceNames name) { return pieces.at(name); }

    /** Registers the engine context with the game board. */
    void register_engine_context(EngineContext engine_context) { engine = engine_context; }

    /** 
     * Checks if a square on the board is occupied.
     * @param position The position to check.
     * @return true if the square is occupied, false otherwise.
     */
    bool is_square_occupied(PiecePositions position);

    /** 
     * Attempts to pick up a piece at the specified location.
     * @param location The location of the piece to pick up.
    */
    void try_pickup_piece_at_location(PiecePositions location);

    /** 
     * Attempts to drop any picked up piece.
    */
    void drop_piece();

private:
    /**
     * Executes the code to stop dragging a specific piece.
     */
    void stop_dragging_piece(UniquePieceData* piece);

    /**
     * Checks if the given move is obstructed by any other piece.
     * @param piece The name of the piece we are moving.
     * @param start The starting point of the move.
     * @param end The ending point of the move.
     * @return true if the move is obstructed.
     */
    bool is_moved_obstructed(PieceNames piece, PiecePositions start, PiecePositions end);
};


#endif // GAME_BOARD_H