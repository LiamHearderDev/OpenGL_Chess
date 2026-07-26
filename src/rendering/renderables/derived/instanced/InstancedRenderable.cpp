#include "InstancedRenderable.h"

#include <glad/glad.h>

// ===== Instanced Renderable ===== //

void InstancedRenderable::init()
{
    // Initialise VAO
    glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

    // VERTICES 
    glGenBuffers(1, &VBO_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_vertices);
    glBufferData(
        GL_ARRAY_BUFFER, 
        (size_t)(sizeof(vertex_data) * get_vertices_count()),
        vertices.data(),
        GL_STATIC_DRAW
    );

    // INSTANCES 
    glGenBuffers(1, &VBO_instances);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_instances);
    glBufferData(
        GL_ARRAY_BUFFER, 
        (size_t)(sizeof(glm::mat4) * instanced_transform_component->get_transforms().size()), 
        instanced_transform_component->get_transforms().data(), 
        GL_STATIC_DRAW
    );
    
    // INDICES 
    glGenBuffers(1, &VBO_indices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_indices);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, 
        (size_t)(sizeof(unsigned int) * get_indices_count()), 
        indices.data(), 
        GL_STATIC_DRAW
    );

    setup_attrib_pointers();

    glBindVertexArray(0); // Unbind, so we don't accidentally write to the above VAO 
    
    // Initialise shader 
    init_material();

    // Bind instance updates
    instanced_transform_component->on_update->add(this, &update_instance_vbo);
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
    glDrawElementsInstanced(GL_TRIANGLES, get_indices_count(), GL_UNSIGNED_INT, nullptr, instance_count);

    // Unbind this entity's VAO, so that we cannot accidentally draw this entity again.
    glBindVertexArray(0);
}

void InstancedRenderable::finish()
{
    glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO_vertices);
    glDeleteBuffers(1, &VBO_indices);
    glDeleteBuffers(1, &VBO_instances);
}

void InstancedRenderable::update_instance_vbo()
{
    fprintf(stdout, "UPDATING VBO...\n");
    const size_t offset = (size_t)(sizeof(vertex_data) * get_vertices_count());
    const size_t data_size = (size_t)(sizeof(glm::mat4) * instanced_transform_component->get_transforms().size());
    glBufferSubData(GL_ARRAY_BUFFER, offset, data_size, instanced_transform_component->get_transforms().data());
}

void InstancedRenderable::setup_attrib_pointers()
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