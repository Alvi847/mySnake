#pragma once
#include <gameObject.hpp>

class Fruit : public GameObject{
public:
	Fruit(Vector2 pos, TextureManager& tm, int atlasIndex, Rectangle textureRect, Game* game, int value):
		GameObject(1, pos, 0.f, tm, Vector2{0.f, -1.f}, atlasIndex, textureRect, game), value(value){}

	void update(float deltaTime) override;

    bool receiveAttack(Snake* other) override;

    void onRemove() override;

private:
    int value;
};