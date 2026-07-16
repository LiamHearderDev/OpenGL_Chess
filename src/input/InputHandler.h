#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "chess/GameBoard.h"
#include "gamestate/GameState.h"

class InputHandler {

    GameState* game_state;
    GLFWwindow* window;

public:

    // ====== Callback variables ====== //

    // Mouse Variables (Dragging)
    bool isDragging = false;
    double last_x = 0.0;
    double last_y = 0.0;


    // ====== Functions ====== //

    void register_game_state(GameState& new_game_state);
    void register_window(GLFWwindow& window);

    void screen_to_world_space(double screen_x, double screen_y, float* world_x, float* world_y, float* world_z);

    // A new function to determine if a click event is hovering over a piece on the board
        // Calls a function in the game board which converts a 2D screen location to a board position.
};

#endif // INPUT_HANDLER_H