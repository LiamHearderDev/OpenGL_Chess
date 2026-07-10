#include "MasterRenderer.h"

#include "components/TextureLoader.h"
#include "rendering/entities/pieces/PieceEntity.h"
#include "rendering/materials/pieces/PieceMaterial.h"
#include "rendering/entities/board/BoardEntity.h"

#include <glad/glad.h>
#include <array>
#include <exception>
#include <iostream>


int MasterRenderer::init()
{
    finish();

	// 1. Reset the screen.
	glClearColor(0.0, 0.0, 0.0, 0.0); // Draw black background

	game_board = std::make_unique<GameBoard>();

	// 2. Handle all the new entities being rendered.
	try {
		renderable_data board_data = {
			board_vertices,
			std::vector<unsigned int>{0,1,3, 1,2,3}
		};

		entities.emplace_back(std::make_unique<BoardEntity>(std::move(board_data)));

		for (int i = 0; i < game_board->get_pieces_count(); i++){
			UniquePieceData data = game_board->get_piece_data(static_cast<PieceNames>(i));
			
			for (const PiecePositions& pos : data.positions){
				entities.emplace_back(std::make_unique<PieceEntity>(data.name, pos));
			}
			
		}


	} catch (const std::bad_alloc& e) {
		fprintf(stderr, "std::bad_alloc during renderer init: %s\n", e.what());
		return 1;
	} catch (const std::exception& e) {
		fprintf(stderr, "Exception during renderer init: %s\n", e.what());
		return 1;
	}

	// 3. Initialise new entities
	for (const auto& element : entities) {
		element->init();
	}

	return 0;
}

void MasterRenderer::draw()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (const auto& element : entities) {
		element->render();
	}
}

void MasterRenderer::finish()
{
	entities.clear();
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
