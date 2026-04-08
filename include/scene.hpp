#include <game.hpp>

class Scene {

public:

    Scene(Game* game): game(game){}

    void initScene();

    void setZIndex(int z);

    int getZIndex();

    void unload();

private:

    Game* game;
    int zIndex = 0;
};