#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>


TextureCache::TextureCache()
{
}


TextureCache::~TextureCache()
{
}


GLTexture TextureCache::getTexture(std::string texturePath) {

	//Look up the texture and see if its in the map - Using auto!
	//std::map<std::string, GLTexture>::iterator mit = _textureMap.find(texturePath);
	auto mit = _textureMap.find(texturePath);

	//check if the texture is not in the map
	if (mit == _textureMap.end()) {
		//Load Texture
		GLTexture newTexture = ImageLoader::loadPNG(texturePath);

		//insert new texture into map
		_textureMap.insert(make_pair(texturePath, newTexture));

		std::cout << "Loaded Cached Texture!\n";
		return newTexture;
	}

	//Return the texture, mit has found the texture already in the map
	std::cout << "Used Cached Texture!\n";
	return mit->second;

}