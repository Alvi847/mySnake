#include <iostream>
#include <fruit.hpp>
#include <snake.hpp>

void Fruit::update(float deltaTime){
    game->queueDrawObject(this);
}

bool Fruit::receiveAttack(Snake* other){
    bool attacked = isAlive();
    if(attacked){
        other->addBodyPieces(value);
        die();
    }
    return attacked;
}

void Fruit::onRemove(){
    game->fruitEaten();
}
