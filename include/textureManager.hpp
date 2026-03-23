#pragma once
#include <game.hpp>
#include <vector>
#include <string>
#include <unordered_map>

const int ATLAS_TILE_WIDTH = 8;
const int ATLAS_TILE_HEIGHT = 8;
const int ATLAS_SCALE_FACTOR = 4;

class TextureManager {
    public:

    TextureManager();

    void setGame(Game* game);
    void draw(int textIndex, Rectangle rect, Vector2 pos, Color color);
    int loadTexture(std::string path);
    void unloadTexture(int index);
    void unloadAll();

    private:

    Game* game;
    std::vector<Texture> textures;
    std::unordered_map<std::string, int> textureIndexes;
};

class TextureError : public std::exception {
private:
    std::string msg;
public:
    // Constructor que recibe un mensaje
    explicit TextureError(const int index);

    // Para devolver el mensaje
    const char* what() const noexcept override {
        return msg.c_str();
    }
};