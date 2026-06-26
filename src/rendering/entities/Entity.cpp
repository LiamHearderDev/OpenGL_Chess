#include "Entity.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>

glm::mat4 LocalTransformComponent::calc_model_matrix() const
{
    glm::mat4 model{};
    model = glm::translate(model, position);
    model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, scale);
    return model;
}

void Renderable::init()
{
    GLuint VBO_vertices, VBO_indices;
    glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

    glGenBuffers(1, &VBO_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_vertices);
    glBufferData(GL_ARRAY_BUFFER, (long)(sizeof(vertex_data) * get_vertices_count()), vertices.data(), GL_STATIC_DRAW);
    setup_attrib_pointers();

    glGenBuffers(1, &VBO_indices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_indices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (long)(sizeof(unsigned int) * get_indices_count()), indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void Renderable::render()
{
    glBindVertexArray(VAO);
    glDrawElementsBaseVertex(GL_TRIANGLES, get_indices_count(), GL_UNSIGNED_INT, nullptr, vertex_offset);
    glBindVertexArray(0);
}

void Renderable::setup_attrib_pointers()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_data), (void*)offsetof(vertex_data, position) );
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_data), (void*)offsetof(vertex_data, texture_coordinate) );
    glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}
