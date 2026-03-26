#include <cell.hpp>

Cell::Cell(){}

// TODO CONSTRUCTOR DA SIGSEV POR AHORA
Cell::Cell(GameObject* obj){
    addObj(obj);
} 

// TODO CONSTRUCTOR DA SIGSEV POR AHORA
Cell::Cell(int type, Rectangle rect, Vector2 pos, TextureManager& tm, int atlasIndex, Game* game)
    {
        GameObject* obj = createCellFromType(type, rect, pos, tm, atlasIndex, game);
        if(obj != nullptr)
            this->addObj(obj);
    } 

GameObject* Cell::createCellFromType(int type, Rectangle rect, Vector2 pos, TextureManager& tm, int atlasIndex, Game* game){
    switch (type)
    {
    case 0:
        return nullptr;
        break;
    case 1:
        return new WallObject(pos, tm, atlasIndex, rect, game);
        break;
    default:
        return nullptr;
    }
}

void Cell::emptyCell(){
    for(auto a : objects){
        delete a;
        a = nullptr;
    }
    objects.clear();
}

bool Cell::isEmpty() const{
    return objects.empty();
}

bool Cell::isTraversable() const{
    int i = 0;

    while(i < objects.size() && objects[i]->istraversable()) i++;

    return i == objects.size();
}

void Cell::addObj(GameObject* obj){
    objects.push_back(obj);
}

void Cell::update(float deltaTime) {
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->update(deltaTime);
	}
}

void Cell::removeObj(GameObject* obj){
    int i = 0;
    while(i < objects.size() && objects[i] != obj)i++;

    if(i < objects.size())
        objects.erase(objects.begin() + i);
}

void Cell::processAttacks() {
    for (int i = 0; i < objects.size(); i++)
	{
        for (int j = 0; j < objects.size(); j++)
		{
            objects[i]->attack(objects[j]);
		}
	}
}

Cell::~Cell(){
    emptyCell();
}
