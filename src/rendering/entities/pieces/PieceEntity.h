#ifndef PIECE_ENTITY_H
#define PIECE_ENTITY_H

#include <rendering/entities/Entity.h>
#include <chess/ChessEnums.h>
#include <rendering/materials/pieces/PieceMaterial.h>

#include <set>


class PieceEntity : public InstancedEntity {
    unsigned int player_team;
    unsigned int piece_id;
    std::set<PiecePositions> positions{};

    const float piece_scale = 1.f/8.f;

    void init_shader_paths() override;
    void init_material() override;

public:
    /**
     * The constructor for PieceEntity.
     * @param name The name of the piece, as defined in the PieceNames enum.
     * @param positions A vector of PiecePositions that this type of piece occupies on the board.
    */
    PieceEntity(PieceNames name, std::set<PiecePositions>&& positions) :
        positions(positions),
        InstancedEntity(
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
            player_team = (name < 6) ? 0 : 1; 
            piece_id = name % 6; 

            std::vector<glm::mat4> temp_transforms;
            for (const PiecePositions& pos : positions) {
                glm::vec3 world_pos = board_to_world_position(pos);
                glm::mat4 instance_transform = calc_instance_transform(world_pos, glm::vec3(0.f), glm::vec3(piece_scale));
                temp_transforms.emplace_back(instance_transform);
            }
            set_transforms(std::move(temp_transforms));
        };
    
    /** A method of changing a piece's position on the board, using chess notation. */
    void change_board_position(PiecePositions original_position, PiecePositions new_position);
    
    [[nodiscard]] glm::vec3 board_to_world_position(PiecePositions board_position) const;

    void set_uniform_data() override;
};

#endif // PIECE_ENTITY_H