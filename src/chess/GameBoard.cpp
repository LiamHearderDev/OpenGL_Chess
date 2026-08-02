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
                // Update the piece's position in the game board
                piece_data->positions[piece_data->dragged_piece_id] = dropped_position;
            }
            piece_data->dragged_piece_id = -1;

            // Broadcast the update to any listeners
            on_update->broadcast(piece_data->name);
            return;
        }
    }
    return;
}
