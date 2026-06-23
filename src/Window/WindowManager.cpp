#include "WindowManager.h"
#include <cstdio>

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void WindowManager::init()
{
    glfwInit();
    if (!glfwInit())
	{
		fprintf(stderr, "Error: Failed to initialise GLFW.\n");
		return;
	}
	glfwSetErrorCallback(error_callback);

	// Add window hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Needed for apple devices, as only forward compatability is supported
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

void WindowManager::createWindow(unsigned int width, unsigned int height)
{
	// Create Window
	window = glfwCreateWindow(width, height, "OpenGL Chess", NULL, NULL);
	if (NULL == window) {
		fprintf(stderr, "Error: Failed to create GLFW window.\n");
		glfwTerminate();
		return;
	}

	// Activate the GLFW context
	glfwMakeContextCurrent(window);
}



bool WindowManager::ShouldWindowClose()
{
    return (window) ? (glfwWindowShouldClose(window)) : (true);
}

void WindowManager::update()
{
    // Update delta time
    static double lastTime = 0.0;
    double time = glfwGetTime();
    if (lastTime != 0.0) {
        delta_time = time - lastTime;
    }
    lastTime = time;

    glfwPollEvents();
}

void WindowManager::swapBuffers()
{
    glfwSwapBuffers(window);
}

void WindowManager::registerFramebufferSizeCallback(GLFWframebuffersizefun callback)
{
	glfwSetFramebufferSizeCallback(window, callback);
}

double WindowManager::getDeltaTime()
{
    return delta_time;
}
