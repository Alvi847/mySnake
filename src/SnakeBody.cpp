#include <snakeBody.hpp>
#include <iostream>
#include <snake.hpp>

void SnakeBody::update(float deltaTime){
    game->queueDrawObject(this);
}

void SnakeBody::emplace(Vector2 newPos){    
    //std::cout << "BODY_POSITION_X: " << position.x << " BODY_POSITION_Y: " << position.y << std::endl;
    //std::cout << "GOAL_X: " << lastSnakeBody->getLastPos().x << " GOAL_Y: " << lastSnakeBody->getLastPos().y << std::endl;

    Reptile::emplace(newPos);

    hasMoved = true;
}

void SnakeBody::die(){
    GameObject::die();
    lastSnakeBody->die();
}

bool SnakeBody::receiveAttack(Snake* attacker){
    bool attacked = hasMoved && isAlive();
    if(attacked){
        lives -= 1;
        attacker->receiveDamage(1);
    }
    return attacked;
}