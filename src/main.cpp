#define GLFW_INCLUDE_NONE

#include <array>
#include <iostream>
#include <cstdint>
#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window/WindowManager.h"
#include "rendering/MasterRenderer.h"

WindowManager window_manager{};
MasterRenderer master_renderer{};

constexpr auto squareVertices = std::array{
    -0.5f, 0.5f, 0.0f,  // Top-left
    0.5f, 0.5f, 0.0f,   // Top-right
    0.5f, 0.5f, 0.0f,   // Top-right
    0.5f, -0.5f, 0.0f,  // Bottom-right
    0.5f, -0.5f, 0.0f,  // Bottom-right
    -0.5f, -0.5f, 0.0f, // Bottom-left
    -0.5f, -0.5f, 0.0f, // Bottom-left
    -0.5f, 0.5f, 0.0f   // Top-left
};

int main() {

	// ======== Window setup ======== //
	WindowManager::init();
	window_manager.createWindow(512, 512);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		fprintf(stderr, "Error: Failed to initialize GLAD.\n");
		return 1;
	}


	// ======== OpenGL setup ======== //
	master_renderer.init();
	

	// ======== Main Event Loop ======== //
	while (!(window_manager.ShouldWindowClose())) {
		master_renderer.draw();
		window_manager.update();
		window_manager.swapBuffers();
		glfwPollEvents();
	}

	master_renderer.finish();

	return 0;
}

