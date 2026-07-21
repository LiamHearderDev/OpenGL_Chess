#include "GameState.h"

#include "input/InputHandler.h"

void GameState::register_input_handler(InputHandler &handler)
{
    input_handler = &handler;

    

}

void GameState::init()
{
    game_board = std::make_shared<GameBoard>();
    game_board->init();
}