#version 330 core
layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec2 vTexCoord;
layout (location = 2) in bool team;
layout (location = 3) in int piece_id;

out vec2 TexCoord;

void main()
{
    gl_Position = vec4(vPosition.x, vPosition.y, vPosition.z, 1.0);
    TexCoord = vTexCoord;
}