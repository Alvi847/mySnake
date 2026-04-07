#include <gameObject.hpp>
#include <gameBoard.hpp>
#include <iostream>

// Sistema de colisi�n AABB (Axis-Aligned Bounding Box)
bool GameObject::isOnPosition(Vector2 other) const{
	return other == this->position;
}

void GameObject::move(Vector2 direction, float deltaTime){
	this->direction = direction; 
	Vector2 newPos = position + (direction * speed);
        
	emplace(newPos);
}

void GameObject::emplace(Vector2 newPos){
	newPos = game->movedToNewCell(this, floor(newPos.x), floor(newPos.y), floor(position.x), floor(position.y));

	if(!Vector2Equals(newPos, position)){
		lastPosition = position;
		position = newPos;
	}
	
	//std::cout << "POSITION_x: " << position.x << " POSITION_y: " << position.y << std::endl;
    //std::cout << "LAST_POSITION_x: " << lastPosition.x << " LAST_POSITION_y: " << lastPosition.y << std::endl;
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

void GameObject::receiveDamage(int dmg){
	lives -= dmg;
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

int GameObject::getSpeed() const{
	return speed;
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

void GameObject::draw(Vector2 globalOrigin) {
	if (texture.atlasIndex != -1)
	{
		textureManager.draw(texture.atlasIndex, texture.rect, position * CELL_SIZE + globalOrigin, direction, WHITE);
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