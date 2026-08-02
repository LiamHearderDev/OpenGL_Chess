#pragma once

#include <memory>

#include "chess/GameBoard.h"
#include "engine/input/InputData.h"
#include <engine/EngineContext.h>


class GameState {
    EngineContext engine;

public:
    GameState() {}
    ~GameState() {}

    std::shared_ptr<GameBoard> game_board{};

    void register_engine_context(EngineContext new_engine) { engine = new_engine; }
    void init();

private:

    // DELEGATE BINDINGS
    void on_mouse_pressed(mouse_click_data data);
    void on_mouse_released(mouse_click_data data);
};