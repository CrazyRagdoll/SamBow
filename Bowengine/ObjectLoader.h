#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

namespace Bowengine {

	class ObjectLoader
	{
	public:

		bool loadOBJ(std::string path, std::vector<glm::vec3> & out_vertices, std::vector<glm::vec2> & out_uvs, std::vector<glm::vec3> & out_normals); 

	};

}