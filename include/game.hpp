#pragma once

#include <memory>
#include <raylib.h>
#include <raymath.h>
#include <vector>

constexpr int ATLAS_TILE_WIDTH = 8; // Anchura en pixeles de una tile del atlas
constexpr int ATLAS_TILE_HEIGHT = 8; // Altura en pixeles de una tile del atlas
constexpr int ATLAS_SCALE_FACTOR = 4; // Factor de escalado de las tiles del atlas

constexpr float GRAVITY = 9.8;
constexpr int CELL_SIZE = ATLAS_SCALE_FACTOR * ATLAS_TILE_WIDTH;
constexpr int MOVEMENT_FREQUENCY = 60;

constexpr float FRUIT_PROBABILITY = 0.1; 
constexpr float FRUIT_SPAWN_COUNTDOWN = 2.0;
constexpr int MAX_FRUIT_COUNT = 7;


class GameObject;
class Snake;
class TextureManager;
class GameBoard;

class Game {
public:

	Game(TextureManager& textureManager);

	void initGame();
	void gameLoop(float deltaTime);
	//void spriteRemoved(int index);

	//void summonAttack(std::shared_ptr<GameObject> attack);
	bool debug();

	void draw();

	void queueDrawObject(GameObject* obj);

	bool canMoveToPos(int x, int y) const;

	Vector2 movedToNewCell(GameObject* obj, int newX, int newY, int oldX, int oldY);

	void addObj(GameObject* obj);

	Vector2 getBoardDimensions() const;

	void fruitEaten();

	/**
	 * Game end conditions
	 */
	bool ended();

	//void summonEnemy(bool onPlayer = true, Vector2 pos = Vector2());

    ~Game();

private:

	void nullDeadPlayers();

	void trySpawnFruit(float deltaTime);

	float rng(int maxInclusive);

	/**
	 * Terminate the game
	 */
	void end();

	struct GameData {
		TextureManager& textureManager;
		int backgroundIndex = 0;
		std::vector<GameObject*> players;
		int deadPlayers = 0;
		GameBoard* board = nullptr;
		float fruitSpawnTimer = 0.f;
		int fruitCounter = 0;

		GameData(TextureManager& sm)
			: textureManager(sm){
		}

	};

	GameData data;
	bool debugMode = true;
};