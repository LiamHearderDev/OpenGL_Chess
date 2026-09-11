#include "ChessUtility.h"


void ChessUtility::board_to_world_position(PiecePositions board_position, glm::vec3& world_position)
{
    const unsigned int row = board_position / 8;
    const unsigned int col = board_position % 8;

    const float piece_scale = ChessUtility::get_piece_scale();

    const float x = (col - 3.5f) * piece_scale;
    const float y = ((7 - row) - 3.5f) * piece_scale;

    world_position = glm::vec3(x, y, 0.f);
}

bool ChessUtility::world_to_board_position(glm::vec3 world_position, PiecePositions& board_pos)
{
    const float piece_scale = ChessUtility::get_piece_scale();

    if (world_position.x < -0.5 || world_position.x > 0.5) { return false; }
    if (world_position.y < -0.5 || world_position.y > 0.5) { return false; }
    
    const unsigned int col = static_cast<unsigned int>(world_position.x / piece_scale + 4.f);
    const unsigned int row = static_cast<unsigned int>(-(world_position.y) / piece_scale + 4.f);

    if (row < 8 && col < 8)
    {
        board_pos = static_cast<PiecePositions>(row * 8 + col);
        return true;
    }
    
    return false;
}

bool ChessUtility::is_move_legal(MoveData move_data)
{
    const unsigned int start_row = move_data.start_pos / 8;
    const unsigned int start_col = move_data.start_pos % 8;
    const unsigned int end_row = move_data.end_pos / 8;
    const unsigned int end_col = move_data.end_pos % 8;

    const int row_diff = static_cast<int>(end_row) - static_cast<int>(start_row);
    const int col_diff = static_cast<int>(end_col) - static_cast<int>(start_col);

    switch (move_data.name) {
        case PieceNames::WHITE_PAWN:
            if (col_diff == 0 && row_diff == -1) {
                return true;
            }
            if (col_diff == 0 && row_diff == -2 && start_row == 6) {
                return true;
            }
            break;
        case PieceNames::BLACK_PAWN:
            // Pawns can move forward one square, or two squares from their starting position
            if (col_diff == 0 && row_diff == 1) {
                return true;
            }
            if (col_diff == 0 && row_diff == 2 && start_row == 1) {
                return true;
            }
            break;
        case PieceNames::WHITE_ROOK:
        case PieceNames::BLACK_ROOK:
            // Rooks can move any number of squares along a rank or file
            if (row_diff == 0 || col_diff == 0) {
                return true;
            }
            break;
        case PieceNames::WHITE_KNIGHT:
        case PieceNames::BLACK_KNIGHT:
            // Knights move in an L-shape: two squares in one direction and then one square perpendicular
            if ((abs(row_diff) == 2 && abs(col_diff) == 1) || (abs(row_diff) == 1 && abs(col_diff) == 2)) {
                return true;
            }
            break;
        case PieceNames::WHITE_BISHOP:
        case PieceNames::BLACK_BISHOP:
            // Bishops move diagonally any number of squares
            if (abs(row_diff) == abs(col_diff)) {
                return true;
            }
            break;
        case PieceNames::WHITE_QUEEN:
        case PieceNames::BLACK_QUEEN:
            // Queens move any number of squares along a rank, file, or diagonal
            if (row_diff == 0 || col_diff == 0 || abs(row_diff) == abs(col_diff)) {
                return true;
            }
            break;
        case PieceNames::WHITE_KING:
        case PieceNames::BLACK_KING:
            // Kings move one square in any direction
            if (abs(row_diff) <= 1 && abs(col_diff) <= 1) {
                return true;
            }
            break;
        default:    // No piece selected, so not legal
            return false;
    }
    return false;
}

