#pragma once

#include <engine/EngineContext.h>
#include <glm/glm.hpp>

class GLFWwindow;

/// A class used to managed open windows.
class WindowManager {
    EngineContext* engine;

    GLFWwindow* window;
    double delta_time = 0.0;

public:    

    // Functions

    static int init();

    WindowManager() {}
    ~WindowManager() {}

    int createWindow(unsigned int width, unsigned int height);

    bool ShouldWindowClose();
    void update();
    void swapBuffers();
    double getDeltaTime();

    void register_engine_context(EngineContext& new_engine) { engine = &new_engine; }

    glm::ivec2 getFrameBufferSize();
};