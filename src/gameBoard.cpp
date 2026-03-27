#include <gameBoard.hpp>
#include <iostream>

// TODO HACER BIEN EL MAPA
GameBoard::GameBoard(TextureManager& tm, int atlasIndex, Game* game, const int height, const int width):
    height(height), width(width), tm(tm), atlasIndex(atlasIndex), borderlessMode(true),
    drawQueue(std::priority_queue<GameObject*, std::vector<GameObject*>, GameObject::CmpGameObjects>()){
        Rectangle rect = {ATLAS_TILE_WIDTH * 12, 0, ATLAS_TILE_WIDTH, ATLAS_TILE_HEIGHT};
        cells = std::vector<std::vector<Cell*>>(width);
        for(int i = 0; i < width; i++){
            cells[i] = std::vector<Cell*>(height);

            for(int j = 0; j < height; j++){
                cells[i][j] = (new Cell(0, rect, Vector2{(float) i, (float) j}, tm, atlasIndex, game));
            }
                
        }
        std::cout << "HEIGHT: " << height << " WIDTH: " << width << std::endl;
}

GameBoard::GameBoard(TextureManager& tm, int atlasIndex, Game* game, std::string levelPath):
    tm(tm), atlasIndex(atlasIndex), borderlessMode(false),
    drawQueue(std::priority_queue<GameObject*, std::vector<GameObject*>, GameObject::CmpGameObjects>()){
        loadFromFile(levelPath, game);
}

void GameBoard::loadFromFile(std::string path, Game* game){
    std::ifstream f(path);
    json data = json::parse(f);

    bool success = false;

    
    if (data.find("width") != data.end() && data["width"].is_number()) {
        width = data["width"];
        if (data.find("height") != data.end() && data["height"].is_number()) {
            height = data["height"];
            if (data.find("map") != data.end() && data["map"].is_array()) {
                success = buildMap(data["map"], game);
            }
        }
    }
    
    if(!success)
    throw MapParseError(path);
}

bool GameBoard::buildMap(std::vector<std::vector<int>> map, Game* game){
    bool success = true;
    int i = 0;
    int j = 0;
    
    Rectangle rect = {ATLAS_TILE_WIDTH * 12, 0, ATLAS_TILE_WIDTH, ATLAS_TILE_HEIGHT};

    cells = std::vector<std::vector<Cell*>>(width);

    if(map.size() == width){
        while(success && i < map.size()){
            if (map[i].size() == height){
                cells[i] = std::vector<Cell*>(height);

                while(success && j < map[i].size()){
                    cells[i][j] = (new Cell(map[i][j], rect, Vector2{(float) i, (float) j}, tm, atlasIndex, game));
                    j++;
                }
            }
            else
                success = false;
            j = 0;
            i++;
        }
    }
    else
        success = false;

    return success;
}

bool GameBoard::canMoveToPos(int x, int y) const {    
    if(!isOut(x, y)){
        return cells[x][y]->isTraversable(); 
    }
    else return false;
    //else throw OutOfBoundsError(Vector2{(float) x, (float) y});
}

void GameBoard::update(float deltaTime) {
	for (auto a : cells)
	{
        for(auto b : a)
		    b->update(deltaTime);
	}
}

void GameBoard::processAttacks() {
	for (auto a : cells)
	{
        for(auto b : a)
		    b->processAttacks();
	}
}

void GameBoard::add(GameObject* obj) {

    Vector2 pos = obj->getPos();

    int x = floor(pos.x);
    int y = floor(pos.y);
    
    if(!isOut(x, y)){
	    cells[x][y]->addObj(obj);
    }
    else throw OutOfBoundsError(pos);
}

void GameBoard::queueDrawObject(GameObject* obj){
	drawQueue.push(obj);
}

void GameBoard::draw(){
	while(!drawQueue.empty()){
		drawQueue.top()->draw();
		drawQueue.pop();
	}
}	

Vector2 GameBoard::getDimensions(){
    return Vector2{(float) width, (float) height};
}

bool GameBoard::isOut(int x, int y) const{
    return x >= cells.size() || y >= cells[x].size() || x < 0 || y < 0;
}

Vector2 GameBoard::moveObjToNewCell(GameObject* obj, int newX, int newY, int oldX, int oldY){
    if(!isOut(newX, newY)){
        if(!isOut(oldX, oldY)){
            cells[oldX][oldY]->removeObj(obj);
            cells[newX][newY]->addObj(obj);

            return Vector2{(float) newX, (float) newY};
        }
        else throw OutOfBoundsError(Vector2{(float) oldX, (float) oldY});
    }
    if(borderlessMode){
        if(!isOut(oldX, oldY)){
            if (newX >= width)
                newX = 0;
            else if (newX < 0)
                newX = width - 1;
            
            if (newY >= height)
                newY = 0;
            else if (newY < 0)
                newY = height - 1;

            cells[oldX][oldY]->removeObj(obj);
            cells[newX][newY]->addObj(obj);
            return Vector2{(float) newX, (float) newY};

        }
        else throw OutOfBoundsError(Vector2{(float) oldX, (float) oldY});
    }
    else throw OutOfBoundsError(Vector2{(float) newX, (float) newY});
}

bool GameBoard::isOut(Vector2 pos) const{
    int x = floor(pos.x);
    int y = floor(pos.y);
    return x > cells.size() || y > cells[x].size() || x < 0 && y < 0;
}

/*void GameBoard::removeDead() {
	for (int i = 0; i < objects.size(); i++)
	{
		if(!objects[i]->isAlive())
		{
			objects[i]->onDeath();
			remove(i);
		}
	}
}*/

/*void GameBoard::spriteRemoved(int index) {
	for (auto& obj : objects)
	{
		obj->spriteRemoved(index);
	}
}*/

void GameBoard::free(){
    for(auto a : cells){
        for(auto b : a){
            delete b;
            b = nullptr;
        }
    }

    cells.clear();
}

GameBoard::~GameBoard(){
	free();
}

OutOfBoundsError::OutOfBoundsError(Vector2 pos) {
	msg = std::string("Error: La posicion {" + std::to_string(pos.x) + std::string(", ") +
     std::to_string(pos.y) +  std::string("} esta fuera del mapa\n"));
}

MapParseError::MapParseError(std::string path) {
	msg = std::string("Error: El json en: " + path + " no cumple con los requisitos para representar un mapa del juego\n");
}