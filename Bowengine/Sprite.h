#pragma once
#include <GL/glew.h>

#include "GLTexture.h"

#include <string>

namespace Bowengine {

	//A 2D quad that can be rendered to screen
	class Sprite
	{
	public:
		Sprite();
		~Sprite();

		//Spirte initalise function
		void init(float x, float y, float width, float height, std::string texturePath);

		//sprite draw function
		void draw();

	private:
		//Dimentions and position of sprite
		float _x, _y, _width, _height;
		//GL int garanteed to be 32bits.
		GLuint _vboID;

		GLTexture _texture;

	};

}