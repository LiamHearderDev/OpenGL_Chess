#ifndef ENTITY_H
#define ENTITY_H

#include "rendering/components/Renderable.h"
#include "rendering/components/TransformComponent.h"

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
class Entity : public Renderable, public LocalTransformComponent {

public:
    Entity(renderable_data&& render_data) :
        LocalTransformComponent(glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)),
        Renderable(std::move(render_data)) {}
    
    void set_uniform_data() override;

protected:
    void setup_attrib_pointers() override;

    void set_cursor_position(glm::dvec2 pos) override { cursor_position = glm::vec2(static_cast<float>(pos.x), static_cast<float>(pos.y)); }

    glm::vec2 cursor_position{};
};



// ====== INSTANCED ENTITY ====== //

/**
 * A structure representing the data of an entity that utilises instancing.
 * Instanced entities are renderable objects that is placed multiple times where each instance
 * can be transformed within the scene.
 */
class InstancedEntity : public InstancedRenderable, public InstancedTransformComponent {
public:
    InstancedEntity(renderable_data&& render_data, unsigned int instance_count) : 
        InstancedTransformComponent(),
        InstancedRenderable(std::move(render_data), instance_count) {}
    
    void set_uniform_data() override;

protected:
    void setup_attrib_pointers() override;

    void set_cursor_position(glm::dvec2 pos) override { cursor_position = glm::vec2(static_cast<float>(pos.x), static_cast<float>(pos.y)); }

    std::vector<glm::mat4> get_instance_transforms() const override { return get_transforms(); }
    glm::vec2 cursor_position{};
};

#endif // ENTITY_H