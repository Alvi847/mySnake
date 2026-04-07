#include <game.hpp>
#include <textureManager.hpp>
#include <snake.hpp>
#include <gameBoard.hpp>
#include <iostream>
#include <inputMappings.hpp>
#include <fruit.hpp>

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
		
	// Modo con tablero	
	//data.board = new GameBoard(data.textureManager, snakeIndex, this, RESOURCES_PATH "levels/level1.json");
	
	// DIMENSIONES DEL TABLERO

	int rightMargin = GetScreenWidth();
	int bottomMargin = GetScreenHeight();
	Rectangle boardDimensions;
	{
		boardDimensions.x = floor(0);
		boardDimensions.y = floor(300);
		boardDimensions.width = floor((rightMargin - boardDimensions.x) / CELL_SIZE);
		boardDimensions.height = floor((bottomMargin - boardDimensions.y) / CELL_SIZE);
	}

	// Modo sin tablero
	data.board = new GameBoard(data.textureManager, snakeIndex, this, boardDimensions);
		
	// Add player
	Vector2 playerPos{ (float) floor(data.board->getDimensions().x / 2), (float) floor(data.board->getDimensions().y / 2)};
		
	// Player 1

	// Controles del player 1
	InputMappings* mappings1 = new InputMappings;

	{
		mappings1->addMapping("right", KEY_RIGHT);
		mappings1->addMapping("left", KEY_LEFT);
		mappings1->addMapping("up", KEY_UP);
		mappings1->addMapping("down", KEY_DOWN);
	}

	
	Snake* player1 = new Snake(1, playerPos, 1, data.textureManager, Vector2{ 1, 0 }, snakeIndex, snakeRect, this, mappings1);
	
	data.players.push_back(player1);
	
	data.board->add(std::move(player1));
	
	player1->addBodyPieces(28);
	
	// Player 2
	
	// Controles del player 2
	InputMappings* mappings2 = new InputMappings;
	
	{
		mappings2->addMapping("right", KEY_D);
		mappings2->addMapping("left", KEY_A);
		mappings2->addMapping("up", KEY_W);
		mappings2->addMapping("down", KEY_S);
	}
	
	playerPos = Vector2{ (float) floor(data.board->getDimensions().x / 4), (float) floor(data.board->getDimensions().y / 4)};
	
	Snake* player2 = new Snake(1, playerPos, 1, data.textureManager, Vector2{ 1, 0 }, snakeIndex, snakeRect, this, mappings2);
	
	data.players.push_back(player2);
	
	data.board->add(std::move(player2));
	
	player2->addBodyPieces(2);
}

void Game::gameLoop(float deltaTime) {
	//data.textureManager.draw(data.backgroundIndex);

	trySpawnFruit(deltaTime);

	data.board->update(deltaTime);

	data.board->processAttacks();

	draw();

	nullDeadPlayers();
	data.board->removeDead();

	if(ended())
		end();
}

bool Game::ended(){
	return data.deadPlayers == data.players.size();
}

void Game::end(){}

void Game::trySpawnFruit(float deltaTime){
	data.fruitSpawnTimer += deltaTime;

	if(data.fruitCounter < MAX_FRUIT_COUNT && data.fruitSpawnTimer >= FRUIT_SPAWN_COUNTDOWN && rng(1) < FRUIT_PROBABILITY){

		data.fruitSpawnTimer = 0.f;

		Vector2 fruitPos = Vector2{(float) floor(rng(data.board->getDimensions().x)), (float) floor(rng(data.board->getDimensions().y))};

		if(!data.board->isCellEmpty(fruitPos.x, fruitPos.y)){

			Rectangle fruitRect{ATLAS_TILE_WIDTH * 6, ATLAS_TILE_HEIGHT * 3,
				ATLAS_TILE_WIDTH, ATLAS_TILE_HEIGHT};

			Fruit* fruit = new Fruit(fruitPos, data.textureManager, 0, fruitRect, this, 1); // TODO: atlasIndex hardcodeado, pero eso está fatal

			data.board->add(fruit);

			data.fruitCounter++;
		}
	}
}

float Game::rng(int maxInclusive){
	return  static_cast <float> (rand()) / static_cast <float> (RAND_MAX/maxInclusive);
}

void Game::nullDeadPlayers(){
	for(int i = 0; i < data.players.size(); i++){
		GameObject** a = &data.players[i];
		if(*a != nullptr && !(*a)->isAlive()){
			*a = nullptr;
			data.deadPlayers++;
		}
	}
}

/*void Game::spriteRemoved(int index) {
	data.board.spriteRemoved(index);
}*/

bool Game::canMoveToPos(int x, int y) const{
	return data.board->canMoveToPos(x, y);
}

void Game::fruitEaten(){
	data.fruitCounter--;
}

Vector2 Game::movedToNewCell(GameObject* obj, int newX, int newY, int oldX, int oldY){
	return data.board->moveObjToNewCell(obj, newX, newY, oldX, oldY);
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

Vector2 Game::getBoardDimensions() const{
	return data.board->getDimensions();
}

Game::~Game(){
	delete data.board;
	data.board = nullptr;
}