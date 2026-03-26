#include <vector>
#include <string>
#include <game.hpp>
#include <textureManager.hpp>
#include <cell.hpp>
#include <nlohmann/json.hpp>
#include <fstream>
#include <queue>

using json = nlohmann::json;

class GameBoard{
public:
	GameBoard(TextureManager& tm, int atlasIndex, Game* game, const int height, const int width);
    GameBoard(TextureManager& tm, int atlasIndex, Game* game, std::string levelPath);

    bool canMoveToPos(int x, int y) const;

	void add(GameObject* obj);
	void update(float deltaTime);
	void processAttacks();
	void draw();
	void queueDrawObject(GameObject* obj);

    bool isOut(int x, int y) const;
    bool isOut(Vector2 pos) const;

    void moveObjToNewCell(GameObject* obj, int newX, int newY, int oldX, int oldY);

    Vector2 getDimensions();

	//void removeDead();
	//void spriteRemoved(int index);
	void free();

	~GameBoard();

    
    private:
	//void remove(int index);
    void loadFromFile(std::string path, Game* game);
    bool buildMap(std::vector<std::vector<int>> map, Game* game);
    
    int height;
    int width;
    std::vector<std::vector<Cell*>> cells;
    TextureManager& tm;
    int atlasIndex;
    
	std::priority_queue<GameObject*, std::vector<GameObject*>, GameObject::CmpGameObjects> drawQueue;
};

class OutOfBoundsError : public std::exception {
private:
    std::string msg;
public:
    // Constructor que recibe un mensaje
    explicit OutOfBoundsError(Vector2 pos);

    // Para devolver el mensaje
    const char* what() const noexcept override {
        return msg.c_str();
    }
};

class MapParseError : public std::exception {
private:
    std::string msg;
public:
    // Constructor que recibe un mensaje
    explicit MapParseError(std::string path);

    // Para devolver el mensaje
    const char* what() const noexcept override {
        return msg.c_str();
    }
};