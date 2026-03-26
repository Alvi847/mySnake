#include <snakeBody.hpp>

void SnakeBody::update(float deltaTime){
    if(Vector2Distance(lastSnakeBody->getPos(), this->position) > 1){
        this->direction = Vector2Normalize(this->getDirectionToPos(lastSnakeBody->getPos() + lastSnakeBody->getDirection() * -1));
        move(direction, deltaTime);
    }
    game->queueDrawObject(this);
}

void SnakeBody::move(Vector2 direction, float deltaTime){
    this->position += (this->direction * this->speed);
    this->hasMoved = true;
}