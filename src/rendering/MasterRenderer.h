#ifndef MASTER_RENDERER_H
#define MASTER_RENDERER_H

#include <glm/glm.hpp>

#include "../chess/GameBoard.h"

struct vertex_data {
    glm::vec3 position;
    glm::vec2 texture_coordinate;
};

class MasterRenderer {

    unsigned int VAO;
    unsigned int VBO;
    unsigned int shaderProgram{};

    GameBoard game_board{};

    // const float squareVertices[24] = {
    //     -0.5f,  0.5f,   0.f,   // Top-left
    //     0.5f,   0.5f,   0.f,   // Top-right
    //     0.5f,   0.5f,   0.f,   // Top-right
    //     0.5f,   -0.5f,  0.f,  // Bottom-right
    //     0.5f,   -0.5f,  0.f,  // Bottom-right
    //     -0.5f,  -0.5f,  0.f,  // Bottom-left
    //     -0.5f,  -0.5f,  0.f,  // Bottom-left
    //     -0.5f,  0.5f,   0.f   // Top-left
    // };

    const std::array<vertex_data, 4> board_vertices = {
        vertex_data{ {-0.5f, 0.5f, 0.f},      {0.f, 1.0f}    },  // Top-left
        vertex_data{ {0.5f, 0.5f, 0.f},       {1.0f, 1.0f}   },  // Top-right
        vertex_data{ {0.5f, -0.5f, 0.f},      {1.0f, 0.f}    },  // Bottom-right
        vertex_data{ {-0.5f, -0.5f, 0.f},     {0.f, 0.f}     },  // Bottom-left
    };

public:
    MasterRenderer() = default;
    int init();
    void draw();
    void finish();
    unsigned int initShader(const char* vert_shader, const char* frag_shader);
};



#endif //MASTER_RENDERER_H