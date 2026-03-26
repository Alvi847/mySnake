#include <gameObject.hpp>


class WallObject : public GameObject {
    public:
    WallObject(Vector2 pos, TextureManager& textureManager, 
	std::string texturePath, Rectangle textureRect, Game* game) :
		GameObject(1, pos, 0, textureManager, Vector2{0, 0},texturePath, textureRect, game ){ 
            toggleInmune(); 
            toggleTraversable();
        }

    WallObject(Vector2 pos, TextureManager& textureManager, 
	int atlasIndex, Rectangle textureRect, Game* game) :
		GameObject(1, pos, 0, textureManager, Vector2{0, 0}, atlasIndex, textureRect, game ){ 
            toggleInmune();
            toggleTraversable();
        }

    virtual void update(float deltaTime) override {
        game->queueDrawObject(this);
    }
};