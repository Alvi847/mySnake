#include <gameBoard.hpp>


// TODO HACER BIEN EL MAPA
GameBoard::GameBoard(TextureManager& tm, int atlasIndex, Game* game, int height, int width):
    GameObject(0, {0, 0}, 0, tm, {0, 0}, atlasIndex, {0, 0, 0, 0}, game), height(height), width(width){
        cells = std::vector<std::vector<bool>>(width);
        for(int i = 0; i < cells.size(); i++){
            cells[i] = std::vector<bool>(height);
            for(int j = 0; j < cells[i].size(); j++){
                cells[i][j] = false;
                if(i == 0 || j == 0 || i == width - 1 || j == height - 1)
                    cells[i][j] = true;
            }
        }
        texture.rect = {ATLAS_TILE_WIDTH * ATLAS_SCALE_FACTOR * 12, 0,
		ATLAS_TILE_WIDTH * ATLAS_SCALE_FACTOR, ATLAS_TILE_HEIGHT * ATLAS_SCALE_FACTOR};
}


void GameBoard::update(float deltaTime){
    for(int i = 0; i < cells.size(); i++){
        for(int j = 0; j < cells[i].size(); j++){
            if(cells[i][j]){
                position = {(float) i * CELL_SIZE, (float) j * CELL_SIZE};
                draw();
            }
        }
    }
}