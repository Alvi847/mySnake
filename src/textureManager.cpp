#include <textureManager.hpp>
#include <iostream>


TextureManager::TextureManager() :
	game(nullptr){}

void TextureManager::setGame(Game* game){
    this->game = game;
}

void TextureManager::draw(int textIndex, Rectangle sourceRect, Vector2 pos, Vector2 orientation = {1, 0}, Color color = WHITE){
	if (textIndex < textures.size()){
		Rectangle destRect = {pos.x , pos.y, CELL_SIZE, CELL_SIZE};
		float angle = Vector2Angle(orientation, {(float)0, (float)-1});
		Vector2 origin = {destRect.width / 2, destRect.height / 2};
		/*if(orientation != Vector2Zero()){
			std::cout << "ANGLE: " << angle << std::endl;
			std::cout << "OR_X: " << orientation.x << " OR_Y: " << orientation.y << std::endl;
		}*/
		DrawTexturePro(textures[textIndex], sourceRect, destRect, origin, -angle * 180 / PI, color);
		//DrawTextureRec(textures[textIndex], sourceRect, pos, color);
	}
	else
		throw TextureError(textIndex);
}

int TextureManager::loadTexture(std::string path){
	int ret;
	auto i = textureIndexes.find(path);

	if(i == textureIndexes.end()){
		textures.push_back(LoadTexture(path.c_str()));
		ret = textures.size() - 1;
		
		//textures[ret].height += (128 * (ATLAS_SCALE_FACTOR - 1));
		//textures[ret].width += (128 * (ATLAS_SCALE_FACTOR - 1));

		textureIndexes.emplace(path, ret);
	}
	else
		ret = i->second;
	return ret;
}

void TextureManager::unloadTexture(int index){
    if (index < textures.size()){
        UnloadTexture(textures[index]);
		textures.erase(textures.begin() + index);
	}
	else
		throw TextureError(index);
}

void TextureManager::unloadAll(){
	for(auto a : textures){
        UnloadTexture(a);
    }
}

TextureError::TextureError(const int index) {
	msg = std::string("Error: El indice de textura " + index + std::string(" no pertenece a ninguna textura cargada\n"));
}