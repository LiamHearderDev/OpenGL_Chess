#ifndef PIECE_ENTITY_H
#define PIECE_ENTITY_H

#include <rendering/entities/Entity.h>
#include <chess/ChessEnums.h>
#include <rendering/materials/pieces/PieceMaterial.h>

class PieceEntity : public Entity {
    unsigned int player_team;
    unsigned int piece_id;

    const float piece_scale = 1.f/8.f;
public:
    // Default Constructor
    PieceEntity(renderable_data&& render_data, unsigned int player_team, unsigned int piece_id) :
        Entity(std::move(render_data)),
        player_team(player_team),
        piece_id(piece_id)
        {
            set_scale(piece_scale);
        };
    
    // Alternative constructor
    PieceEntity(renderable_data&& render_data, PieceNames name) : 
        Entity(std::move(render_data))
        {
            player_team = (name < 6) ? 0 : 1;
            piece_id = name % 6;
            set_scale(piece_scale);
            set_board_position(static_cast<PiecePositions>(name));
        };
    
    PieceEntity(PieceNames name) :
        Entity(std::make_unique<renderable_data>(
            std::vector<vertex_data>{
                vertex_data{ {-0.5f, 0.5f, 0.f},      {0.f, 1.0f}    },  // Top-left
                vertex_data{ {0.5f, 0.5f, 0.f},       {1.0f, 1.0f}   },  // Top-right
                vertex_data{ {0.5f, -0.5f, 0.f},      {1.0f, 0.f}    },  // Bottom-right
                vertex_data{ {-0.5f, -0.5f, 0.f},     {0.f, 0.f}     },  // Bottom-left
            },
            std::vector<unsigned int>{0,1,3, 1,2,3},
			std::make_unique<PieceMaterial>(0,0)
        )) {}
        
    
    void set_board_position(PiecePositions position);

    void setup_attrib_pointers() override;
    void set_uniform_data() override;
};

#endif // PIECE_ENTITY_H