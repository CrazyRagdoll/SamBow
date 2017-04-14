#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "GLTexture.h"

#include <string>

namespace Bowengine {

	class Cube
	{
	public:
		Cube();
		~Cube();

		//Cube init function
		void init(glm::vec3 position, float width, float height, float depth, std::string filePath);

		//Cube draw function
		void draw();

	private:

		int _vertexSize;

		//Cube position
		glm::vec3 _position;

		//Size floats
		float _width, _height, _depth;

		//GL int garanteed to be 32bits.
		GLuint _vboID;

		//Used to hold the cube's texture
		GLTexture _texture;

	};

}