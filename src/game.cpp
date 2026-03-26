#include <game.hpp>
#include <textureManager.hpp>
#include <snake.hpp>
#include <gameBoard.hpp>
#include <iostream>

Game::Game(TextureManager& textureManager):
	data(textureManager)
	{
		initGame();
	}

void Game::initGame() {

	data.textureManager.setGame(this);

	// Load texture atlas
	int snakeIndex = data.textureManager.loadTexture(RESOURCES_PATH "snake.png");
	Rectangle snakeRect{ATLAS_TILE_WIDTH, ATLAS_TILE_HEIGHT * 3,
		ATLAS_TILE_WIDTH, ATLAS_TILE_HEIGHT};
		
	data.board = new GameBoard(data.textureManager, snakeIndex, this, RESOURCES_PATH "levels/level1.json");
		
		
	// Add player
	Vector2 playerPos{ (float) floor(data.board->getDimensions().x / 2), (float) floor(data.board->getDimensions().y / 2)};
		
	
	Snake* player = new Snake(3, playerPos, 1, data.textureManager, Vector2{ 1, 0 }, snakeIndex, snakeRect, this);

	data.player = player;

	data.board->add(std::move(player));

	player->addBodyPieces(2);

	//GameObject* gameBoard = new GameBoard(data.textureManager, snakeIndex, this, 10, 10);

	//data.board.add(std::move(gameBoard));
}

void Game::gameLoop(float deltaTime) {
	//data.textureManager.draw(data.backgroundIndex);

	data.board->update(deltaTime);

	data.board->processAttacks();

	draw();

	//data.board.removeDead();
}

/*void Game::spriteRemoved(int index) {
	data.board.spriteRemoved(index);
}*/

bool Game::canMoveToPos(int x, int y) const{
	return data.board->canMoveToPos(x, y);
}

void Game::movedToNewCell(GameObject* obj, int newX, int newY, int oldX, int oldY){
	data.board->moveObjToNewCell(obj, newX, newY, oldX, oldY);
}

void Game::draw(){
	data.board->draw();
	data.board->draw();
}

void Game::addObj(GameObject* obj){
	if(obj != nullptr)
		data.board->add(obj);
}

void Game::queueDrawObject(GameObject* obj){
	data.board->queueDrawObject(obj);
}

bool Game::debug() {
	return debugMode;
}

Game::~Game(){
	delete data.board;
	data.board = nullptr;
	data.player = nullptr;
}