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
		renderables.emplace_back(std::make_unique<BoardEntity>());

		for (int i = 0; i < game_board->get_pieces_count(); i++){
			UniquePieceData data = game_board->get_piece_data(static_cast<PieceNames>(i));
			renderables.emplace_back(std::make_unique<PieceEntity>(data.name, std::move(data.positions)));
		}


	} catch (const std::bad_alloc& e) {
		fprintf(stderr, "std::bad_alloc during renderer init: %s\n", e.what());
		return 1;
	} catch (const std::exception& e) {
		fprintf(stderr, "Exception during renderer init: %s\n", e.what());
		return 1;
	}

	// 3. Initialise new entities
	for (const auto& element : renderables) {
		element->init();
	}

	return 0;
}

void MasterRenderer::draw()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (const auto& element : renderables) {
		element->render();
	}
}

void MasterRenderer::finish()
{
	renderables.clear();
}
