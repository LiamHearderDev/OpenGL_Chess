#include "GameState.h"

#include <engine/input/InputHandler.h>
#include <engine/logger/Logger.h>
#include <chess/ChessUtility.h>
#include <glm/glm.hpp>

void GameState::init()
{
    game_board = std::make_shared<GameBoard>();
    game_board->init();

    // Bind to the input handler
    engine.input_handler->on_mouse_pressed->add(this, &on_mouse_pressed);
    engine.input_handler->on_mouse_released->add(this, &on_mouse_released);
}

void GameState::on_mouse_pressed(mouse_click_data data)
{
    // Take the screen coords of cursor
    double pos_x = data.cursor_pos_x;
    double pos_y = data.cursor_pos_y;

    // Convert into world coordinatess
    glm::vec3 world_pos = glm::vec3(0.f, 0.f, 0.f);
    engine.input_handler->screen_to_world_space(pos_x, pos_y, world_pos);

    fprintf(stdout, "pressed at world: x=%f,    y=%f,   z=%f\n", world_pos.x, world_pos.y, world_pos.z);
    
    PiecePositions board_pos;
    const bool status = ChessUtility::world_to_board_position(world_pos, board_pos);
    if (status) {
        game_board->try_pickup_piece_at_location(board_pos);
    } else {
        fprintf(stderr, "could not convert...\n");
    }
}

void GameState::on_mouse_released(mouse_click_data data)
{
    game_board->drop_piece();
}
