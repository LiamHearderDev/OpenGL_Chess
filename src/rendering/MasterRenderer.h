#ifndef MASTER_RENDERER_H
#define MASTER_RENDERER_H

#include <glm/glm.hpp>
#include <rendering/components/Renderable.h>

#include <vector>
#include <string>
#include <memory>

// Forward Declarations
class GameState;
class InputHandler;


/** The Master Renderer handles and manages all renderable entities in the scene. */
class MasterRenderer {

    GameState* game_state;
    InputHandler* input_handler;
    std::vector<std::unique_ptr<RenderableBase>> renderables;

public:
    MasterRenderer() = default;
    ~MasterRenderer() { finish(); }

    int init();
    void draw();
    void finish();

    void register_game_state(GameState& new_game_state);
    void register_input_handler(InputHandler& new_input_handler);
};



#endif //MASTER_RENDERER_H