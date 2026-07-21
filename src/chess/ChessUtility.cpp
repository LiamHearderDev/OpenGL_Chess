#include "ChessUtility.h"


glm::vec3 ChessUtility::board_to_world_position(PiecePositions board_position)
{
    const unsigned int row = board_position / 8;
    const unsigned int col = board_position % 8;

    const float piece_scale = ChessUtility::get_piece_scale();

    const float x = (row - 3.5f) * piece_scale;
    const float y = (col - 3.5f) * piece_scale;

    return glm::vec3(x, y, 0.f);
}

PiecePositions ChessUtility::world_to_board_position(glm::vec3 world_position)
{
    const float piece_scale = ChessUtility::get_piece_scale();

    const unsigned int row = static_cast<unsigned int>(world_position.x / piece_scale + 3.5f);
    const unsigned int col = static_cast<unsigned int>(world_position.y / piece_scale + 3.5f);

    return static_cast<PiecePositions>(row * 8 + col);
}
