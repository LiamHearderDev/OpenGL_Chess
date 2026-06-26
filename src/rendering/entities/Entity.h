#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>
#include <glm/glm.hpp>

#include "Renderable.h"

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


/**
 * A structure representing the data of a renderable entity.
 * Including vertices, indices, etc.
 */
class Entity : public Renderable, public LocalTransformComponent {
    std::string name;
    std::string shader_path;
    unsigned int vertex_offset = 0; // Used for instancing.
public:
    Entity(const std::string name, const std::string shader_path) : 
        name(name), shader_path(shader_path), 
        LocalTransformComponent(glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)) {}
};


#endif // ENTITY_H