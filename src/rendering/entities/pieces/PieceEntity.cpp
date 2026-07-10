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

void PieceEntity::set_board_position(PiecePositions position)
{
    unsigned int row = position / 8;
    unsigned int col = position % 8;

    float x = (row - 3.5f) * piece_scale; 
    float y = (col - 3.5f) * piece_scale;

    set_position({x, y, 0.f});
}

void PieceEntity::render()
{
    // Shader setup
    material->use();
    set_uniform_data();

    // Texture setup
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, get_texture_id());
    unsigned int texture_loc = glGetUniformLocation(get_shader_program(), "screenTexture");
    glUniform1i(texture_loc, 0);

    // Bind the VAO we plan to use
    glBindVertexArray(get_vao());

    // Draw
    glDrawElementsInstanced(GL_TRIANGLES, get_indices_count(), GL_UNSIGNED_INT, nullptr, positions.size());

    // Unbind this entity's VAO, so that we cannot accidentally draw this entity again.
    glBindVertexArray(0);
}

void PieceEntity::setup_attrib_pointers()
{
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_data), (void*)offsetof(vertex_data, position) );
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_data), (void*)offsetof(vertex_data, texture_coordinate) );
    glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

    // Instancing Data
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_data), (void*)offsetof(vertex_data, texture_coordinate) );
}

void PieceEntity::set_uniform_data()
{
    Entity::set_uniform_data();

    constexpr glm::vec2 sprite_scale = {(1.f / 6.f), (1.f / 2.f)};
    const glm::vec2 sprite_offset = {(piece_id * (1.f / 6.f)), ((1-player_team) * (1.f / 2.f))};
    
    unsigned int shader = get_shader_program();

    unsigned int sprite_scale_loc = glGetUniformLocation(shader, "sprite_scale");
    unsigned int sprite_offset_loc = glGetUniformLocation(shader, "sprite_offset");

    glUniform2fv(sprite_scale_loc, 1, glm::value_ptr(sprite_scale));
    glUniform2fv(sprite_offset_loc, 1, glm::value_ptr(sprite_offset));
}
