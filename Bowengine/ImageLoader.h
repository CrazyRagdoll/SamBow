#pragma once

#include "GLTexture.h"

#include <string>

namespace Bowengine {

	class ImageLoader
	{
	public:

		static GLTexture loadImage(std::string filePath);
		static GLTexture loadPNG(std::string filePath);
		static GLTexture loadBMP(std::string filePath);

	};

}