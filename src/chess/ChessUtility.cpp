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
        case PieceNames::WHITE_PAWN: name_str = "White Pawn"; break;
        case PieceNames::WHITE_ROOK: name_str = "White Rook"; break;
        case PieceNames::WHITE_KNIGHT: name_str = "White Knight"; break;
        case PieceNames::WHITE_BISHOP: name_str = "White Bishop"; break;
        case PieceNames::WHITE_QUEEN: name_str = "White Queen"; break;
        case PieceNames::WHITE_KING: name_str = "White King"; break;
        case PieceNames::BLACK_PAWN: name_str = "Black Pawn"; break;
        case PieceNames::BLACK_ROOK: name_str = "Black Rook"; break;
        case PieceNames::BLACK_KNIGHT: name_str = "Black Knight"; break;
        case PieceNames::BLACK_BISHOP: name_str = "Black Bishop"; break;
        case PieceNames::BLACK_QUEEN: name_str = "Black Queen"; break;
        case PieceNames::BLACK_KING: name_str = "Black King"; break;
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
