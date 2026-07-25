#include "InputHandler.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

// #include <cstdio>


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


	// === BROADCASTING === //
	double pos_x, pos_y;
	glfwGetCursorPos(window, &pos_x, &pos_y);

	mouse_click_data data = { button, action, mods, pos_x, pos_y };
	input_handler->on_mouse_button->broadcast(data);

	if (action == GLFW_PRESS) {
		input_handler->on_mouse_pressed->broadcast(data);
	} else if (action == GLFW_RELEASE) {
		input_handler->on_mouse_released->broadcast(data);
	}
}

void glfw_callback_mouse_moved(GLFWwindow *window, double pos_x, double pos_y)
{
	InputHandler* input_handler = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
	if(!input_handler) { return; }

	input_handler->on_mouse_move->broadcast(pos_x, pos_y);
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

void InputHandler::screen_to_world_space(double screen_x, double screen_y, float& world_x, float& world_y, float& world_z)
{
	if (!window) {
		fprintf(stderr, "ERROR: InputHandler::screen_to_world_space() error caused by uninitialised window.\n");
		return;
	}
	
	int screen_width, screen_height;
	glfwGetWindowSize(window, &screen_width, &screen_height);

	world_x = screen_x / screen_width * 2 - 1;
	world_y = 1 - screen_y / screen_height * 2;
	world_z = 0.f;
}

void InputHandler::screen_to_world_space(double screen_x, double screen_y, glm::vec3 &world)
{
	float x, y, z;
	screen_to_world_space(screen_x, screen_y, x, y, z);
	world = glm::vec3(x, y, z);
}

void InputHandler::screen_to_world_space(glm::dvec2 screen, float &world_x, float &world_y, float &world_z)
{
	screen_to_world_space(screen.x, screen.y, world_x, world_y, world_z);
}

void InputHandler::screen_to_world_space(glm::dvec2 screen, glm::vec3& world)
{
	float x, y, z;
	screen_to_world_space(screen.x, screen.y, x, y, z);
	world = glm::vec3(x, y, z);
}

bool InputHandler::get_is_dragging() const
{
    return isDragging;
}

glm::dvec2 InputHandler::get_cursor_position() const
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);
    return glm::dvec2(x, y);
}
