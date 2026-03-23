#include <textureManager.hpp>
#include <iostream>


TextureManager::TextureManager() :
	game(nullptr){}

void TextureManager::setGame(Game* game){
    this->game = game;
}

void TextureManager::draw(int textIndex, Rectangle rect, Vector2 pos, Color color = WHITE){
	if (textIndex < textures.size())
		DrawTextureRec(textures[textIndex], rect, pos, color);
	else
		throw TextureError(textIndex);
}

int TextureManager::loadTexture(std::string path){
	int ret;
	auto i = textureIndexes.find(path);

	if(i == textureIndexes.end()){
		textures.push_back(LoadTexture(path.c_str()));
		ret = textures.size() - 1;
		
		textures[ret].height += (128 * (ATLAS_SCALE_FACTOR - 1));
		textures[ret].width += (128 * (ATLAS_SCALE_FACTOR - 1));

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