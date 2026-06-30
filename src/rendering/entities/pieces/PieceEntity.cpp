#include "PieceEntity.h"
#include <glad/glad.h>

void PieceEntity::setup_attrib_pointers()
{
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_data), (void*)offsetof(piece_vertex_data, position) );
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_data), (void*)offsetof(piece_vertex_data, texture_coordinate) );
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_data), (void*)offsetof(piece_vertex_data, player_team) );
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_data), (void*)offsetof(piece_vertex_data, piece_id) );
    glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
}