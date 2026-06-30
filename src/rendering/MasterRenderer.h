#ifndef MASTER_RENDERER_H
#define MASTER_RENDERER_H

#include <glm/glm.hpp>
#include "../chess/GameBoard.h"
#include "rendering/materials/BaseMaterial.h"
#include "rendering/entities/Entity.h"
#include "rendering/entities/pieces/PieceEntity.h"

#include <vector>
#include <string>

class MasterRenderer {

    unsigned int VAO;
    unsigned int VBO;
    unsigned int shaderProgram{};

    GameBoard game_board{};

    const std::vector<vertex_data> board_vertices = {
        vertex_data{ {-0.5f, 0.5f, 0.f},      {0.f, 1.0f}    },  // Top-left
        vertex_data{ {0.5f, 0.5f, 0.f},       {1.0f, 1.0f}   },  // Top-right
        vertex_data{ {0.5f, -0.5f, 0.f},      {1.0f, 0.f}    },  // Bottom-right
        vertex_data{ {-0.5f, -0.5f, 0.f},     {0.f, 0.f}     },  // Bottom-left
    };

    const std::vector<vertex_data> piece_vertices = {
        vertex_data{ {-0.5f, 0.5f, 1.f},      {0.f, 1.0f}    },  // Top-left
        vertex_data{ {0.5f, 0.5f, 1.f},       {1.0f, 1.0f}   },  // Top-right
        vertex_data{ {0.5f, -0.5f, 1.f},      {1.0f, 0.f}    },  // Bottom-right
        vertex_data{ {-0.5f, -0.5f, 1.f},     {0.f, 0.f}     },  // Bottom-left
    };

    const renderable_data board_data = {
        board_vertices,
        std::vector<unsigned int>{0,1,3, 1,2,3},
        new BaseMaterial("board/vert.glsl", "board/frag.glsl") // TODO: Ensure you can actually pass through shaders
    };

    const renderable_data pawn_data = {
        piece_vertices, // TODO: obviously change this
        std::vector<unsigned int>{0,1,3, 1,2,3},
        new BaseMaterial("pieces/vert.glsl", "pieces/frag.glsl", "chess/piece_spritesheet.png")
    };
    
    std::vector<Entity*> entities;

    void drawPiece();

public:
    MasterRenderer() = default;
    int init();
    void draw();
    void finish();
    
private:
    
};



#endif //MASTER_RENDERER_H