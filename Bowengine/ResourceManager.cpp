#include "ResourceManager.h"

namespace Bowengine {

	TextureCache ResourceManager::_textureCache;

	//Wrapper function to return textures
	GLTexture ResourceManager::getTexture(std::string texturePath) {
		return _textureCache.getTexture(texturePath);
	}

}