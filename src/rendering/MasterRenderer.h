#ifndef MASTER_RENDERER_H
#define MASTER_RENDERER_H

#include <glm/glm.hpp>
#include "gamestate/GameState.h"
#include "rendering/materials/BaseMaterial.h"
#include "rendering/entities/Entity.h"

#include <vector>
#include <string>
#include <memory>

class MasterRenderer {

    GameState* game_state;
    std::vector<std::unique_ptr<RenderableBase>> renderables;

public:
    MasterRenderer() = default;
    ~MasterRenderer() { finish(); }

    int init();
    void draw();
    void finish();

    void register_game_state(GameState& new_game_state);
};



#endif //MASTER_RENDERER_H