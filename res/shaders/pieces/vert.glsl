#version 330 core
layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec2 vTexCoord;

uniform mat4 model_mat;
uniform vec2 sprite_scale;
uniform vec2 sprite_offset;
out vec2 TexCoord;

void main()
{
    gl_Position = model_mat * vec4(vPosition, 1.0);
    TexCoord = sprite_offset + vTexCoord * sprite_scale;
}