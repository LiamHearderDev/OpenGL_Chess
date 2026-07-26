#ifndef INSTANCED_TRANSFORM_COMPONENT_H
#define INSTANCED_TRANSFORM_COMPONENT_H

#include <glm/glm.hpp>
#include <vector>

/**
 * A transform component used by Instanced meshes. 
 */
class InstancedTransformComponent {
    std::vector<glm::mat4> transformations;
    
public:
    InstancedTransformComponent() {}
    ~InstancedTransformComponent() {}

    [[nodiscard]] glm::mat4 calc_instance_transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) const;

    void set_transforms(std::vector<glm::mat4>&& new_transforms);
    void set_transform_at(glm::mat4 new_transform, unsigned int index);
    void remove_transform(unsigned int index) {}
    void add_transform(glm::mat4 new_transform) {}
    
    std::vector<glm::mat4> get_transforms() const { return transformations; }
};


#endif // INSTANCED_TRANSFORM_COMPONENT_H