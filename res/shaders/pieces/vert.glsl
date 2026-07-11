#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in mat4 aInstanceMatrix;

uniform vec2 sprite_scale;
uniform vec2 sprite_offset;
out vec2 TexCoord;

void main()
{
    gl_Position = aInstanceMatrix * vec4(aPos, 1.0);
    TexCoord = sprite_offset + aTexCoord * sprite_scale;
}