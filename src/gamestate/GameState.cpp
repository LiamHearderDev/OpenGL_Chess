#include "GameState.h"

#include "input/InputHandler.h"

void GameState::register_input_handler(InputHandler &handler)
{
    input_handler = &handler;

    input_handler->on_mouse_pressed->add(this, &on_mouse_pressed);
    input_handler->on_mouse_released->add(this, &on_mouse_released);
}

void GameState::init()
{
    game_board = std::make_shared<GameBoard>();
    game_board->init();
}

void GameState::on_mouse_pressed(mouse_click_data data)
{
    // Take the screen coords of cursor
    double pos_x = data.cursor_pos_x;
    double pos_y = data.cursor_pos_y;

    // Convert into world coordinates
    float world_x, world_y, world_z;
    input_handler->screen_to_world_space( pos_x, pos_y,
        &world_x, &world_y, &world_z );
    
    
}

void GameState::on_mouse_released(mouse_click_data data)
{
}
