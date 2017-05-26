#include "ResourceManager.h"

namespace Bowengine {

	TextureCache ResourceManager::_textureCache;
	ImageLoader ResourceManager::_imageLoader;
	ObjectLoader ResourceManager::_objectLoader;

	//Wrapper function to return textures
	GLTexture ResourceManager::getTexture(std::string texturePath) {
		return _textureCache.getTexture(texturePath);
	}

	bool ResourceManager::loadObject(std::string objectPath, std::vector<glm::vec3> & out_vertices, std::vector<glm::vec2> & out_uvs, std::vector<glm::vec3> & out_normals) {
		return _objectLoader.loadOBJ(objectPath, out_vertices, out_uvs, out_normals);
	}

}