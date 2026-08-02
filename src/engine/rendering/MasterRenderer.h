#pragma once

#include <glm/glm.hpp>
#include <engine/rendering/renderables/base/RenderableBase.h>
#include <engine/EngineContext.h>

#include <vector>
#include <string>
#include <memory>


/** The Master Renderer handles and manages all renderable entities in the scene. */
class MasterRenderer {
    EngineContext engine;

    std::vector<std::unique_ptr<RenderableBase>> renderables;

public:
    MasterRenderer() {}
    ~MasterRenderer() { finish(); }

    int init();
    void draw();
    void finish();

    void register_engine_context(EngineContext new_engine) { engine = new_engine; }
};