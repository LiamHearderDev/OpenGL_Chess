#ifndef BOARD_ENTITY_H
#define BOARD_ENTITY_H

#include <rendering/entities/base/Entity.h>

class BoardEntity : public Entity {
    void init_shader_paths() override;

public:
    BoardEntity() :
        Entity(
            renderable_data{
                std::vector<vertex_data>{
                    vertex_data{ {-0.5f, 0.5f, -1.f},      {0.f, 1.0f}    },  // Top-left
                    vertex_data{ {0.5f, 0.5f, -1.f},       {1.0f, 1.0f}   },  // Top-right
                    vertex_data{ {0.5f, -0.5f, -1.f},      {1.0f, 0.f}    },  // Bottom-right
                    vertex_data{ {-0.5f, -0.5f, -1.f},     {0.f, 0.f}     },  // Bottom-left
                },
                std::vector<unsigned int>{0,1,3, 1,2,3}
            }
        ) {}
    
    void update() override {}
};

#endif // BOARD_ENTITY_H