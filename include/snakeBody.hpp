#pragma once
#include <gameObject.hpp>
#include <game.hpp>

class SnakeBody : public GameObject{
public:
	SnakeBody(int lives, Vector2 pos, float speed, TextureManager& tm, Vector2 direction, int atlasIndex, Rectangle textureRect, Game* game, const GameObject* lastSnakeBody):
		GameObject(lives, pos, speed, tm, direction, atlasIndex, textureRect, game), lastSnakeBody(lastSnakeBody){}

	void update(float deltaTime) override;
	void move(Vector2 direction, float deltaTime) override;


private:


    bool hasMoved = false; // Para ver si se han movido al menos una vez (para las colisiones de la serpiente consigo misma)
    const GameObject* lastSnakeBody;
};