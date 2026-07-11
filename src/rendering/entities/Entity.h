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
};



// ====== INSTANCED ENTITY ====== //

/**
 * A structure representing the data of an entity that utilises instancing.
 * Instanced entities are renderable objects that is placed multiple times where each instance
 * can be transformed within the scene.
 */
class InstancedEntity : public InstancedRenderable, public InstancedTransformComponent {
public:
    InstancedEntity(renderable_data&& render_data) : 
        InstancedTransformComponent(),
        InstancedRenderable(std::move(render_data)) {}
    
    void set_uniform_data() override;

protected:
    void setup_attrib_pointers() override;
};

#endif // ENTITY_H