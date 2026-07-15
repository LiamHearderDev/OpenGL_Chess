#include "InputHandler.h"

// ===== Callbacks ===== //

void on_mouse_button(GLFWwindow *window, int button, int action, int mods)
{
	InputHandler* manager = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
	if (!manager) { return; }

	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		switch(action) {
			case GLFW_PRESS:
				manager->isDragging = true;
				glfwGetCursorPos(window, &(manager->last_x), &(manager->last_y));
				break;
			case GLFW_RELEASE:
				manager->isDragging = false;
				break;
		}
	}
}

void on_mouse_moved(GLFWwindow *window, double pos_x, double pos_y)
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
}
