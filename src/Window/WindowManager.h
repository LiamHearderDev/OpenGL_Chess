#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H
/// A class used to managed open windows.

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>

class WindowManager {
    GLFWwindow* window;
    double delta_time = 0.0;

public:
    static void init();

    WindowManager() = default;

    void createWindow(unsigned int width, unsigned int height);
    bool ShouldWindowClose();
    void update();
    void swapBuffers();
    double getDeltaTime();    
};

#endif //WINDOW_MANAGER_H