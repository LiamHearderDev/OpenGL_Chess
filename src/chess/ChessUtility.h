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

    // ====== STRUCTURES ====== //

    /**
     * MoveData structure is used to store information about a chess move, including 
     * the piece being moved and its starting and ending positions.
     */
    struct MoveData {
        PieceNames name;
        PiecePositions start_pos;
        PiecePositions end_pos;
    };


    struct CaptureData {
        ChessTeam attacking_team;
        ChessTeam defending_team;
        PieceNames attacking_piece;
        PieceNames defending_piece;
        PiecePositions start_pos;
        PiecePositions end_pos;
    };


    // ====== FUNCTIONS ====== //

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
     * @param move_data Data about the requested move.
     * @return true if the move is a valid, legal move
     */
    static bool is_move_legal(MoveData move_data);

    /**
     * Checks if a capture is legal based on the attacking and defending pieces, as well as the move data.
     * @param attacking_piece The piece that is attempting to capture.
     * @param defending_piece The piece that is being captured.
     * @param move_data Data about the requested move.
     * @return true if the capture is legal, false otherwise.
     */
    static bool is_capture_legal(CaptureData capture_data, MoveData move_data);

    /**
     * Returns the team of a given chess piece.
     * @param piece The chess piece, as defined in the PieceNames enum.
     * @return The team to which the piece belongs, as defined in the ChessTeam enum.
     */
    static ChessTeam get_team(PieceNames piece);

    /**
     * Returns the correct MovementType based on the provided MoveData structure.
     * @param move_data Data about a chess move.
     * @param movement_type A reference to a MovementType variable that will be set to the corresponding 
     *      movement type if the conversion is successful.
     * @return True if the move_data corresponds to a valid MovementType, false otherwise.
     */
    [[nodiscard]] static bool move_data_to_movement_type(MoveData move_data, MovementType& movement_type);

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