#include "PieceEntity.h"
#include <glad/glad.h>

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

    unsigned int shader = get_shader_program();

    unsigned int player_team_loc = glGetUniformLocation(shader, "team");
    unsigned int piece_id_loc = glGetUniformLocation(shader, "piece_id");
    
    glUniform1ui(player_team_loc, player_team);
    glUniform1ui(piece_id_loc, piece_id);
}
