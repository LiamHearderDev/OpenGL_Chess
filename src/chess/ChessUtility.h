#ifndef CHESS_UTILITY_H
#define CHESS_UTILITY_H

#include <chess/ChessEnums.h>
#include <glm/glm.hpp>

class ChessUtility {
public:

    /* Used to scale the size of each piece. */
    [[nodiscard]] static constexpr float get_piece_scale() { return 1.f/8.f; }

    // Conversions
    [[nodiscard]] static glm::vec3 board_to_world_position(PiecePositions board_position);
    [[nodiscard]] static PiecePositions world_to_board_position(glm::vec3 world_position);
};


#endif // CHESS_UTILITY_H