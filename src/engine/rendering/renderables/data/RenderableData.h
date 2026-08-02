#ifndef RENDERABLE_DATA_H
#define RENDERABLE_DATA_H

#include <glm/glm.hpp>
#include <vector>

// ====== Data Structures ====== //

struct vertex_data {
    glm::vec3 position;
    glm::vec2 texture_coordinate;
};

struct renderable_data {
    std::vector<vertex_data> vertices;
    std::vector<unsigned int> indices;
};


#endif // RENDERABLE_DATA_H