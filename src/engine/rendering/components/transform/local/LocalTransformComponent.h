#ifndef LOCAL_TRANSFORM_COMPONENT_H
#define LOCAL_TRANSFORM_COMPONENT_H

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

    ~LocalTransformComponent() {}

    glm::mat4 get_transform() const { return transform; }

    void set_scale(glm::vec3 new_scale);
    void set_scale(float new_scale);
    void set_position(glm::vec3 new_position);
    void set_rotation(glm::vec3 new_rotation);
};

#endif // LOCAL_TRANSFORM_COMPONENT_H