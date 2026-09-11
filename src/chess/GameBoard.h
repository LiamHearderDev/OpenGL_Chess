#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <cstdint>
#include <array>
#include <set>
#include <vector>

#include <chess/ChessEnums.h>
#include <chess/ChessUtility.h>
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

    /** 
     * Gets the number of unique pieces on the board.
     * @return The number of unique pieces on the board.
     */
    unsigned int get_pieces_count() { return pieces.size(); }

    /**
     * Gets a copy of the UniquePieceData structure for the specified piece name.
     * @param name The name of the piece to get data for.
     * @return A copy of the UniquePieceData structure for the specified piece name.
     */
    UniquePieceData get_piece_data(PieceNames name) { return pieces.at(name); }

    /**
     * Gets a reference to the UniquePieceData structure for the specified piece name.
     * @param name The name of the piece to get data for.
     * @return A reference to the UniquePieceData structure for the specified piece name.
     */
    UniquePieceData& get_piece_data_ref(PieceNames name) { return pieces.at(name); }

    /** 
     * Registers the engine context with the game board. 
     * @param engine_context The engine context to register.
     */
    void register_engine_context(EngineContext engine_context) { engine = engine_context; }

    /** 
     * Checks if a square on the board is occupied.
     * @param position The position to check.
     * @return true if the square is occupied, false otherwise.
     */
    bool is_square_occupied(PiecePositions position);
    
    /** 
     * Checks if a square on the board is occupied.
     * @param row Integer matching the row number for the position.
     * @param column Integer matching the column number for the position.
     * @return true if the square is occupied, false otherwise.
     */
    bool is_square_occupied(int row, int column);

    /**
     * Attempts to get the piece at the specified position.
     * @param pos The position to check.
     * @param piece_data A reference to a UniquePieceData structure that will be set to the found piece's data if a piece is found at the position.
     * @return true if a piece was found at the position, false otherwise.
     */
    [[nodiscard]] bool get_piece_at_position(const PiecePositions pos, UniquePieceData& piece_data);

    /**
     * Attempts to get the piece at the specified row and column.
     * @param row Integer matching the row number for the position.
     * @param column Integer matching the column number for the position.
     * @param piece_data A reference to a UniquePieceData structure that will be set to the found piece's data if a piece is found at the position.
     * @return true if a piece was found at the position, false otherwise.
     */
    [[nodiscard]] bool get_piece_at_position(const int row, const int column, UniquePieceData& piece_data);

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
     * This is different to checking if a piece exists on the ending
     * position, such as when attacking a piece. This function only
     * checks the squares between two positions.
     * @param piece The name of the piece we are moving.
     * @param start The starting point of the move.
     * @param end The ending point of the move.
     * @return true if the move is obstructed.
     */
    bool is_move_obstructed(ChessUtility::MoveData move_data);

    /**
     * Captures a chess piece, removes it from the board, and updates the game state accordingly.
     * Does NOT check if the capture is legal, that should be done before calling this function.
     * Also does not move the attacking piece to the defending piece's position, that should be done after calling this function.
     * @param capture_data A structure containing information about the capture, including the attacking and defending pieces, their teams, and their positions.
     */
    void capture_piece(ChessUtility::CaptureData capture_data);
};


#endif // GAME_BOARD_H