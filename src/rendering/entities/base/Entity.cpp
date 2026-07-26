#include "Entity.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

void Entity::set_uniform_data()
{
    unsigned int model_mat_loc = glGetUniformLocation(get_shader_program(), "model_mat");
    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, glm::value_ptr(local_transform_component->get_transform()));

    unsigned int cursor_pos_loc = glGetUniformLocation(get_shader_program(), "cursor_pos");
    glUniform2fv(cursor_pos_loc, 1, glm::value_ptr(cursor_position));
}

void Entity::setup_attrib_pointers()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_data), (void*)offsetof(vertex_data, position) );
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_data), (void*)offsetof(vertex_data, texture_coordinate) );
    glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}