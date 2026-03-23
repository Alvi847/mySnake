#include <gameObject.hpp>

bool GameObject::attack(GameObject* other) {
	return false;
}

// Sistema de colisi�n AABB (Axis-Aligned Bounding Box)
bool GameObject::isOnPosition(Vector2 other) {
	return other == position;
}

void GameObject::move(Vector2 direction, float deltaTime) {}

bool GameObject::isAlive() {
	return lives > 0;
}

void GameObject::die() {
	lives = 0;
}

Vector2 GameObject::getPos() {
	return position;
}

bool GameObject::isInmune() {
	return inmune;
}

void GameObject::draw() {
	if (texture.atlasIndex != -1)
	{
		textureManager.draw(texture.atlasIndex, texture.rect, position, WHITE);
	}
}

/*void GameObject::debugDraw() {
	if (spriteIndex != -1)
	{
		textureManager.debugMoveSpriteTo(spriteIndex, position);

		textureManager.debugDraw(spriteIndex);
	}
}*/

Vector2 GameObject::getDirectionToPos(Vector2 position) {
	return Vector2{ position.x - this->position.x, position.y - this->position.y };
}