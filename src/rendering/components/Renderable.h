#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "rendering/materials/BaseMaterial.h"

#include <vector>
#include <string>
#include <memory>
#include <glm/glm.hpp>


// ====== Data Structures ====== //

struct vertex_data {
    glm::vec3 position;
    glm::vec2 texture_coordinate;
};

struct instanced_vertex_data {
    glm::vec3 position;
    glm::vec2 texture_coordinate;
    glm::mat4 instance_transform;
};

struct renderable_data {
    std::vector<vertex_data> vertices;
    std::vector<unsigned int> indices;
};

struct instanced_renderable_data {
    std::vector<instanced_vertex_data> vertices;
    std::vector<unsigned int> indices;
};



// ====== Renderable Component ====== //

class Renderable {
private:
    std::vector<vertex_data> vertices;
    std::vector<unsigned int> indices;

    unsigned int VAO{};
    unsigned int VBO_vertices{};
    unsigned int VBO_indices{};

    /** Finishes up the class so that it can be safely unloaded. This should only be called by the destructor. */
    void finish();

protected:
    std::unique_ptr<BaseMaterial> material;

    /** The file path of the desired vertex shader. Must be overriden. */
    std::string vert_file_path;

    /** The file path of the desired fragment shader. Must be overriden. */
    std::string frag_file_path = "frag.glsl";

    virtual void setup_attrib_pointers() {}

    /** Sets the variable `material` to be a valid pointer, i.e., used for material initialisation in `init()`. */
    virtual void init_material();

    /** Initialises the file paths for shaders. Designed to be overriden for derived classes. */
    virtual void init_shader_paths();

public:
    Renderable(renderable_data&& render_data) : 
        vertices(std::move(render_data.vertices)),
        indices(std::move(render_data.indices)) { }
    
    ~Renderable() { finish(); }

    /** Initialisation Function. Should only be called by the constructor, and not by the user. */
    void init();

    /** Render the entity. This should be called every frame, and only called by the MasterRenderer. */ 
    virtual void render();

    /** Sets uniform variable data used by shaders. */
    virtual void set_uniform_data() {}

    // === Public Functions used for retrieving information about an instance of this class. === //

    unsigned int get_vertices_count() { return vertices.size(); }
    unsigned int get_indices_count() { return indices.size(); }
    unsigned int get_vao() { return VAO; }
    unsigned int get_shader_program() { return material->get_shader_program(); }
    unsigned int get_texture_id() { return material->get_texture_id(); }
};



// ====== Instanced Renderable Component ====== //

class InstancedRenderable {
private:
    std::vector<instanced_vertex_data> vertices;
    std::vector<unsigned int> indices;

    unsigned int VAO{};
    unsigned int VBO_vertices{};
    unsigned int VBO_indices{};

    /** Finishes up the class so that it can be safely unloaded. This should only be called by the destructor. */
    void finish();

protected:

    std::unique_ptr<BaseMaterial> material;

    /** The file path of the desired vertex shader. Must be overriden. */
    std::string vert_file_path;

    /** The file path of the desired fragment shader. Must be overriden. */
    std::string frag_file_path;

    virtual void setup_attrib_pointers() {}

    /** Sets the variable `material` to be a valid pointer, i.e., used for material initialisation in `init()`. */
    virtual void init_material();

    /** Initialises the file paths for shaders. Designed to be overriden for derived classes. */
    virtual void init_shader_paths();

public:
    InstancedRenderable(instanced_renderable_data&& render_data) : 
        vertices(std::move(render_data.vertices)),
        indices(std::move(render_data.indices)) { }
    
    ~InstancedRenderable() { finish(); }

    /** Initialisation Function. Should only be called by the constructor, and not by the user. */
    void init();

    /** Render the entity. This should be called every frame, and only called by the MasterRenderer. */ 
    virtual void render();

    /** Sets uniform variable data used by shaders. */
    virtual void set_uniform_data() {}

    // === Public Functions used for retrieving information about an instance of this class. === //

    unsigned int get_vertices_count() { return vertices.size(); }
    unsigned int get_indices_count() { return indices.size(); }
    unsigned int get_vao() { return VAO; }
    unsigned int get_shader_program() { return material->get_shader_program(); }
    unsigned int get_texture_id() { return material->get_texture_id(); }
};

#endif // RENDERABLE_H