#pragma once
#include <reptile.hpp>
#include <game.hpp>
#include <snakeBody.hpp>
#include <inputMappings.hpp>

class Snake : public Reptile{
public:
	Snake(int lives, Vector2 pos, float speed, TextureManager& tm, Vector2 direction, int atlasIndex, Rectangle textureRect, 
		Game* game, InputMappings* mappings):
		Reptile(lives, pos, speed, tm, direction, atlasIndex, textureRect, game), nextDirection(direction),
		mappings(mappings) {}

	void update(float deltaTime) override;
	void move(Vector2 direction, float deltaTime) override;

	void addBodyPieces(int count);

	bool attack(GameObject* other) override;
	void die() override;

	~Snake();

private:

	InputMappings* mappings;

	bool speed_boost = false;

	float PLAYER_SPEED_BOOST = 1.5f;

	Vector2 nextDirection;
	
	bool dieRecursionStop = false;

};