#pragma once
#include <gameObject.hpp>
#include <game.hpp>
#include <snakeBody.hpp>

class Snake : public GameObject{
public:
	Snake(int lives, Vector2 pos, float speed, TextureManager& tm, Vector2 direction, int atlasIndex, Rectangle textureRect, Game* game):
		GameObject(lives, pos, speed, tm, direction, atlasIndex, textureRect, game), nextDirection(direction) {}

	void update(float deltaTime) override;
	void move(Vector2 direction, float deltaTime) override;

	void addBodyPieces(int count);

private:
	bool speed_boost = false;

	float PLAYER_SPEED_BOOST = 1.5f;

	Vector2 nextDirection;

	GameObject* lastSnakeBody = this;

};