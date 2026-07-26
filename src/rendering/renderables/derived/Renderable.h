#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "rendering/materials/BaseMaterial.h" // TODO: MOVE TO CPP?

#include <rendering/renderables/base/RenderableBase.h>
#include <rendering/renderables/data/RenderableData.h>

#include <string>
#include <memory>
#include <glm/glm.hpp>




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

#endif // RENDERABLE_H