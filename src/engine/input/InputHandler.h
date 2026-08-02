#pragma once

#include <glm/glm.hpp>
#include "delegates/MulticastDelegate.h"
#include "engine/input/InputData.h"
#include <engine/EngineContext.h>


// Forward Declarations
class GLFWwindow;


/** A class for handling all user inputs on a given window. */
class InputHandler {
    EngineContext engine;
    GLFWwindow* window;

public:
    InputHandler() { init(); };
    ~InputHandler() { finish(); };

    /** Registers the engine context with the input handler. */
    void register_engine_context(EngineContext new_engine) { engine = new_engine; }

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

    /** Registers a GLFWwindow with the input handler, allowing it to receive input events from said window. */
    void register_window(GLFWwindow* window);

    /** Converts a screen space position to a world space position. */
    void screen_to_world_space(double screen_x, double screen_y, float& world_x, float& world_y, float& world_z);
    void screen_to_world_space(double screen_x, double screen_y, glm::vec3& world);
    void screen_to_world_space(glm::dvec2 screen, float& world_x, float& world_y, float& world_z);
    void screen_to_world_space(glm::dvec2 screen, glm::vec3& world);
    
    /** Returns whether the user is currently dragging the mouse. */
    bool get_is_dragging() const;

    /** Returns the current cursor position in screen space. */
    glm::dvec2 get_cursor_position() const;

private:
    void init();
    void finish();
};