#ifndef INSTANCED_RENDERABLE_H
#define INSTANCED_RENDERABLE_H

#include <engine/rendering/components/transform/instanced/InstancedTransformComponent.h>
#include <engine/rendering/renderables/derived/Renderable.h>


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
public:
    std::unique_ptr<InstancedTransformComponent> instanced_transform_component;
protected:
    std::unique_ptr<BaseMaterial> material;

    /** The file path of the desired vertex shader. Must be overriden. */
    std::string vert_file_path;

    /** The file path of the desired fragment shader. Must be overriden. */
    std::string frag_file_path;


public:
    InstancedRenderable(renderable_data&& render_data, unsigned int instance_count) : 
        instance_count(instance_count),
        vertices(std::move(render_data.vertices)),
        indices(std::move(render_data.indices)),
        instanced_transform_component(std::make_unique<InstancedTransformComponent>())
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
private:
    /** Finishes up the class so that it can be safely unloaded. This should only be called by the destructor. */
    void finish() override;
    void update_instance_vbo();

protected:
    virtual void setup_attrib_pointers() override;
    virtual void init_material() override;
    virtual void init_shader_paths() override;
};

#endif // INSTANCED_RENDERABLE_H