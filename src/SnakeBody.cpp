#include <snakeBody.hpp>
#include <iostream>

void SnakeBody::update(float deltaTime){
    if(Vector2Distance(lastSnakeBody->getPos(), this->position) > 1){
        this->direction = this->getDirectionToPos(lastSnakeBody->getLastPos());
        move(direction, deltaTime);
    }
    game->queueDrawObject(this);
}

void SnakeBody::move(Vector2 direction, float deltaTime){
    hasMoved = true;

    GameObject::move(direction, deltaTime);

    std::cout << "BODY_POSITION_X: " << position.x << " BODY_POSITION_Y: " << position.y << std::endl;
    std::cout << "GOAL_X: " << lastSnakeBody->getLastPos().x << " GOAL_Y: " << lastSnakeBody->getLastPos().y << std::endl;
}