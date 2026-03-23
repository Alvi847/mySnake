#pragma once

#include <memory>
#include <raylib.h>
#include <raymath.h>
#include <gameObjectContainer.hpp>

constexpr float GRAVITY = 9.8;

class GameObject;
class Snake;
class TextureManager;

class Game {
public:

	Game(TextureManager& textureManager);

	void initGame();
	void gameLoop(float deltaTime);
	//void spriteRemoved(int index);

	//void summonAttack(std::shared_ptr<GameObject> attack);
	bool debug();

	//void summonEnemy(bool onPlayer = true, Vector2 pos = Vector2());

    ~Game();

private:
	struct GameData {
		GameObjectContainer container;
		TextureManager& textureManager;
		int backgroundIndex = 0;
		GameObject* player = nullptr;

		GameData(GameObjectContainer c, TextureManager& sm)
			: container(std::move(c)), textureManager(sm){
		}

	};

	GameData data;
	bool debugMode = true;
};