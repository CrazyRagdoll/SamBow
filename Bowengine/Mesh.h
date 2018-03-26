#pragma once

#include <vector>

#include "Vertex.h"

using namespace std;

namespace Bowengine {

	class Mesh
	{
	public:
		//Mesh Functions
		Mesh(vector<VertexOBJ> vertices, vector<unsigned int> indices, vector<Texture> textures);
		~Mesh();

		void setupMesh();

		void draw();

	private:
		//Mesh date
		vector<VertexOBJ> _vertices;
		vector<unsigned int> _indices;
		vector<Texture> _textures;

		//GL int garanteed to be 32bits.
		GLuint _vaoID, _vboID, _eboID;

	};

}