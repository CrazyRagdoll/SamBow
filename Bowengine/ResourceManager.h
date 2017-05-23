#pragma once

#include "TextureCache.h"
#include "ImageLoader.h"

#include <string>

namespace Bowengine {

	class ResourceManager
	{
	public:
		static GLTexture getTexture(std::string texturePath);
		static GLTexture getBMPTexture(std::string texturePath);

	private:
		static TextureCache _textureCache;
		static ImageLoader _imageLoader;
	};

}