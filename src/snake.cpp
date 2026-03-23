#include <snake.hpp>

Snake::Snake(int lives, Vector2 pos, float speed, TextureManager& tm, Vector2 direction, int atlasIndex, Rectangle textureRect, Game* game):
GameObject(lives, pos, speed, tm, direction, atlasIndex, textureRect, game) {}

void Snake::update(float deltaTime){
    Vector2 direction = {0, 0};
    if (IsKeyDown(KEY_RIGHT)) direction += {1, 0};
    if (IsKeyDown(KEY_LEFT)) direction += {-1, 0};
    if (IsKeyDown(KEY_UP)) direction += {0, -1};
    if (IsKeyDown(KEY_DOWN)) direction += {0, 1};
    move(direction, deltaTime);
    //std::cout << "Position: {" << position.x << ", " << position.y << "}\n";
    draw();
}

void Snake::move(Vector2 direction, float deltaTime){
    position = position + (direction * speed) * deltaTime;
}