#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <memory>

#include "chess/GameBoard.h"

// Forward declarations
class InputHandler;

class GameState {
    InputHandler* input_handler;

public:
    GameState() {}
    ~GameState() {}

    std::shared_ptr<GameBoard> game_board{};

    void register_input_handler(InputHandler& handler) { input_handler = &handler; }
    void init();
};

#endif // GAME_STATE_H