#include "Entity.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

glm::mat4 LocalTransformComponent::calc_model_matrix() const
{
    glm::mat4 model{1.f};
    model = glm::translate(model, position);
    model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, scale);
    return model;
}

void LocalTransformComponent::set_scale(glm::vec3 new_scale)
{
    scale = new_scale;
    transform = calc_model_matrix();
}

void LocalTransformComponent::set_scale(float new_scale)
{
    scale = glm::vec3(new_scale, new_scale, new_scale);
    transform = calc_model_matrix();
}

void LocalTransformComponent::set_position(glm::vec3 new_position)
{
    position = new_position;
    transform = calc_model_matrix();
}

void LocalTransformComponent::set_rotation(glm::vec3 new_rotation)
{
    rotation = new_rotation;
    transform = calc_model_matrix();
}

void Entity::set_uniform_data()
{
    unsigned int model_mat_loc = glGetUniformLocation(get_shader_program(), "model_mat");
    glUniformMatrix4fv(model_mat_loc, 1, GL_FALSE, glm::value_ptr(get_transform()));
}

void Entity::setup_attrib_pointers()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_data), (void*)offsetof(vertex_data, position) );
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_data), (void*)offsetof(vertex_data, texture_coordinate) );
    glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}


