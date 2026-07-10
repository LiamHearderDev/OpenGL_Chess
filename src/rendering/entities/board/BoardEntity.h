#ifndef BOARD_ENTITY_H
#define BOARD_ENTITY_H

#include <rendering/entities/Entity.h>

class BoardEntity : public Entity {
    void init_shader_paths() override;

public:
    BoardEntity(renderable_data&& render_data) :
        Entity(std::move(render_data)) {}
};

#endif // BOARD_ENTITY_H