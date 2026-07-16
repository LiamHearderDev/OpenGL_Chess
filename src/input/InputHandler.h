#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "chess/GameBoard.h"

class InputHandler {

    GameBoard* game_board;
    GLFWwindow* window;

    

public:

    // ====== Callback variables ====== //

    // Mouse Variables (Dragging)
    bool isDragging = false;
    double last_x = 0.0;
    double last_y = 0.0;


    // ====== Functions ====== //

    void register_game_board(GameBoard& game_board_ptr);
    void register_window(GLFWwindow& window);
};

#endif // INPUT_HANDLER_H