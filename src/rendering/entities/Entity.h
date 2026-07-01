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
    std::unique_ptr<BaseMaterial> material;
};


// ====== Local Transform Component ====== //

class LocalTransformComponent {
public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
public:
    LocalTransformComponent(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) : 
        position(position), rotation(rotation), scale(scale) {}

    [[nodiscard]] glm::mat4 calc_model_matrix() const; 
};


// ====== Renderable Component ====== //

class Renderable {
private:
    std::vector<vertex_data> vertices;
    std::vector<unsigned int> indices;
    std::unique_ptr<BaseMaterial> material;

    unsigned int VAO;
    unsigned int VBO_vertices;
    unsigned int VBO_indices;

protected:
    unsigned int vertex_offset = 0; // Currently unused. Perhaps override this in an `InstancedEntity` derived class?
    virtual void setup_attrib_pointers() {}

public:
    Renderable(renderable_data&& render_data) : 
        vertices(std::move(render_data.vertices)),
        indices(std::move(render_data.indices)),
        material(std::move(render_data.material)) {}
    
    ~Renderable() { finish(); }

    void init();
    void render();
    void finish();

    unsigned int get_vertices_count() { return vertices.size(); }
    unsigned int get_indices_count() { return indices.size(); }
    unsigned int get_vertex_offset() { return vertex_offset; }
    unsigned int get_vao() { return VAO; }
    
    const char* get_vert_shader_path();
    const char* get_frag_shader_path();
};


// ====== ENTITY ====== //

/**
 * A structure representing the data of a renderable entity.
 * Including vertices, indices, etc.
 */
class Entity : public Renderable, public LocalTransformComponent {
    std::string name;
public:
    Entity(const std::string name, renderable_data&& render_data) :
        name(name), 
        LocalTransformComponent(glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)),
        Renderable(std::move(render_data)) {}

protected:
    void setup_attrib_pointers() override;
};

#endif // ENTITY_H