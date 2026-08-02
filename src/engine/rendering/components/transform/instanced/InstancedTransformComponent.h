#ifndef INSTANCED_TRANSFORM_COMPONENT_H
#define INSTANCED_TRANSFORM_COMPONENT_H

#include <delegates/MulticastDelegate.h>
#include <glm/glm.hpp>
#include <vector>

/**
 * A transform component used by Instanced meshes. 
 */
class InstancedTransformComponent {
    std::vector<glm::mat4> transformations;
    
public:
    DECLARE_MULTICAST_DELEGATE(on_update);

    InstancedTransformComponent() {}
    ~InstancedTransformComponent() {}

    [[nodiscard]] glm::mat4 calc_instance_transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) const;

    void set_transforms(std::vector<glm::mat4> new_transforms, bool update); 
    void set_transform_at(glm::mat4 new_transform, unsigned int index, bool update = true);
    void remove_transform(unsigned int index, bool update) {}
    void add_transform(glm::mat4 new_transform, bool update) {}
    
    std::vector<glm::mat4> get_transforms() const;
    int get_instance_count() const;
};


#endif // INSTANCED_TRANSFORM_COMPONENT_H