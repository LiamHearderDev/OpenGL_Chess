#pragma once

class GameState;
class InputHandler;
class MasterRenderer;
class WindowManager;
class Logger;

struct EngineContext {
    GameState* game_state;
    InputHandler* input_handler;
    MasterRenderer* master_renderer;
    WindowManager* window_manager;
    Logger* logger;
};