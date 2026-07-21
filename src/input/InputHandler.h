#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <glm/glm.hpp>

#include "delegates/MulticastDelegate.h"
#include "input/InputData.h"


// Forward Declarations
class GLFWwindow;


/** A class for handling all user inputs on a given window. */
class InputHandler {
    GLFWwindow* window;

public:
    InputHandler() {};
    ~InputHandler() {};

    // ====== Callback variables ====== //

    // Mouse Variables (Dragging)
    bool isDragging = false;
    double last_x = 0.0;
    double last_y = 0.0;


    // ====== Delegates ====== //
    
    DECLARE_MULTICAST_DELEGATE(on_mouse_button, mouse_click_data /* data */);
    DECLARE_MULTICAST_DELEGATE(on_mouse_pressed, mouse_click_data /* data */);
    DECLARE_MULTICAST_DELEGATE(on_mouse_released, mouse_click_data /* data */);
    DECLARE_MULTICAST_DELEGATE(on_mouse_move, double /* position x */, double /* position y*/);
    

    // ====== Functions ====== //

    void register_window(GLFWwindow& window);
    void screen_to_world_space(double screen_x, double screen_y, float* world_x, float* world_y, float* world_z);
    
    bool get_is_dragging() const;
    glm::dvec2 get_cursor_position() const;
};

#endif // INPUT_HANDLER_H