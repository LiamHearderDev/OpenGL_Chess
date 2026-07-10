#ifndef ENTITY_H
#define ENTITY_H

#include "rendering/components/Renderable.h"

#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <glm/glm.hpp>




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



// ====== ENTITY ====== //

/**
 * A structure representing the data of an entity.
 * Entities are renderable objects that can be transformed within the scene. 
 */
class Entity : public Renderable, public LocalTransformComponent {

public:
    Entity(renderable_data&& render_data) :
        LocalTransformComponent(glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)),
        Renderable(std::move(render_data)) {}
    
    void set_uniform_data() override;

protected:
    void setup_attrib_pointers() override;
};



// ====== INSTANCED ENTITY ====== //

/**
 * A structure representing the data of an entity that utilises instancing.
 * Instanced entities are renderable objects that is placed multiple times where each instance
 * can be transformed within the scene.
 */
class InstancedEntity : public InstancedRenderable {
public:
    InstancedEntity(instanced_renderable_data&& render_data) : 
        InstancedRenderable(std::move(render_data)) {}
    
    void set_uniform_data() override;

protected:
    void setup_attrib_pointers() override;
};

#endif // ENTITY_H