#ifndef CHESS_UTILITY_H
#define CHESS_UTILITY_H

#include <chess/ChessEnums.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

class ChessUtility {
public:

    /* Used to scale the size of each piece. */
    [[nodiscard]] static constexpr float get_piece_scale() { return 1.f/8.f; }

    /**
     * Converts a board position to a world position.
     * @param board_position The board position to convert.
     * @param world_position A reference to a glm::vec3 object that will be set to the converted world position.
     */
    static void board_to_world_position(PiecePositions board_position, glm::vec3& world_position);

    /**
     * Converts a world position to a board position.
     * @param world_position The world position to convert.
     * @param board_pos A reference to a PiecePositions object that will be set to the converted board position if the conversion was successful.
     * @return true if the conversion was successful, or false if the world position is out of bounds.
     */
    [[nodiscard]] static bool world_to_board_position(glm::vec3 world_position, PiecePositions& board_pos);

    static void position_to_string(PiecePositions position, std::string& output);
    // TODO: make this just straight up print the position
};


#endif // CHESS_UTILITY_H