#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "rendering/materials/BaseMaterial.h"

#include <vector>
#include <string>
#include <memory>
#include <span>
#include <glm/glm.hpp>


// ====== Data Structures ====== //

struct vertex_data {
    glm::vec3 position;
    glm::vec2 texture_coordinate;
};

struct renderable_data {
    std::vector<vertex_data> vertices;
    std::vector<unsigned int> indices;
};



class RenderableBase {
protected:
    virtual void setup_attrib_pointers() = 0;

    /** Sets the variable `material` to be a valid pointer, i.e., used for material initialisation in `init()`. */
    virtual void init_material() = 0;

    /** Initialises the file paths for shaders. Designed to be overriden for derived classes. */
    virtual void init_shader_paths() = 0;

public:
    /** Initialisation Function. Must be manually called after construction. */
    virtual void init() = 0;

    virtual void finish() = 0;

    /** Render the entity. This should be called every frame, and only after initialisation. */ 
    virtual void render() = 0;

    /** Sets uniform variable data used by shaders. */
    virtual void set_uniform_data() = 0;
};


// ====== Renderable Component ====== //

class Renderable : public RenderableBase {
private:
    std::vector<vertex_data> vertices;
    std::vector<unsigned int> indices;

    unsigned int VAO{};
    unsigned int VBO_vertices{};
    unsigned int VBO_indices{};

    /** Finishes up the class so that it can be safely unloaded. This should only be called by the destructor. */
    void finish() override;

protected:
    std::unique_ptr<BaseMaterial> material;

    /** The file path of the desired vertex shader. Must be overriden. */
    std::string vert_file_path;

    /** The file path of the desired fragment shader. Must be overriden. */
    std::string frag_file_path;


    // === Overrides from `RenderableBase` === //

    virtual void setup_attrib_pointers() override {}
    virtual void init_material() override;
    virtual void init_shader_paths() override;

public:
    Renderable(renderable_data&& render_data) : 
        vertices(std::move(render_data.vertices)),
        indices(std::move(render_data.indices)) { }
    
    ~Renderable() { finish(); }

    // === Public Functions used for retrieving information about an instance of this class. === //

    unsigned int get_vertices_count() { return vertices.size(); }
    unsigned int get_indices_count() { return indices.size(); }
    unsigned int get_vao() { return VAO; }
    unsigned int get_shader_program() { return material->get_shader_program(); }
    unsigned int get_texture_id() { return material->get_texture_id(); }
    unsigned int get_vbo_vertices() { return VBO_vertices; }


    // === Overrides from `RenderableBase` === //

    virtual void init() override;
    virtual void render() override;
    virtual void set_uniform_data() override {}
};



// ====== Instanced Renderable Component ====== //

class InstancedRenderable : public RenderableBase {
private:
    std::vector<vertex_data> vertices;
    std::vector<unsigned int> indices;
    unsigned int instance_count = 0;

    unsigned int VAO{};
    unsigned int VBO_vertices{};
    unsigned int VBO_indices{};
    unsigned int VBO_instances{};

    /** Finishes up the class so that it can be safely unloaded. This should only be called by the destructor. */
    void finish() override;

protected:

    std::unique_ptr<BaseMaterial> material;

    /** The file path of the desired vertex shader. Must be overriden. */
    std::string vert_file_path;

    /** The file path of the desired fragment shader. Must be overriden. */
    std::string frag_file_path;

    void set_instance_count(unsigned int new_count);
    virtual std::vector<glm::mat4> get_instance_transforms() const = 0;


    // === Overrides from `RenderableBase` === //

    virtual void setup_attrib_pointers() override {}
    virtual void init_material() override;
    virtual void init_shader_paths() override;

public:
    InstancedRenderable(renderable_data&& render_data, unsigned int instance_count) : 
        instance_count(instance_count),
        vertices(std::move(render_data.vertices)),
        indices(std::move(render_data.indices)) 
        {}
    
    ~InstancedRenderable()
        { finish(); }


    // === Getters === //

    unsigned int get_vertices_count() const { return vertices.size(); }
    unsigned int get_indices_count() const  { return indices.size(); }
    unsigned int get_instance_count() const { return instance_count; }
    unsigned int get_vao() const            { return VAO; }
    unsigned int get_shader_program() const { return material->get_shader_program(); }
    unsigned int get_texture_id() const     { return material->get_texture_id(); }
    unsigned int get_vbo_vertices() const   { return VBO_vertices; }
    unsigned int get_vbo_instances() const  { return VBO_instances; }


    // === Overrides from `RenderableBase` === //

    virtual void init() override;
    virtual void render() override;
    virtual void set_uniform_data() override {}
};

#endif // RENDERABLE_H