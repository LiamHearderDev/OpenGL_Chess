#ifndef PIECE_MATERIAL_H
#define PIECE_MATERIAL_H

#include <rendering/materials/BaseMaterial.h>

class PieceMaterial : public BaseMaterial {

    const std::string vert_path = "pieces/vert.glsl";
    const std::string frag_path = "pieces/frag.glsl";

    bool player_team;
    unsigned int piece_id;

public:
    PieceMaterial(bool player_team, unsigned int piece_id) :
        player_team(player_team), piece_id(piece_id), BaseMaterial(vert_path, frag_path) {}

    ~PieceMaterial() { finish(); }
};


#endif // PIECE_MATERIAL_H