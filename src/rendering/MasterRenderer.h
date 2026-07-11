#ifndef MASTER_RENDERER_H
#define MASTER_RENDERER_H

#include <glm/glm.hpp>
#include "../chess/GameBoard.h"
#include "rendering/materials/BaseMaterial.h"
#include "rendering/entities/Entity.h"

#include <vector>
#include <string>
#include <memory>

class MasterRenderer {

    std::unique_ptr<GameBoard> game_board;
    std::vector<std::unique_ptr<RenderableBase>> renderables;

public:
    MasterRenderer() = default;
    ~MasterRenderer() { finish(); }
    int init();
    void draw();
    void finish();
};



#endif //MASTER_RENDERER_H