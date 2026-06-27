#include "TextureLoader.h"
#include <glad/glad.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

unsigned int TextureLoader::loadTexture(const char *filepath)
{
    int width, height, channels;
	stbi_set_flip_vertically_on_load(true);

	// Load the image using stb
	unsigned char* data = stbi_load(filepath, &width, &height, &channels, 4);

	if (!data) {
		fprintf(stderr, "Error: Failed to load texture at [%s]", filepath);
		return 0;
	}

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RGBA, 
		width, height, 0, GL_RGBA, 
		GL_UNSIGNED_BYTE, data
	);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Free the stb image memory
	stbi_image_free(data);
    return texture;
}
