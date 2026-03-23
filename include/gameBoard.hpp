#include <gameObject.hpp>
#include <vector>
#include <string>

const int CELL_SIZE = 8 * ATLAS_SCALE_FACTOR;

class GameBoard : public GameObject{
public:
	GameBoard(TextureManager& tm, int atlasIndex, Game* game, int height, int width);

	void update(float deltaTime) override;


private:
    int height;
    int width;
    std::vector<std::vector<bool>> cells;
};