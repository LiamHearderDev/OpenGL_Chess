#include <rendering/materials/pieces/PieceMaterial.h>
#include "PieceMaterial.h"

#include <glad/glad.h>

void PieceMaterial::set_uniform_data()
{
    unsigned int player_team_loc = glGetUniformLocation(shader_program, "team");
    unsigned int piece_id_loc = glGetUniformLocation(shader_program, "piece_id");
    glUniform1ui(player_team_loc, player_team);
    glUniform1ui(piece_id_loc, piece_id);
}