#pragma once

#include <engine/EngineContext.h>

#include <engine/rendering/renderables/derived/instanced/InstancedRenderable.h>
#include <chess/ChessEnums.h>
#include <chess/ChessUtility.h>


class PieceEntity : public InstancedRenderable {
    unsigned int player_team;
    unsigned int piece_id;
    PieceNames name;
    std::vector<PiecePositions> positions{};

    // todo: delete
    float z_rot = 0;

    // References
    EngineContext engine;

public:
    /**
     * The constructor for PieceEntity.
     * @param name The name of the piece, as defined in the PieceNames enum.
     * @param positions A vector of PiecePositions that this type of piece occupies on the board.
    */
    PieceEntity(PieceNames name, std::vector<PiecePositions>&& positions, EngineContext engine) :
        name(name),
        positions(positions),
        engine(engine),
        InstancedRenderable(
            renderable_data{
                std::vector<vertex_data>{
                    vertex_data{{-0.5f, 0.5f, 0.f}, {0.f, 1.0f}    },  // Top-left
                    vertex_data{{0.5f, 0.5f, 0.f},  {1.0f, 1.0f}   },  // Top-right
                    vertex_data{{0.5f, -0.5f, 0.f}, {1.0f, 0.f}    },  // Bottom-right
                    vertex_data{{-0.5f, -0.5f, 0.f},{0.f, 0.f}     },  // Bottom-left
                },
                std::vector<unsigned int>{0,1,3, 1,2,3} 
            }, 
            positions.size() )
        { 
            init_piece();
        };
    
    /** A method of changing a piece's position on the board, using chess notation. */
    void change_board_position(PiecePositions original_position, PiecePositions new_position);

    void update() override;

    void set_uniform_data() override;

    PieceNames get_name() { return name; }

private:
    void init_shader_paths() override;
    void init_material() override;

    void init_piece();

    void on_game_board_updated(PieceNames piece_updated);
};