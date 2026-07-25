#include "ChessUtility.h"


void ChessUtility::board_to_world_position(PiecePositions board_position, glm::vec3& world_position)
{
    const unsigned int row = board_position / 8;
    const unsigned int col = board_position % 8;

    const float piece_scale = ChessUtility::get_piece_scale();

    const float x = (row - 3.5f) * piece_scale;
    const float y = (col - 3.5f) * piece_scale;

    world_position = glm::vec3(x, y, 0.f);
}

bool ChessUtility::world_to_board_position(glm::vec3 world_position, PiecePositions& board_pos)
{
    const float piece_scale = ChessUtility::get_piece_scale();

    if (world_position.x < -0.5 || world_position.x > 0.5) { return false; }
    if (world_position.y < -0.5 || world_position.y > 0.5) { return false; }
    
    const unsigned int row = static_cast<unsigned int>(world_position.x / piece_scale + 4.f);
    const unsigned int col = static_cast<unsigned int>(world_position.y / piece_scale + 4.f);

    if (row < 8 && col < 8)
    {
        board_pos = static_cast<PiecePositions>(row * 8 + col);
        return true;
    }
    
    return false;
}
