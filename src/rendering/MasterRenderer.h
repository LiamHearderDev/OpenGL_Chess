#ifndef MASTER_RENDERER_H
#define MASTER_RENDERER_H


#include <glad/glad.h>


class MasterRenderer {

    GLuint VAO;
    GLuint VBO;
    GLuint shaderProgram{};

    const float squareVertices[16] = {
        -0.5f,  0.5f,   // Top-left
        0.5f,   0.5f,   // Top-right
        0.5f,   0.5f,   // Top-right
        0.5f,   -0.5f,  // Bottom-right
        0.5f,   -0.5f,  // Bottom-right
        -0.5f,  -0.5f,  // Bottom-left
        -0.5f,  -0.5f,  // Bottom-left
        -0.5f,  0.5f,   // Top-left
    }; 

public:
    MasterRenderer() = default;
    void init();
    void draw();
    void finish();
    GLuint initShader(const char* vert_shader, const char* frag_shader);
};

#endif //MASTER_RENDERER_H