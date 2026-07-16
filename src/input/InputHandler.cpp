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

				// Detect if we are beginning a drag, and retrieve info from the GameBoard if we are.
				

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

		float x, y, z;
		manager->screen_to_world_space(pos_x, pos_y, &x, &y, &z);

		fprintf(stdout, "x=%f,	y=%f,	z=%f\n", x, y, z);
	}
}


// ================== //

void InputHandler::register_game_state(GameState& new_game_state)
{
    if (game_state) { return; }
    game_state = &new_game_state;
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

void InputHandler::screen_to_world_space(double screen_x, double screen_y, float* world_x, float* world_y, float* world_z)
{
	if (!window || !world_x || !world_y || !world_z) { return; }
	
	int screen_width, screen_height;
	glfwGetWindowSize(window, &screen_width, &screen_height);

	*world_x = screen_x / screen_width * 2 - 1;
	*world_y = 1 - screen_y / screen_height * 2;
	*world_z = 0.f;
}
