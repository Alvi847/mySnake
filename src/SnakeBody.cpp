#include <snakeBody.hpp>
#include <iostream>
#include <snake.hpp>

void SnakeBody::update(float deltaTime){
    game->queueDrawObject(this);
}

void SnakeBody::emplace(Vector2 newPos){    
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