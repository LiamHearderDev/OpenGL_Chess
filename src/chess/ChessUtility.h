#ifndef CHESS_UTILITY_H
#define CHESS_UTILITY_H

#include <chess/ChessEnums.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>



/**
 * A static utility class for chess-related operations, such as converting between board and world positions, printing piece names, and more.
 */
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

    /**
     * Checks if a move is a legal depending on standard movement rules. 
     * Does NOT consider obstruction or current turn.
     * @param piece The name of the piece we are moving.
     * @param start The starting board position.
     * @param end The ending board position.
     * @return true if the move is a valid legal
     */
    static bool is_move_legal(PieceNames piece, PiecePositions start, PiecePositions end);

    /**
     * Converts a board position to a string representation.
     * @param position The board position to convert.
     * @param output A reference to a std::string object that will be set to the converted string.
     */
    static void position_to_string(PiecePositions position, std::string& output);

    /**
     * Prints the string representation of a board position.
     * @param position The board position to print.
     * @param new_line Whether to print a newline character after the position.
     */
    static void print_position(PiecePositions position, bool new_line = false);

    /**
     * Prints the name of a chess piece.
     * @param name The name of the piece, as defined in the PieceNames enum.
     * @param new_line Whether to print a newline character after the name.
     */
    static void print_piece_name(PieceNames name, bool new_line = false);
};


#endif // CHESS_UTILITY_H