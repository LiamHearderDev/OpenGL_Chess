#define GLFW_INCLUDE_NONE

#include <array>
#include <iostream>
#include <cstdint>
#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window/WindowManager.h"
#include "rendering/MasterRenderer.h"
#include "input/InputHandler.h"
#include "gamestate/GameState.h"


int main(int arc, char** argv) {
	fprintf(stdout, "Beginning OpenGL_Chess...\n");

	// Generate Engine Components
	std::shared_ptr<WindowManager>	window_manager 	= std::make_shared<WindowManager>();
	std::shared_ptr<MasterRenderer> master_renderer = std::make_shared<MasterRenderer>();
	std::shared_ptr<InputHandler> 	input_handler 	= std::make_shared<InputHandler>();
	std::shared_ptr<GameState>		game_state 		= std::make_shared<GameState>();

	// ======== Window setup ======== //
	fprintf(stdout, "Beginning Window Manager...\n");
	WindowManager::init();
	
	window_manager->createWindow(800, 800);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		fprintf(stderr, "Error: Failed to initialize GLAD.\n");
		return 1;
	}

		
	// ======== Game State setup ======== //
	game_state->init();
	

	// ======== Input Handler setup ======== //
	window_manager->register_input_handler(*input_handler);
	game_state->register_input_handler(*input_handler);
		// TODO: here you set up all other classes that should read player inputs


	// ======== Renderer setup ======== //
	fprintf(stdout, "Beginning renderer...\n");
	master_renderer->register_game_state(*game_state);
	if (master_renderer->init() != 0) {
		fprintf(stderr, "Error: Could not initialise renderer.");
		return 1;
	}


	// ======== Main Event Loop ======== //
	fprintf(stdout, "Beginning main loop...\n");
	while (!(window_manager->ShouldWindowClose())) {
		master_renderer->draw();
		window_manager->update();
		window_manager->swapBuffers();
		glfwPollEvents();
	}


	// ======== Finish ======== //
	master_renderer->finish();

	return 0;
}