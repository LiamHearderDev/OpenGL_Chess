#include "PieceEntity.h"
#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

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

void PieceEntity::change_board_position(PiecePositions original_position, PiecePositions new_position)
{
    for (int i = 0; i < positions.size(); i++){
        if (positions[i] == original_position) {
            positions[i] = new_position;
            return;
        }
    }
}

glm::vec3 PieceEntity::board_to_world_position(PiecePositions board_position) const
{
    const unsigned int row = board_position / 8;
    const unsigned int col = board_position % 8;

    const float x = (row - 3.5f) * piece_scale;
    const float y = (col - 3.5f) * piece_scale;

    return glm::vec3(x, y, 0.f);
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
