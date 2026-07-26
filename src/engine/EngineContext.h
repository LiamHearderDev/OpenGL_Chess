#pragma once

class GameState;
class InputHandler;
class MasterRenderer;
class WindowManager;

struct EngineContext {
    GameState& game_state;
    InputHandler& input_handler;
    MasterRenderer& master_renderer;
    WindowManager& window_manager;
};