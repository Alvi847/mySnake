#include <snake.hpp>
#include <iostream>

void Snake::update(float deltaTime){
    if (IsKeyDown(mappings->get("right")) && direction != Vector2{-1, 0}) nextDirection = {1, 0};
    if (IsKeyDown(mappings->get("left")) && direction != Vector2{1, 0}) nextDirection = {-1, 0};
    if (IsKeyDown(mappings->get("up")) && direction != Vector2{0, 1}) nextDirection = {0, -1};
    if (IsKeyDown(mappings->get("down")) && direction != Vector2{0, -1}) nextDirection = {0, 1};
    move(nextDirection, deltaTime);
    //std::cout << "Position: {" << position.x << ", " << position.y << "}\n";
    game->queueDrawObject(this);
}

void Snake::move(Vector2 direction, float deltaTime){
    
    if(!canMove(deltaTime)){
        return;
    }
    
    GameObject::move(direction, deltaTime);

    if(nextSnakeBody != this){ 
        nextSnakeBody->emplace(lastPosition);   // Next body piece's goal position is our LAST POSITION
    }
    
    //std::cout << "POSITION_x: " << position.x << " POSITION_y: " << position.y << std::endl;
    //std::cout << "LAST_POSITION_x: " << lastPosition.x << " LAST_POSITION_y: " << lastPosition.y << std::endl;
}

void Snake::addBodyPieces(int count){
    Rectangle snakeBodyTextureRect{ATLAS_TILE_WIDTH * 5, ATLAS_TILE_HEIGHT * 3,
		ATLAS_TILE_WIDTH, ATLAS_TILE_HEIGHT};

    for(int i = 0; i < count; i++){
        Vector2 bodyPos = lastSnakeBody->getPos();
        SnakeBody* bodyPiece = new SnakeBody(1, bodyPos, speed, textureManager, direction,
            texture.atlasIndex, snakeBodyTextureRect, game, lastSnakeBody);
        lastSnakeBody->setNextBodyPiece(bodyPiece);
        lastSnakeBody = bodyPiece;
        game->addObj(bodyPiece);
    }
}

bool Snake::attack(GameObject* other){
    bool attacked = other->receiveAttack(this);
    if(!isAlive())
        die();
	return attacked;
}

void Snake::die() {
    if(!dieRecursionStop){
        dieRecursionStop = true;
        std::cout << "MUERTEEE\n";
        GameObject::die();
        lastSnakeBody->die();
    }
}


Snake::~Snake(){
    delete mappings;
    mappings = nullptr;
}