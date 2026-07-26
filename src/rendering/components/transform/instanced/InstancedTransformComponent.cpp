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

void InstancedTransformComponent::set_transforms(std::vector<glm::mat4> &&new_transforms)
{
    transformations = new_transforms;
}

void InstancedTransformComponent::set_transform_at(glm::mat4 new_transform, unsigned int index)
{
    if (transformations.size() <= index) {
        return;
    }
    transformations[index] = new_transform;
}