bool ChessUtility::is_capture_legal(CaptureData capture_data, MoveData move_data)
{
    // If same team, capture is obviously illegal
    if (get_team(capture_data.attacking_piece) == get_team(capture_data.defending_piece)){
        return false;
    }

    // Get data about the move
    const unsigned int start_row = move_data.start_pos / 8;
    const unsigned int start_col = move_data.start_pos % 8;
    const unsigned int end_row = move_data.end_pos / 8;
    const unsigned int end_col = move_data.end_pos % 8;
    const int row_diff = static_cast<int>(end_row) - static_cast<int>(start_row);
    const int col_diff = static_cast<int>(end_col) - static_cast<int>(start_col);

    // Check if the attacking piece is a WHITE pawn
    if (capture_data.attacking_piece == PieceNames::WHITE_PAWN){
        // They can only attack up, diagonally, by 1 square.
        if (row_diff != -1 || abs(row_diff) != abs(col_diff)) {
            return false;
        }
    }

    // Check if the attacking piece is a BLACK pawn
    if (capture_data.attacking_piece == PieceNames::BLACK_PAWN){
        // They can only attack down, diagonally, and by 1 square.
        if (row_diff != 1 || abs(row_diff) != abs(col_diff)) {
            return false;
        }
    }
    
    // Else the capture is legal
    // This is because all other legal chess moves, are also legal captures.
    // Therefore, you must always check if the move is legal first.

    return true;
}

ChessTeam ChessUtility::get_team(PieceNames piece)
{
    return static_cast<ChessTeam>(piece / 6);
}

bool ChessUtility::move_data_to_movement_type(MoveData move_data, MovementType& movement_type)
{
    // Rows = Ranks = Numbers
    // Cols = Files = Letters
    const unsigned int start_row = move_data.start_pos / 8;
    const unsigned int start_col = move_data.start_pos % 8;
    const unsigned int end_row = move_data.end_pos / 8;
    const unsigned int end_col = move_data.end_pos % 8;

    const int row_diff = static_cast<int>(end_row) - static_cast<int>(start_row);
    const int col_diff = static_cast<int>(end_col) - static_cast<int>(start_col);

    // Check if the piece moved at all
    if (move_data.start_pos == move_data.end_pos) { 
        return false; 
    }

    // Horizontal Movement
    if (start_row == end_row) {
        movement_type = MovementType::HORIZONTAL;
        return true;
    }
    
    // Vertical Movement
    if (start_col == end_col) {
        movement_type = MovementType::VERTICAL;
        return true;
    }

    // Diagonal Movement
    if (abs(row_diff) == abs(col_diff)) {
        movement_type = MovementType::DIAGONAL;
        return true;
    }

    // L-Shaped Movement
    if ((abs(row_diff) == 2 && abs(col_diff) == 1) || (abs(row_diff) == 1 && abs(col_diff) == 2)) {
        movement_type = MovementType::L_SHAPED;
        return true;
    }

    return false;
}

void ChessUtility::position_to_string(PiecePositions position, std::string &output)
{
    const char file = static_cast<char>('A' + (position / 8));
    const char rank = static_cast<char>('1' + (position % 8));
    output.push_back(file);
    output.push_back(rank);
}

void ChessUtility::print_position(PiecePositions position, bool new_line)
{
    const char file = static_cast<char>('A' + (position / 8));
    const char rank = static_cast<char>('1' + (position % 8));
    fprintf(stdout, "%c%c", file, rank);
    if (new_line) {
        fprintf(stdout, "\n");
    }
}

void ChessUtility::print_piece_name(PieceNames name, bool new_line)
{
    const char* name_str = nullptr;
    switch (name) {
        case PieceNames::WHITE_PAWN:    name_str = "White Pawn";    break;
        case PieceNames::WHITE_ROOK:    name_str = "White Rook";    break;
        case PieceNames::WHITE_KNIGHT:  name_str = "White Knight";  break;
        case PieceNames::WHITE_BISHOP:  name_str = "White Bishop";  break;
        case PieceNames::WHITE_QUEEN:   name_str = "White Queen";   break;
        case PieceNames::WHITE_KING:    name_str = "White King";    break;
        case PieceNames::BLACK_PAWN:    name_str = "Black Pawn";    break;
        case PieceNames::BLACK_ROOK:    name_str = "Black Rook";    break;
        case PieceNames::BLACK_KNIGHT:  name_str = "Black Knight";  break;
        case PieceNames::BLACK_BISHOP:  name_str = "Black Bishop";  break;
        case PieceNames::BLACK_QUEEN:   name_str = "Black Queen";   break;
        case PieceNames::BLACK_KING:    name_str = "Black King";    break;
    }
    if (name_str) {
        fprintf(stdout, "%s", name_str);
    } else {
        fprintf(stdout, "Unknown Piece");
    }

    if (new_line) {
        fprintf(stdout, "\n");
    }
}
