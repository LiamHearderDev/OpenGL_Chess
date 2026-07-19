#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// Forward declarations
class InputHandler;

/// A class used to managed open windows.
class WindowManager {
    GLFWwindow* window;
    InputHandler* input_handler;

    double delta_time = 0.0;

public:    

    // Functions

    static void init();
    WindowManager() = default;

    void createWindow(unsigned int width, unsigned int height);
    void register_input_handler(InputHandler& new_input_handler);

    bool ShouldWindowClose();
    void update();
    void swapBuffers();
    double getDeltaTime();

    glm::ivec2 getFrameBufferSize();
};

#endif //WINDOW_MANAGER_H