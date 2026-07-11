#include "Renderable.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// ====== Renderable ====== //

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
    init_material();
}

void Renderable::render()
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
    glDrawElements(GL_TRIANGLES, get_indices_count(), GL_UNSIGNED_INT, nullptr);

    // Unbind this entity's VAO, so that we cannot accidentally draw this entity again.
    glBindVertexArray(0);
}

void Renderable::finish()
{
    glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO_vertices);
    glDeleteBuffers(1, &VBO_indices);
}

void Renderable::init_material()
{
    init_shader_paths();
    if (vert_file_path.empty() || frag_file_path.empty()) { return; }

    material = std::make_unique<BaseMaterial>(vert_file_path, frag_file_path);
    material->init();
}

void Renderable::init_shader_paths()
{
    vert_file_path = "vert.glsl";
    frag_file_path = "frag.glsl";
}



// ===== Instanced Renderable ===== //

void InstancedRenderable::init()
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
    init_material();
}

void InstancedRenderable::render()
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
    glDrawElementsInstanced(GL_TRIANGLES, get_indices_count(), GL_UNSIGNED_INT, nullptr, 1);

    // Unbind this entity's VAO, so that we cannot accidentally draw this entity again.
    glBindVertexArray(0);
}

void InstancedRenderable::finish()
{
    glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO_vertices);
    glDeleteBuffers(1, &VBO_indices);
}

void InstancedRenderable::init_material()
{
    init_shader_paths();
    if (vert_file_path.empty() || frag_file_path.empty()) { return; }

    material = std::make_unique<BaseMaterial>(vert_file_path, frag_file_path);
    material->init();
}

void InstancedRenderable::init_shader_paths()
{
    vert_file_path = "vert.glsl";
    frag_file_path = "frag.glsl";
}

