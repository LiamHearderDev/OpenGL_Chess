#include "PieceEntity.h"
#include <glad/glad.h>

#include <engine/rendering/materials/pieces/PieceMaterial.h>
#include <glm/gtc/type_ptr.hpp>

#include <engine/gamestate/GameState.h>
#include <engine/input/InputHandler.h>
#include <engine/window/WindowManager.h>

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

    // Bind to delegates
    engine.game_state->game_board->on_update->add(this, &PieceEntity::on_game_board_updated);

    // TODO: delete this
    fprintf(stdout, "Initialising piece: ");
    ChessUtility::print_piece_name(name, true);

    update();
}

void PieceEntity::on_game_board_updated(PieceNames piece_updated)
{
    if (piece_updated == name) {
        update();
    }
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
    const UniquePieceData data = engine.game_state->game_board->get_piece_data(name);

    // Update the positions vector with the new positions from the game board
    positions.clear();
    for (int i = 0; i < data.positions.size(); i++) {
        positions.emplace_back(data.positions[i]);
    }

    // Update the instance transforms for each piece position
    std::vector<glm::mat4> temp_transforms{};
    for (int i = 0; i < positions.size(); i++) {
        const PiecePositions& piece_pos = positions[i];
        
        glm::vec3 world_pos = glm::vec3(0.f, 0.f, 0.f);

        // If this instance is being dragged, the instance transform's location must be the cursor.
        if (i == data.dragged_piece_id) {
            engine.input_handler->screen_to_world_space(engine.input_handler->get_cursor_position(), world_pos);
        } else {
            ChessUtility::board_to_world_position(piece_pos, world_pos);
        }

        glm::mat4 instance_transform = instanced_transform_component->calc_instance_transform(
            world_pos, glm::vec3(0.f, 0.f, 0.f), glm::vec3(ChessUtility::get_piece_scale())
        );
        temp_transforms.emplace_back(instance_transform);
    }
    instanced_transform_component->set_transforms(temp_transforms, true);
}

void PieceEntity::set_uniform_data()
{
    InstancedRenderable::set_uniform_data();

    constexpr glm::vec2 sprite_scale = {(1.f / 6.f), (1.f / 2.f)};
    const glm::vec2 sprite_offset = {(piece_id * (1.f / 6.f)), ((1-player_team) * (1.f / 2.f))};
    
    unsigned int shader = get_shader_program();

    unsigned int sprite_scale_loc = glGetUniformLocation(shader, "sprite_scale");
    unsigned int sprite_offset_loc = glGetUniformLocation(shader, "sprite_offset");

    glUniform2fv(sprite_scale_loc, 1, glm::value_ptr(sprite_scale));
    glUniform2fv(sprite_offset_loc, 1, glm::value_ptr(sprite_offset));
}
