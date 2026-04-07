#pragma once
#include <gameObject.hpp>
#include <game.hpp>

class Reptile : public GameObject{
public:
	Reptile(int lives, Vector2 pos, float speed, TextureManager& tm, Vector2 direction, int atlasIndex, Rectangle textureRect, 
		Game* game):
		GameObject(lives, pos, speed, tm, direction, atlasIndex, textureRect, game) {}

	void setNextBodyPiece(Reptile* bodyPiece);

    void emplace(Vector2 newPos) override;

protected:

    bool isGoalOnTheOtherEnd(Vector2 nextBodyPos) const;

	Reptile* lastSnakeBody = this;
	Reptile* nextSnakeBody = this;

};