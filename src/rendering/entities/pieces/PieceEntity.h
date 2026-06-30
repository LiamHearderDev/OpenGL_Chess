#ifndef PIECE_ENTITY_H
#define PIECE_ENTITY_H

#include <rendering/entities/Entity.h>

class PieceEntity : public Entity {
    bool player_team;
    unsigned int piece_id;
public:
    PieceEntity(std::string name, renderable_data render_data, bool player_team, unsigned int piece_id) :
        Entity(name, render_data), player_team(player_team), piece_id(piece_id) {}

    void setup_attrib_pointers() override;
};


struct piece_vertex_data {
    glm::vec3 position;
    glm::vec2 texture_coordinate;
    bool player_team;
    unsigned int piece_id;
};


#endif // PIECE_ENTITY_H