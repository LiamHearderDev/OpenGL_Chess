#ifndef INSTANCED_ENTITY_H
#define INSTANCED_ENTITY_H

#include <rendering/renderables/derived/instanced/InstancedRenderable.h>
#include <rendering/components/transform/instanced/InstancedTransformComponent.h>

// ====== INSTANCED ENTITY ====== //

/**
 * A structure representing the data of an entity that utilises instancing.
 * Instanced entities are renderable objects that is placed multiple times where each instance
 * can be transformed within the scene.
 */
class InstancedEntity : public InstancedRenderable {

public:
    std::unique_ptr<InstancedTransformComponent> instanced_transform_component;

    InstancedEntity(renderable_data&& render_data, unsigned int instance_count) : 
        InstancedRenderable(std::move(render_data), instance_count),
        instanced_transform_component(std::make_unique<InstancedTransformComponent>())
        {}
        
    void set_uniform_data() override;

protected:
    void setup_attrib_pointers() override;

    std::vector<glm::mat4> get_instance_transforms() const override { return instanced_transform_component->get_transforms(); }
    glm::vec2 cursor_position{};
};

#endif // INSTANCED_ENTITY_H