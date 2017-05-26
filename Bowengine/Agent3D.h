#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

#include "GLTexture.h"

namespace Bowengine {

	class Agent3D
	{
	public:

		Agent3D();
		~Agent3D();

		void init(std::string objectPath, std::string texturePath);

		void draw();

	private:

		//GL int garanteed to be 32bits.
		GLuint _vboID;

		int _vertexSize, _vertexAmount;

		std::vector<glm::vec3> _vertices, _normals;
		std::vector<glm::vec2> _uvs;

		//Used to hold the agents's texture
		GLTexture _texture;
	};

}