#version 330 core
layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec2 vTexCoord;

uniform mat4 model_mat;
out vec2 TexCoord;

void main()
{
    gl_Position = model_mat * vec4(vPosition, 1.0);
    TexCoord = vTexCoord;
}