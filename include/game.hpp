#pragma once

#include <memory>
#include <raylib.h>
#include <raymath.h>

const int ATLAS_TILE_WIDTH = 8; // Anchura en pixeles de una tile del atlas
const int ATLAS_TILE_HEIGHT = 8; // Altura en pixeles de una tile del atlas
const int ATLAS_SCALE_FACTOR = 4; // Factor de escalado de las tiles del atlas

constexpr float GRAVITY = 9.8;
const int CELL_SIZE = ATLAS_SCALE_FACTOR * ATLAS_TILE_WIDTH;
const int MOVEMENT_FREQUENCY = 60;


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

	//void summonEnemy(bool onPlayer = true, Vector2 pos = Vector2());

    ~Game();

private:
	struct GameData {
		TextureManager& textureManager;
		int backgroundIndex = 0;
		GameObject* player = nullptr;
		GameBoard* board = nullptr;

		GameData(TextureManager& sm)
			: textureManager(sm){
		}

	};

	GameData data;
	bool debugMode = true;
};