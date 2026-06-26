#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "rendering/MasterRenderer.h"
#include <vector>

class Renderable {

protected:
    std::vector<vertex_data> vertices;
    std::vector<unsigned int> indices;
    unsigned int vertex_offset = 0;
    unsigned int VAO;

    virtual void init();
    virtual void render();
    virtual void setup_attrib_pointers();

public:
    unsigned int get_vertices_count() { return vertices.size(); }
    unsigned int get_indices_count() { return indices.size(); }
    unsigned int get_vertex_offset() { return vertex_offset; }
    unsigned int get_vao() { return VAO; }
};

#endif // RENDERABLE_H