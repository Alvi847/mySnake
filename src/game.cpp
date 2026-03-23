#include <game.hpp>
#include <textureManager.hpp>
#include <gameObjectContainer.hpp>
#include <snake.hpp>
#include <gameBoard.hpp>

Game::Game(TextureManager& textureManager) :
	data(GameObjectContainer(), textureManager) {}

void Game::initGame() {

	data.textureManager.setGame(this);

	// Load texture atlas
	int snakeIndex = data.textureManager.loadTexture(RESOURCES_PATH "snake.png");
	Rectangle snakeRect{ATLAS_TILE_WIDTH * ATLAS_SCALE_FACTOR, ATLAS_TILE_HEIGHT * 3 * ATLAS_SCALE_FACTOR,
		ATLAS_TILE_WIDTH * ATLAS_SCALE_FACTOR, ATLAS_TILE_HEIGHT * ATLAS_SCALE_FACTOR};


	// Add player
	Vector2 playerPos{ 100.f, 100.f };

	// TODO: solucionar el problema que tengo al haber creado los AnimatableObjects
	GameObject* player = new Snake(3, playerPos, 100, data.textureManager, Vector2{ 1, 0 }, snakeIndex, snakeRect, this);

	data.player = player;

	data.container.add(std::move(player));


	GameObject* gameBoard = new GameBoard(data.textureManager, snakeIndex, this, 10, 10);

	data.container.add(std::move(gameBoard));
}

void Game::gameLoop(float deltaTime) {
	//data.textureManager.draw(data.backgroundIndex);

	data.container.update(deltaTime);

	data.container.processAttacks();

	//data.container.removeDead();
}

/*void Game::spriteRemoved(int index) {
	data.container.spriteRemoved(index);
}*/

bool Game::debug() {
	return debugMode;
}

Game::~Game(){
	data.container.free();
}