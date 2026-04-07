#pragma once
#include <reptile.hpp>
#include <game.hpp>

class SnakeBody : public Reptile{
public:
	SnakeBody(int lives, Vector2 pos, float speed, TextureManager& tm, Vector2 direction, int atlasIndex, Rectangle textureRect, Game* game, GameObject* lastSnakeBody):
		Reptile(lives, pos, speed, tm, direction, atlasIndex, textureRect, game), lastSnakeBody(lastSnakeBody){}

	void update(float deltaTime) override;
	void emplace(Vector2 newPos) override;

	bool receiveAttack(Snake* attacker) override;

	void die() override;

private:


    bool hasMoved = false; // Para ver si se han movido al menos una vez (para las colisiones de la serpiente consigo misma)
    GameObject* lastSnakeBody;
};