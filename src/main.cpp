#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>

#include <array>
#include <iostream>
#include <cstdint>


int main() {

	// Initialize GLFW
	// TODO: This will all be abstracted out into its own class
	if (!glfwInit())
	{
		fprintf(stderr, "Error: Failed to initialise GLFW.");
		return 1;
	}
	glfwSetErrorCallback(error_callback);

	// Add window hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Create Window
	GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGL Chess", NULL, NULL);
	if (NULL == window) {
		fprintf(stderr, "Error: Failed to create GLFW window.");
		glfwTerminate();
		return 1;
	}

	// Activate the GLFW context
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK){
		fprintf(stderr, "Error: Failed to initialise GLEW.");
		return 1;
	}

	// TODO: Add OpenGL setup

	
	// Connect frame buffer size changed callback
	glfwSetFramebufferSizeCallback(window, OnFramebufferSizeChanged);

	// Event Loop
	while (false == glfwWindowShouldClose(window)) {
		render(window);
		glfwPollEvents();
	}

	// Finish up OpenGL
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	return 0;
}

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void OnFramebufferSizeChanged(GLFWwindow *window, int32_t width, int32_t height) {
	glViewport(0, 0, width, height);
	render(window);
}

void render(GLFWwindow *window){
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	return;
}
