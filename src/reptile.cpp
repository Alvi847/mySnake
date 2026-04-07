#include <reptile.hpp>
#include <iostream>

void Reptile::setNextBodyPiece(Reptile* bodyPiece){
    nextSnakeBody = bodyPiece;
}

void Reptile::emplace(Vector2 newPos){
    GameObject::emplace(newPos);
    
    if(nextSnakeBody != this){
        Vector2 goalPosition = lastPosition; // Next body piece's goal position is our LAST POSITION 
        Vector2 boardDimensions = game->getBoardDimensions();
        Vector2 nextBodyPos = nextSnakeBody->getPos();
        
        nextSnakeBody->emplace(goalPosition);
    }
}

bool Reptile::isGoalOnTheOtherEnd(Vector2 nextBodyPos) const{
    Vector2 boardDimensions = game->getBoardDimensions();
    /*std::cout << "BOARD: { " << boardDimensions.x << " " << boardDimensions.y << " }\n";
    std::cout << "GOAL: { " << position.x << " " << position.y << " }\n";
    std::cout << "POSITION: { " << nextBodyPos.x << " " << nextBodyPos.y << " }\n";
    MAL, DIRECCION DE THIS, NO DE NEXTBODYPIECE std::cout << "DIRECTION: { " << direction.x << " " << direction.y << " }\n";
    std::cout << "------------------------\n";*/
    return ((nextBodyPos.x >= boardDimensions.x - 1 && position.x <= 1.f) || (position.x >= boardDimensions.x - 2 && nextBodyPos.x <= 0.f)) || 
        ((nextBodyPos.y >= boardDimensions.y - 1 && position.y <= 1.f) || (position.y >= boardDimensions.y - 2 && nextBodyPos.y <= 0.f));
}