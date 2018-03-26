#pragma once

#include "TextureCache.h"
#include "ImageLoader.h"
#include "ObjectLoader.h"

#include <string>

namespace Bowengine {

	class ResourceManager
	{
	public:
		static GLTexture getTexture(std::string texturePath);
		static bool loadObject(std::string objectPath, std::vector<glm::vec3> & out_vertices, std::vector<glm::vec2> & out_uvs, std::vector<glm::vec3> & out_normals);

	private:
		static TextureCache _textureCache;
		static ImageLoader _imageLoader;
		static ObjectLoader _objectLoader;

	};

}