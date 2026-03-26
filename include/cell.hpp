#include <gameObject.hpp>
#include <wallObject.hpp>
#include <textureManager.hpp>
#include <vector>

class Cell {
    public:

    Cell();

    Cell(GameObject* obj);

    Cell(int type, Rectangle rect, Vector2 pos, TextureManager& tm, int atlasIndex, Game* game);

    bool isEmpty() const;

    void emptyCell();

    bool isTraversable() const;

    void addObj(GameObject* obj);

    void update(float deltaTime);

    void processAttacks();

    void removeObj(GameObject* obj);
    
    ~Cell();
    
    private:
    static GameObject* createCellFromType(int type, Rectangle rect, Vector2 pos, TextureManager& tm, int atlasIndex, Game* game);

    std::vector<GameObject*> objects;


};