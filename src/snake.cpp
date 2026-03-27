#include <snake.hpp>
#include <iostream>

void Snake::update(float deltaTime){
    if (IsKeyDown(KEY_RIGHT) && direction != Vector2{-1, 0}) nextDirection = {1, 0};
    if (IsKeyDown(KEY_LEFT) && direction != Vector2{1, 0}) nextDirection = {-1, 0};
    if (IsKeyDown(KEY_UP) && direction != Vector2{0, 1}) nextDirection = {0, -1};
    if (IsKeyDown(KEY_DOWN) && direction != Vector2{0, -1}) nextDirection = {0, 1};
    move(nextDirection, deltaTime);
    //std::cout << "Position: {" << position.x << ", " << position.y << "}\n";
    game->queueDrawObject(this);
}

void Snake::move(Vector2 direction, float deltaTime){
    
    if(!canMove(deltaTime)){
        return;
    }
    
    this->direction = direction;
    GameObject::move(direction, deltaTime);

    
    std::cout << "POSITION_x: " << position.x << " POSITION_y: " << position.y << std::endl;
    std::cout << "LAST_POSITION_x: " << lastPosition.x << " LAST_POSITION_y: " << lastPosition.y << std::endl;
}

void Snake::addBodyPieces(int count){
    Rectangle snakeBodyTextureRect{ATLAS_TILE_WIDTH * 5, ATLAS_TILE_HEIGHT * 3,
		ATLAS_TILE_WIDTH, ATLAS_TILE_HEIGHT};

    for(int i = 0; i < count; i++){
        Vector2 bodyPos = lastSnakeBody->getPos();
        SnakeBody* bodyPiece = new SnakeBody(1, bodyPos, speed, textureManager, direction,
            texture.atlasIndex, snakeBodyTextureRect, game, lastSnakeBody);
        lastSnakeBody = bodyPiece;
        game->addObj(bodyPiece);
    }
}