#ifndef RENDERABLE_BASE_H
#define RENDERABLE_BASE_H

class RenderableBase {
protected:
    virtual void setup_attrib_pointers() = 0;

    /** Sets the variable `material` to be a valid pointer, i.e., used for material initialisation in `init()`. */
    virtual void init_material() = 0;

    /** Initialises the file paths for shaders. Designed to be overriden for derived classes. */
    virtual void init_shader_paths() = 0;

public:
    /** Initialisation Function. Must be manually called after construction. */
    virtual void init() = 0;

    /** A function used to update the renderable's data. */
    virtual void update() = 0;

    /** A function used to clean up and finish a class, getting ready for destruction. */
    virtual void finish() = 0;

    /** Render the entity. This should be called every frame, and only after initialisation. */ 
    virtual void render() = 0;

    /** Sets uniform variable data used by shaders. */
    virtual void set_uniform_data() = 0;
};

#endif // RENDERABLE_BASE_H