#include "MasterRenderer.h"
#include "components/TextureLoader.h"

#include <glad/glad.h>
#include <array>
#include <iostream>





int MasterRenderer::init()
{
	// 1. Reset the screen.
	glClearColor(0.0, 0.0, 0.0, 0.0); // Draw black background

	// 2. Handle all the new entities being rendered.

	// TODO: Make this a different function somewhere.
	Entity* square = new Entity("board", board_data);
	entities.push_back(square);

	Entity* pawn = new PieceEntity("white pawn", pawn_data, 0, 0);
	entities.push_back(pawn);

	// 3. Initialise new entities
	for (Entity* element : entities) {
		element->init();
	}

	return 0;
}

void MasterRenderer::draw()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(sizeof(squareVertices)/3));
	//glDrawArrays(GL_LINE_LOOP, 0, static_cast<GLsizei>(board_vertices.size()));
	
	//const std::array<uint64_t, 12> pieces = game_board.getPieces();

	for (Entity* element : entities) {
		element->render();
	}
}

void MasterRenderer::finish()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
}


// unsigned int MasterRenderer::loadTexture(const char* filepath)
// {
// 	int width, height, channels;
// 	stbi_set_flip_vertically_on_load(true);

// 	// Load the image using stb
// 	unsigned char* data = stbi_load(filepath, &width, &height, &channels, 4);

// 	if (!data) {
// 		fprintf(stderr, "Error: Failed to load texture at [%s]", filepath);
// 		return 0;
// 	}

// 	GLuint texture;
// 	glGenTextures(1, &texture);
// 	glBindTexture(GL_TEXTURE_2D, texture);
// 	glTexImage2D(
// 		GL_TEXTURE_2D, 0, GL_RGBA, 
// 		width, height, 0, GL_RGBA, 
// 		GL_UNSIGNED_BYTE, data
// 	);
// 	glGenerateMipmap(GL_TEXTURE_2D);

// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

// 	// Free the stb image memory
// 	stbi_image_free(data);
//     return texture;
// }

void MasterRenderer::drawPiece()
{

}
