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

	virtual void move(Vector2 direction, float deltaTime){}
	bool canMove(float deltaTime);

	virtual void update(float deltaTime) = 0;

	//virtual bool receiveAttack(GameObject* attacker);

	virtual bool attack(GameObject* other);

	bool isAlive() const;
	void die();

	virtual void onDeath() {}

	// Sistema de colision AABB (Axis-Aligned Bounding Box)
	virtual bool isOnPosition(Vector2 other) const;

	Vector2 getDirectionToPos(Vector2 position) const;

	Vector2 getPos() const;

	Vector2 getDirection() const;

	bool isInmune() const;

	void setZIndex(int z);

	virtual ~GameObject() = default;

	struct CmpGameObjects{
		bool operator()(const GameObject* a, const GameObject* b) const{
			return  a->zIndex < b->zIndex;
		}
	};

	virtual void draw();

	void toggleInmune();

	void toggleTraversable();

	bool istraversable() const;

protected:
	//virtual void debugDraw();

	int movementTimerReset = MOVEMENT_FREQUENCY;
	int movementTimer = movementTimerReset;

	bool traversable = true;

	int lives;
	Vector2 position; // Posicion EN EL TABLERO DEL JUEGO
	float speed;
	TextureManager& textureManager;
	Vector2 direction = Vector2Zero();
	int zIndex = 0; // For drawing order (the object with the highest z gets drawn on top of the other objects) 
	
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
