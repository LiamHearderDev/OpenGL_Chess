#include "InputHandler.h"

#include <cstdio>


// ===== Callbacks ===== //

void glfw_callback_mouse_button(GLFWwindow *window, int button, int action, int mods)
{
	InputHandler* input_handler = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
	if (!input_handler) { return; }

	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		switch(action) {
			case GLFW_PRESS:
				input_handler->isDragging = true;
				glfwGetCursorPos(window, &(input_handler->last_x), &(input_handler->last_y));
				break;
			case GLFW_RELEASE:
				input_handler->isDragging = false;
				break;
		}
	}
}

void glfw_callback_mouse_moved(GLFWwindow *window, double pos_x, double pos_y)
{
	InputHandler* manager = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
	if (manager->isDragging) {
		const double delta_x = pos_x - manager->last_x;
		const double delta_y = pos_y - manager->last_y;

		manager->last_x = pos_x;
		manager->last_y = pos_y;

		fprintf(stdout, "x=%lf,	y=%lf\n", pos_x, pos_y);
	}
}


// ================== //

void InputHandler::register_game_board(GameBoard &game_board_ptr)
{
    if (game_board) { return; }
    game_board = &game_board_ptr;
}

void InputHandler::register_window(GLFWwindow& new_window)
{
    if (window) { return; }
    window = &new_window;

	// Set this class as a User Pointer, giving each GLFWwindow access to this class
	glfwSetWindowUserPointer(window, this);

	// Callbacks
	glfwSetCursorPosCallback(window, glfw_callback_mouse_moved);
	glfwSetMouseButtonCallback(window, glfw_callback_mouse_button);
}
