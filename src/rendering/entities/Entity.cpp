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
    // 1. Initialise vertices
    glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

    glGenBuffers(1, &VBO_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_vertices);
    glBufferData(GL_ARRAY_BUFFER, (long)(sizeof(vertex_data) * get_vertices_count()), vertices.data(), GL_STATIC_DRAW);
    setup_attrib_pointers();

    glGenBuffers(1, &VBO_indices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_indices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (long)(sizeof(unsigned int) * get_indices_count()), indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0); // Unbind, so we don't accidentally write to the above VAO

    // 2. Initialise shader
    material->init();
}

void Renderable::render()
{
    /**
     * 1. Use shader
     * 2. Set shader data (such as projection view matrix, view position, instance model matrix, etc...)
     * 3. Set active texture (GL_TEXTURE0 to start), then bind texture.
     * 4. Bind VAO
     * 5. Draw()
     */

    material->use();


    glBindVertexArray(VAO);

    glDrawElementsBaseVertex(GL_TRIANGLES, get_indices_count(), GL_UNSIGNED_INT, nullptr, vertex_offset);
    glBindVertexArray(0);
}

void Renderable::finish()
{
    glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO_vertices);
    glDeleteBuffers(1, &VBO_indices);
}

void Entity::setup_attrib_pointers()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_data), (void*)offsetof(vertex_data, position) );
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_data), (void*)offsetof(vertex_data, texture_coordinate) );
    glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}


