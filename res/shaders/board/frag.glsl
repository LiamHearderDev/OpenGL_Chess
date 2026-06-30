#version 330 core

out vec4 FragColor;
in vec2 TexCoord;
uniform sampler2D screenTexture;

void main()
{
    vec4 green = vec4(0.356f, 0.552f, 0.408f, 1.0f);
    vec4 white = vec4(1.0f, 1.0f, 1.0f, 1.0f);

    if ( int(floor(TexCoord.y * 7)) % 2 == 0) {
        if ( int(floor(TexCoord.x * 7)) % 2 == 0) {
            FragColor = white;
        } else {
            FragColor = green;
        }
    } else {
        if ( int(floor(TexCoord.x * 7)) % 2 == 0) {
            FragColor = green;
        } else {
            FragColor = white;
        }
    }

    //FragColor = texture(screenTexture, TexCoord);
}