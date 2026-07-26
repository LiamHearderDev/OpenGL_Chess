#include "InstancedEntity.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>


// ===== Instanced Entity ===== //

void InstancedEntity::set_uniform_data()
{

}

void InstancedEntity::setup_attrib_pointers()
{
    glBindBuffer(GL_ARRAY_BUFFER, get_vbo_vertices());

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_data), (void*)offsetof(vertex_data, position) );
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_data), (void*)offsetof(vertex_data, texture_coordinate) );
    glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, get_vbo_instances());

    // Instance Transform Data
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(0));
    glVertexAttribDivisor(2, 1);

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(1 * sizeof(glm::vec4)));
    glVertexAttribDivisor(3, 1);

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
    glVertexAttribDivisor(4, 1);

    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
    glVertexAttribDivisor(5, 1);
}