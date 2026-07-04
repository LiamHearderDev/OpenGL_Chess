#ifndef PIECE_ENTITY_H
#define PIECE_ENTITY_H

#include <rendering/entities/Entity.h>

class PieceEntity : public Entity {
    unsigned int player_team;
    unsigned int piece_id;

    const float desired_scale = 1.f/8.f;
public:
    PieceEntity(std::string name, renderable_data&& render_data, unsigned int player_team, unsigned int piece_id) :
        Entity(name, std::move(render_data)),
        player_team(player_team),
        piece_id(piece_id)
        {
            set_scale(desired_scale);
        }

    void setup_attrib_pointers() override;
    void set_uniform_data() override;
};

#endif // PIECE_ENTITY_H