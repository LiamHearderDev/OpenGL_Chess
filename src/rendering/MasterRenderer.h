#ifndef MASTER_RENDERER_H
#define MASTER_RENDERER_H

class MasterRenderer {

    unsigned int VAO;
    unsigned int VBO;
    unsigned int shaderProgram{};

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
    unsigned int initShader(const char* vert_shader, const char* frag_shader);
};

#endif //MASTER_RENDERER_H