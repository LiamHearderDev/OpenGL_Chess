#include "PieceEntity.h"
#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

void PieceEntity::setup_attrib_pointers()
{
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_data), (void*)offsetof(vertex_data, position) );
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_data), (void*)offsetof(vertex_data, texture_coordinate) );
    glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

void PieceEntity::set_uniform_data()
{
    Entity::set_uniform_data();

    constexpr glm::vec2 sprite_scale = {(1.f / 6.f), (1.f / 2.f)};
    const glm::vec2 sprite_offset = {(piece_id * (1.f / 6.f)), (player_team * (1.f / 2.f))};
    
    unsigned int shader = get_shader_program();

    unsigned int sprite_scale_loc = glGetUniformLocation(shader, "sprite_scale");
    unsigned int sprite_offset_loc = glGetUniformLocation(shader, "sprite_offset");

    glUniform2fv(sprite_scale_loc, 1, glm::value_ptr(sprite_scale));
    glUniform2fv(sprite_offset_loc, 1, glm::value_ptr(sprite_offset));
}
