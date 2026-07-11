#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include <glm/glm.hpp>
#include <vector>



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

    ~LocalTransformComponent() {}

    glm::mat4 get_transform() const { return transform; }

    void set_scale(glm::vec3 new_scale);
    void set_scale(float new_scale);
    void set_position(glm::vec3 new_position);
    void set_rotation(glm::vec3 new_rotation);
};



// ====== Instanced Transform Component ====== //

/**
 * A transform component used by Instanced meshes. 
 */
class InstancedTransformComponent {
    std::vector<glm::mat4> transformations;
public:
    InstancedTransformComponent() {}
    ~InstancedTransformComponent() {}

    void set_transforms(std::vector<glm::mat4>&& new_transforms);
    void set_transform_at(glm::mat4 new_transform, unsigned int index);
};


#endif // TRANSFORM_COMPONENT_H