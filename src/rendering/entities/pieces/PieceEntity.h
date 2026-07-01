#ifndef PIECE_ENTITY_H
#define PIECE_ENTITY_H

#include <rendering/entities/Entity.h>

class PieceEntity : public Entity {
    unsigned int player_team;
    unsigned int piece_id;
public:
    PieceEntity(std::string name, renderable_data&& render_data, unsigned int player_team, unsigned int piece_id) :
        Entity(name, std::move(render_data)), player_team(player_team), piece_id(piece_id) {}

    void setup_attrib_pointers() override;
};

#endif // PIECE_ENTITY_H