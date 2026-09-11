#include "GameBoard.h"

#include <cstdio>
#include <chess/ChessUtility.h>
#include <engine/input/InputHandler.h>

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
    for (const auto& piece_data : pieces) {
        for (const PiecePositions& pos : piece_data.positions) {
            if (pos == position) {
                return true;
            }
        }
    }
    return false;
}

void GameBoard::try_pickup_piece_at_location(PiecePositions position)
{
    fprintf(stdout, "trying to pickup piece.\n");
    for (auto& piece_data : pieces) {
        for (int i = 0; i < piece_data.positions.size(); i++) {
            if (piece_data.positions[i] == position) {

                piece_data.dragged_piece_id = i;
                on_update->broadcast(piece_data.name);

                return;
            }
        }
    }
    return;
}

void GameBoard::drop_piece() {
    for (int i = 0; i < pieces.size(); i++) {
        UniquePieceData* piece_data = &pieces[i];

        if (piece_data->dragged_piece_id != -1) {

            // Get cursor position in screen space
            const glm::dvec2 cursor_pos = engine.input_handler->get_cursor_position();

            // Convert to world space
            glm::vec3 world_pos;
            engine.input_handler->screen_to_world_space(cursor_pos, world_pos);
            
            // Convert to board position
            PiecePositions dropped_position;
            bool conversion_result = ChessUtility::world_to_board_position(world_pos, dropped_position);
            if (conversion_result) {

                /** The Plan:
                 * 1. If the start and end points are the same, cancel.
                 * 
                 * 2. Check if this is a valid move based on standard movement rules.
                 * 
                 * 3. Check if any pieces block this move.
                 *      a. Unless the moving piece is a knight, then skip this step.
                 * 
                 * 4. Check if any piece currently occupies the target square.
                 *      a. Check if that piece is an enemy piece. 
                 *          A. Check if this capture is valid, based on capturing rules.
                 *          B. Remove the enemy piece.
                 *          C. TODO: add this piece to the team's "captured pieces" list.
                 * 
                 * 5. Change the current turn.
                */

                // Collect all required data
                const PiecePositions start_pos = piece_data->positions[piece_data->dragged_piece_id];


                // 1. Check if start and end are the same.
                // if (start_pos == dropped_position) {
                //     stop_dragging_piece(piece_data);
                //     return;
                // }

                // // 2. Check if this is a valid move
                if (false == ChessUtility::is_move_legal(ChessUtility::MoveData{piece_data->name, start_pos, dropped_position})) {
                    stop_dragging_piece(piece_data);

                    fprintf(stdout, "Illegal move for ");
                    ChessUtility::print_piece_name(piece_data->name, false);
                    fprintf(stdout, " at position ");
                    ChessUtility::print_position(dropped_position, true);

                    return;
                }

                // // 3. Check if any pieces block this move.
                // if (is_move_obstructed(piece_data->name, start_pos, dropped_position)) {
                //     stop_dragging_piece(piece_data);
                //     return;
                // }

                // Update the piece's position in the game board
                piece_data->positions[piece_data->dragged_piece_id] = dropped_position;
            }
            stop_dragging_piece(piece_data);
            return;
        }
    }
    return;
}

void GameBoard::stop_dragging_piece(UniquePieceData* piece)
{
    piece->dragged_piece_id = -1;
    on_update->broadcast(piece->name);
}

bool GameBoard::is_move_obstructed(ChessUtility::MoveData move_data)
{
    // First, get data about the move itself
    const unsigned int start_row = move_data.start_pos / 8;
    const unsigned int start_col = move_data.start_pos % 8;
    const unsigned int end_row = move_data.end_pos / 8;
    const unsigned int end_col = move_data.end_pos % 8;

    MovementType movement_type;

    switch (move_data.name) {
        case PieceNames::WHITE_ROOK:
        case PieceNames::BLACK_ROOK:
        case PieceNames::BLACK_PAWN:
        case PieceNames::WHITE_PAWN:
        
            // Rooks can move any number of squares along a rank or file
            if (start_row == end_row) { // Same row
                const int min_col = std::min(start_col, end_col);
                const int max_col = std::max(start_col, end_col);

                for (int col = min_col + 1; col < max_col; ++col) {
                    if (is_square_occupied(static_cast<PiecePositions>(start_row + col))) {
                        return true;
                    }
                }
            } else if (start_col == end_col) { // Same column
                const int min_row = std::min(start_row, end_row);
                const int max_row = std::max(start_row, end_row);

                for (int row = min_row + 1; row < max_row; ++row) {
                    if (is_square_occupied(static_cast<PiecePositions>(row * 8 + start_col))) {
                        return true;
                    }
                }
            }
            break;
    }
    return false;
}
