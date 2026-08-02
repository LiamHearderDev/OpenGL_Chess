#include "InstancedTransformComponent.h"

#include <glm/gtc/matrix_transform.hpp>


glm::mat4 InstancedTransformComponent::calc_instance_transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) const
{
    glm::mat4 model{1.f};
    model = glm::translate(model, position);
    model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, scale);
    return model;
}

void InstancedTransformComponent::set_transforms(std::vector<glm::mat4> new_transforms, bool update)
{
    transformations.clear();
    for (const auto& transform : new_transforms) {
        transformations.emplace_back(transform);
    }
}

void InstancedTransformComponent::set_transform_at(glm::mat4 new_transform, unsigned int index, bool update)
{
    if (transformations.size() <= index) {
        fprintf(stderr, "Error: InstancedTransformComponent::set_transform_at() - index %d is out of bounds (size: %d)\n", index, transformations.size());
        return;
    }
    transformations[index] = new_transform;
    
    if (update) on_update->broadcast();
}

std::vector<glm::mat4> InstancedTransformComponent::get_transforms() const
{
    return transformations;
}

int InstancedTransformComponent::get_instance_count() const
{
    return transformations.size();
}
