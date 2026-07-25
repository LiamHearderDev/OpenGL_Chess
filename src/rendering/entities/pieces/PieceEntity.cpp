#include "PieceEntity.h"
#include <glad/glad.h>

#include <rendering/materials/pieces/PieceMaterial.h>
#include <glm/gtc/type_ptr.hpp>
#include <chess/GameBoard.h>
#include <input/InputHandler.h>

void PieceEntity::init_shader_paths()
{
    vert_file_path = "pieces/vert.glsl";
    frag_file_path = "pieces/frag.glsl";
}

void PieceEntity::init_material()
{
    init_shader_paths();
    if (vert_file_path.empty() || frag_file_path.empty()) { return; }

    material = std::make_unique<PieceMaterial>(vert_file_path, frag_file_path);
    material->init();
}

void PieceEntity::init_piece()
{
    // Calculate piece information
    player_team = (name < 6) ? 0 : 1; 
    piece_id = name % 6; 

    // Set instance transforms
    std::vector<glm::mat4> temp_transforms;
    for (const PiecePositions& board_pos : positions) {

        glm::vec3 world_pos{0.f};
        ChessUtility::board_to_world_position(board_pos, world_pos);

        glm::mat4 instance_transform = calc_instance_transform(world_pos, glm::vec3(0.f), glm::vec3(ChessUtility::get_piece_scale()));
        temp_transforms.emplace_back(instance_transform);
    }
    set_transforms(std::move(temp_transforms));

    // Bind to delegates
    game_board->on_update->add(this, &update);
}

void PieceEntity::change_board_position(PiecePositions original_position, PiecePositions new_position)
{
    for (int i = 0; i < positions.size(); i++){
        if (positions[i] == original_position) {
            positions[i] = new_position;
            return;
        }
    }
}

void PieceEntity::update()
{
    const UniquePieceData data = game_board->get_piece_data(name);

    positions = std::move(data.positions);

    std::vector<glm::mat4> temp_transforms;
    for (int i = 0; i < positions.size(); i++) {
        const PiecePositions& piece_pos = positions[i];
        
        glm::vec3 world_pos = glm::vec3(0.f, 0.f, 0.f);

        // If this instance is being dragged, the instance transform's location must be the cursor.
        if (i == data.dragged_piece_id) {
            input_handler->screen_to_world_space(input_handler->get_cursor_position(), world_pos);
        } else {
            ChessUtility::board_to_world_position(piece_pos, world_pos);
        }
        if (data.dragged_piece_id >= 0) {
            //fprintf(stdout, "dragged id = %d...\n", data.dragged_piece_id);
        }

        glm::mat4 instance_transform = calc_instance_transform(world_pos, glm::vec3(0.f), glm::vec3(ChessUtility::get_piece_scale()));
        temp_transforms.emplace_back(instance_transform);
    }
    set_transforms(std::move(temp_transforms));
}

void PieceEntity::set_uniform_data()
{
    InstancedEntity::set_uniform_data();

    constexpr glm::vec2 sprite_scale = {(1.f / 6.f), (1.f / 2.f)};
    const glm::vec2 sprite_offset = {(piece_id * (1.f / 6.f)), ((1-player_team) * (1.f / 2.f))};
    
    unsigned int shader = get_shader_program();

    unsigned int sprite_scale_loc = glGetUniformLocation(shader, "sprite_scale");
    unsigned int sprite_offset_loc = glGetUniformLocation(shader, "sprite_offset");

    glUniform2fv(sprite_scale_loc, 1, glm::value_ptr(sprite_scale));
    glUniform2fv(sprite_offset_loc, 1, glm::value_ptr(sprite_offset));
}
