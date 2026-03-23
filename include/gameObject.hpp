#pragma once
#include <cmath>
#include <raylib.h>
#include <raymath.h>
#include <textureManager.hpp>
#include <string>

class GameObject {
public:

	// Hice dos pq me daba pereza pensar yqs xd
	GameObject(int lives, Vector2 pos, float speed, TextureManager& textureManager, Vector2 direction, 
		int atlasIndex, Rectangle textureRect, Game* game) :
		lives(lives), position(pos), speed(speed), textureManager(textureManager), direction(direction), game(game),
		texture(atlasIndex, textureRect) {}
	
	GameObject(int lives, Vector2 pos, float speed, TextureManager& textureManager, Vector2 direction, 
	std::string texturePath, Rectangle textureRect, Game* game) :
		lives(lives), position(pos), speed(speed), textureManager(textureManager), direction(direction), game(game), 
		texture(textureManager.loadTexture(texturePath), textureRect){}

	virtual void move(Vector2 direction, float deltaTime);
	virtual void update(float deltaTime) = 0;

	//virtual bool receiveAttack(GameObject* attacker);

	virtual bool attack(GameObject* other);

	bool isAlive();
	void die();

	virtual void onDeath() {}

	// Sistema de colision AABB (Axis-Aligned Bounding Box)
	virtual bool isOnPosition(Vector2 other);

	Vector2 getDirectionToPos(Vector2 position);

	Vector2 getPos();

	bool isInmune();

	virtual ~GameObject() = default;

protected:
	virtual void draw();
	//virtual void debugDraw();

	int lives;
	Vector2 position;
	float speed;
	TextureManager& textureManager;
	Vector2 direction;
	
	struct TextureData {
		int atlasIndex = -1;
		Rectangle rect;

		TextureData(int index, Rectangle rect)
			: atlasIndex(index), rect(rect){
		}
	};
	
	TextureData texture;
	Game* game;
	bool inmune = false;
};
