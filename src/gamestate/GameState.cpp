#include "GameState.h"

#include "input/InputHandler.h"

void GameState::init()
{
    game_board = std::make_shared<GameBoard>();
    game_board->init();
}