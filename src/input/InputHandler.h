#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "delegates/MulticastDelegate.h"


/** Data that's passed to mouse click input events. */
struct mouse_click_data {
    int button;
    int action;
    int mods;
    glm::dvec2 cursor_position;
};


/** A class for handling all user inputs on a given window. */
class InputHandler {
    GLFWwindow* window;


    // ====== Callback variables ====== //

    // Mouse Variables (Dragging)
    bool isDragging = false;
    double last_x = 0.0;
    double last_y = 0.0;


public:
    InputHandler() {};
    ~InputHandler() {};


    // ====== Delegates ====== //
    
    DECLARE_MULTICAST_DELEGATE(on_mouse_button, mouse_click_data /* data */);
    DECLARE_MULTICAST_DELEGATE(on_mouse_move, glm::dvec2 /* position*/);


    // ====== Functions ====== //

    void register_window(GLFWwindow& window);
    void screen_to_world_space(double screen_x, double screen_y, float* world_x, float* world_y, float* world_z);
};

#endif // INPUT_HANDLER_H