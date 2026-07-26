#include "MasterRenderer.h"

#include <gamestate/GameState.h>
#include <input/InputHandler.h>
#include "components/texture_loader/TextureLoader.h"

#include "entities/derived/pieces/PieceEntity.h"
#include "entities/derived/board/BoardEntity.h"

#include <glad/glad.h>
#include <array>
#include <exception>
#include <iostream>


int MasterRenderer::init()
{
	// Just in case there's something left over.
    renderables.clear();

	// Reset the screen.
	glClearColor(0.0, 0.0, 0.0, 0.0); // Draw black background

	// Try to create the scene
	try {

		// Create the board
		renderables.emplace_back(std::make_unique<BoardEntity>());

		// Create all pieces
		for (int i = 0; i < game_state->game_board->get_pieces_count(); i++) {
			UniquePieceData data = game_state->game_board->get_piece_data(static_cast<PieceNames>(i));
			renderables.emplace_back(std::make_unique<PieceEntity>(
				data.name, std::move(data.positions), *(game_state->game_board), *input_handler)
			);
		}

	} catch (const std::bad_alloc& e) {
		fprintf(stderr, "std::bad_alloc during renderer init: %s\n", e.what());
		return 1;
	} catch (const std::exception& e) {
		fprintf(stderr, "Exception during renderer init: %s\n", e.what());
		return 1;
	}

	// Initialise all entities
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
		element->update();
		element->render();
	}
}

void MasterRenderer::finish()
{
	renderables.clear();
}

void MasterRenderer::register_game_state(GameState& new_game_state)
{
	game_state = &new_game_state;
}

void MasterRenderer::register_input_handler(InputHandler &new_input_handler)
{
	input_handler = &new_input_handler;
}
