#ifndef PIECE_MATERIAL_H
#define PIECE_MATERIAL_H

#include <rendering/materials/BaseMaterial.h>

class PieceMaterial : public BaseMaterial {
    unsigned int player_team;
    unsigned int piece_id;

public:
    PieceMaterial(unsigned int player_team, unsigned int piece_id) :
        BaseMaterial("pieces/vert.glsl", "pieces/frag.glsl"),
        player_team(player_team),
        piece_id(piece_id) {}

    ~PieceMaterial() { finish(); }

    void set_uniform_data() override;
};


#endif // PIECE_MATERIAL_H