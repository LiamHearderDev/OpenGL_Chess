#define GLFW_INCLUDE_NONE

#include <array>
#include <iostream>
#include <cstdint>
#include <fstream>
#include <filesystem>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "engine/window/WindowManager.h"
#include "engine/rendering/MasterRenderer.h"
#include "engine/input/InputHandler.h"
#include "engine/gamestate/GameState.h"
#include "engine/logger/Logger.h"


int main(int arc, char** argv) {
	fprintf(stdout, "Beginning OpenGL_Chess\n\n");
	
	// ======== Generate Engine Services ======== //
	std::shared_ptr<Logger> 		logger 			= std::make_shared<Logger>(argv);
	std::shared_ptr<WindowManager>	window_manager 	= std::make_shared<WindowManager>();
	std::shared_ptr<MasterRenderer> master_renderer = std::make_shared<MasterRenderer>();
	std::shared_ptr<InputHandler> 	input_handler 	= std::make_shared<InputHandler>();
	std::shared_ptr<GameState>		game_state 		= std::make_shared<GameState>();

	EngineContext engine_context {
		game_state.get(),
		input_handler.get(),
		master_renderer.get(),
		window_manager.get(),
		logger.get()
	};

	window_manager->register_engine_context(engine_context);
	master_renderer->register_engine_context(engine_context);
	input_handler->register_engine_context(engine_context);
	game_state->register_engine_context(engine_context);

	// ======== Window setup ======== //
	logger->LogMessage("Initialising Window Manager...	");
	WindowManager::init();
	logger->LogMessage("finished.\n");

	logger->LogMessage("Creating window...		");
	int window_status = window_manager->createWindow(800, 800);
	if (window_status == 1) {
		logger->LogMessage("Error: Cannot open multiple windows.\n");
		return 1;
	} else if (window_status == 2) {
		logger->LogMessage("Error: Failed to create GLFW window.\n");
		return 1;
	}
	logger->LogMessage("finished.\n");

	logger->LogMessage("Initialising GLAD...		");
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		logger->LogMessage("Error: Failed to initialize GLAD.\n");
		return 1;
	}
	logger->LogMessage("finished.\n");
	
	
	
	// ======== Game State setup ======== //
	logger->LogMessage("Initialising Game State...	");
	game_state->init();
	logger->LogMessage("finished.\n");


	// ======== Renderer setup ======== //
	logger->LogMessage("Initialising renderer...	");
	if (master_renderer->init() != 0) {
		logger->LogMessage("Error: Could not initialise renderer.\n");
		return 1;
	}
	logger->LogMessage("finished.\n");


	// ======== Main Event Loop ======== //
	logger->LogMessage("Beginning main loop...		");
	while (!(window_manager->ShouldWindowClose())) {
		master_renderer->draw();
		window_manager->update();
		window_manager->swapBuffers();
		glfwPollEvents();
	}
	logger->LogMessage("finished.\n");


	logger->LogMessage("Success!\n");
	return 0;
}