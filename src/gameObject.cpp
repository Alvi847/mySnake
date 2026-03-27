#include <gameObject.hpp>
#include <gameBoard.hpp>

bool GameObject::attack(GameObject* other) {
	return false;
}

// Sistema de colisi�n AABB (Axis-Aligned Bounding Box)
bool GameObject::isOnPosition(Vector2 other) const{
	return other == this->position;
}

void GameObject::move(Vector2 direction, float deltaTime){
	Vector2 newPos = position + (direction * speed); 
        
    newPos = game->movedToNewCell(this, floor(newPos.x), floor(newPos.y), floor(position.x), floor(position.y));

    if(!Vector2Equals(newPos, position)){
        lastPosition = position;
        position = newPos;
    }
}

bool GameObject::canMove(float deltaTime) {
	this->movementTimer -= deltaTime;
	if(this->movementTimer > 0)
		return false;

	this->movementTimer = this->movementTimerReset;
	return true;
}

bool GameObject::isAlive() const{
	return this->lives > 0;
}

void GameObject::die() {
	this->lives = 0;
}

Vector2 GameObject::getPos() const{
	return this->position;
}

Vector2 GameObject::getLastPos() const{
	return this->lastPosition;
}

Vector2 GameObject::getDirection() const{
	return this->direction;
}

bool GameObject::isInmune() const{
	return this->inmune;
}

void GameObject::setZIndex(int z){
	this->zIndex = z;
}

void GameObject::toggleInmune(){
	this->inmune = !this->inmune;
}

void GameObject::toggleTraversable(){
	this->traversable = !this->traversable;
}

bool GameObject::istraversable() const{
	return traversable;
}

void GameObject::draw() {
	if (texture.atlasIndex != -1)
	{
		textureManager.draw(texture.atlasIndex, texture.rect, position * CELL_SIZE, direction, WHITE);
	}
}

/*void GameObject::debugDraw() {
	if (spriteIndex != -1)
	{
		textureManager.debugMoveSpriteTo(spriteIndex, position);

		textureManager.debugDraw(spriteIndex);
	}
}*/

Vector2 GameObject::getDirectionToPos(Vector2 position) const{
	return Vector2Normalize(Vector2{ position.x - this->position.x, position.y - this->position.y });
}