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


int main(int arc, char** argv) {
	// Creating output log file...
	std::filesystem::path filepath = std::string(argv[0]) + "/../../out/log.txt";
	std::ofstream output_file(filepath);
	
	output_file << "Beginning OpenGL_Chess\n\n";
	

	
	// ======== Generate Engine Services ======== //
	output_file << "Creating engine services...	";
	std::shared_ptr<WindowManager>	window_manager 	= std::make_shared<WindowManager>();
	std::shared_ptr<MasterRenderer> master_renderer = std::make_shared<MasterRenderer>();
	std::shared_ptr<InputHandler> 	input_handler 	= std::make_shared<InputHandler>();
	std::shared_ptr<GameState>		game_state 		= std::make_shared<GameState>();

	std::unique_ptr<EngineContext> engine_context = std::make_unique<EngineContext>(
		*game_state,
		*input_handler,
		*master_renderer,
		*window_manager
		);

	window_manager->register_engine_context(*engine_context);
	master_renderer->register_engine_context(*engine_context);
	input_handler->register_engine_context(*engine_context);
	game_state->register_engine_context(*engine_context);
	output_file << "finished.\n";

	// ======== Window setup ======== //
	output_file << "Initialising Window Manager...	";
	WindowManager::init();
	output_file << "finished.\n";

	output_file << "Creating window...		";
	window_manager->createWindow(800, 800);
	output_file << "finished.\n";

	output_file << "Initialising GLAD...		";
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		output_file << "Error: Failed to initialize GLAD." << std::endl;
		return 1;
	}
	output_file << "finished.\n";
	
	
	// ======== Game State setup ======== //
	output_file << "Initialising Game State...	";
	game_state->init();
	output_file << "finished.\n";


	// ======== Renderer setup ======== //
	output_file << "Initialising renderer...	";
	if (master_renderer->init() != 0) {
		output_file << "Error: Could not initialise renderer." << std::endl;
		return 1;
	}
	output_file << "finished.\n";


	// ======== Main Event Loop ======== //
	output_file << "Beginning main loop...		";
	while (!(window_manager->ShouldWindowClose())) {
		master_renderer->draw();
		window_manager->update();
		window_manager->swapBuffers();
		glfwPollEvents();
	}
	output_file << "finished.\n";

	
	// ======== Finish ======== //
	output_file << "Finishing renderer...		";
	master_renderer->finish();
	output_file << "finished.\n";

	// end output log
	output_file.close();

	output_file << "Success!\n";
	return 0;
}