#pragma once
#include <gameObject.hpp>
#include <game.hpp>

class Snake : public GameObject{
public:
	Snake(int lives, Vector2 pos, float speed, TextureManager& sm, Vector2 direction, int atlasIndex, Rectangle textureRect, Game* game);

	void update(float deltaTime) override;
	void move(Vector2 direction, float deltaTime) override;


private:
	bool speed_boost = false;

	float PLAYER_SPEED_BOOST = 1.5f;

	std::shared_ptr<GameObject> attack = nullptr;

};