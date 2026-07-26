#ifndef ENTITY_H
#define ENTITY_H

#include <rendering/renderables/derived/Renderable.h>
#include <rendering/components/transform/local/LocalTransformComponent.h>

#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <glm/glm.hpp>


// ====== ENTITY ====== //

/**
 * A structure representing the data of an entity.
 * Entities are renderable objects that can be transformed within the scene. 
 */
class Entity : public Renderable {

public:

    std::unique_ptr<LocalTransformComponent> local_transform_component;

    Entity(renderable_data&& render_data) :
        Renderable(std::move(render_data)),
        local_transform_component(std::make_unique<LocalTransformComponent>(glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f))) 
        {}
    
    void set_uniform_data() override;

protected:
    void setup_attrib_pointers() override;

    glm::vec2 cursor_position{};
};


#endif // ENTITY_H