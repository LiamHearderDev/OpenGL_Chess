#ifndef PIECE_MATERIAL_H
#define PIECE_MATERIAL_H

#include <rendering/materials/BaseMaterial.h>

class PieceMaterial : public BaseMaterial {

public:
    PieceMaterial(std::string vert_file_path, std::string frag_file_path) :
        BaseMaterial(vert_file_path, frag_file_path, "chess/piece_spritesheet.png") {}

    ~PieceMaterial() { finish(); }
};


#endif // PIECE_MATERIAL_H