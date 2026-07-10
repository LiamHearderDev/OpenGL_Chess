#ifndef ENTITY_H
#define ENTITY_H

#include "rendering/materials/BaseMaterial.h"

#include <vector>
#include <string>
#include <memory>
#include <utility>
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


// ====== Local Transform Component ====== //

class LocalTransformComponent {
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::mat4 transform{1.f};

    [[nodiscard]] glm::mat4 calc_model_matrix() const;

public:
    LocalTransformComponent(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) : 
        position(position), rotation(rotation), scale(scale) { transform = calc_model_matrix(); }

    glm::mat4 get_transform() const { return transform; }
    void set_scale(glm::vec3 new_scale);
    void set_scale(float new_scale);
    void set_position(glm::vec3 new_position);
    void set_rotation(glm::vec3 new_rotation);
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

    unsigned int vertex_offset = 0; // Currently unused. Perhaps override this in an `InstancedEntity` derived class?
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
    void render();

    /** Sets uniform variable data used by shaders. */
    virtual void set_uniform_data() {}

    // === Public Functions used for retrieving information about an instance of this class. === //

    unsigned int get_vertices_count() { return vertices.size(); }
    unsigned int get_indices_count() { return indices.size(); }
    unsigned int get_vertex_offset() { return vertex_offset; }
    unsigned int get_vao() { return VAO; }
    unsigned int get_shader_program() { return material->get_shader_program(); }
    unsigned int get_texture_id() { return material->get_texture_id(); }
};


// ====== ENTITY ====== //

/**
 * A structure representing the data of a renderable entity.
 * Including vertices, indices, etc.
 */
class Entity : public Renderable, public LocalTransformComponent {

public:
    Entity(renderable_data&& render_data) :
        LocalTransformComponent(glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)),
        Renderable(std::move(render_data)) {}
    
    // Entity(std::unique_ptr<renderable_data>& render_data) :
    //     LocalTransformComponent(glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)),
    //     Renderable(std::move(render_data)) {}
    
    void set_uniform_data() override;

protected:
    void setup_attrib_pointers() override;
};

#endif // ENTITY_H