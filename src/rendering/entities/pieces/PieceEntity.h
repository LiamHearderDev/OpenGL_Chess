#ifndef PIECE_ENTITY_H
#define PIECE_ENTITY_H

#include <rendering/entities/Entity.h>
#include <chess/ChessEnums.h>
#include <rendering/materials/pieces/PieceMaterial.h>

class PieceEntity : public Entity {
    unsigned int player_team;
    unsigned int piece_id;

    const float piece_scale = 1.f/8.f;

    void init_shader_paths() override;
    void init_material() override;
public:
    // Default constructor
    PieceEntity(renderable_data&& render_data, PieceNames name) : 
        Entity(std::move(render_data))
        {
            player_team = (name < 6) ? 0 : 1;
            piece_id = name % 6;

            set_scale(piece_scale);
            set_board_position(static_cast<PiecePositions>(name));
        };
    
    /** A method of setting a piece's position on the board, using chess notation. */
    void set_board_position(PiecePositions position);

    void setup_attrib_pointers() override;
    void set_uniform_data() override;
};

#endif // PIECE_ENTITY_H