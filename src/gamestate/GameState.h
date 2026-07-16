#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "chess/GameBoard.h"
#include <memory>

class GameState {
    
public:
    GameState() {}
    ~GameState() {}

    std::shared_ptr<GameBoard> game_board{};

    void init();
};

#endif // GAME_STATE_H