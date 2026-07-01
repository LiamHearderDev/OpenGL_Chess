#ifndef MASTER_RENDERER_H
#define MASTER_RENDERER_H

#include <glm/glm.hpp>
#include "../chess/GameBoard.h"
#include "rendering/materials/BaseMaterial.h"
#include "rendering/entities/Entity.h"
#include "rendering/entities/pieces/PieceEntity.h"
#include "rendering/materials/pieces/PieceMaterial.h"

#include <vector>
#include <string>
#include <memory>

class MasterRenderer {

    unsigned int VAO{};
    unsigned int VBO{};
    unsigned int shaderProgram{};

    GameBoard game_board{};

    const std::vector<vertex_data> board_vertices = {
        vertex_data{ {-0.5f, 0.5f, -1.f},      {0.f, 1.0f}    },  // Top-left
        vertex_data{ {0.5f, 0.5f, -1.f},       {1.0f, 1.0f}   },  // Top-right
        vertex_data{ {0.5f, -0.5f, -1.f},      {1.0f, 0.f}    },  // Bottom-right
        vertex_data{ {-0.5f, -0.5f, -1.f},     {0.f, 0.f}     },  // Bottom-left
    };

    const std::vector<vertex_data> piece_vertices = {
        vertex_data{ {-0.5f, 0.5f, 0.f},      {0.f, 1.0f}    },  // Top-left
        vertex_data{ {0.5f, 0.5f, 0.f},       {1.0f, 1.0f}   },  // Top-right
        vertex_data{ {0.5f, -0.5f, 0.f},      {1.0f, 0.f}    },  // Bottom-right
        vertex_data{ {-0.5f, -0.5f, 0.f},     {0.f, 0.f}     },  // Bottom-left
    };

    std::vector<std::unique_ptr<Entity>> entities;

    void drawPiece();

public:
    MasterRenderer() = default;
    ~MasterRenderer() { finish(); }
    int init();
    void draw();
    void finish();
    
private:
    
};



#endif //MASTER_RENDERER_H