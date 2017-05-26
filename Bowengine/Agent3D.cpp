#include "Agent3D.h"
#include "ResourceManager.h"
#include "Vertex.h"

#include <cstddef>
#include <iostream>

namespace Bowengine {

	Agent3D::Agent3D() {
		_vboID = 0;
	}

	Agent3D::~Agent3D() {
		//Delete the buffers when used
		if (_vboID != 0) {
			glDeleteBuffers(1, &_vboID);
		}
	}

	void Agent3D::init(std::string objectPath, std::string texturePath) {

		//Call the load Object function
		Bowengine::ResourceManager::loadObject(objectPath, _vertices, _uvs, _normals);

		//Generate the buffer
		if (_vboID == 0) {
			glGenBuffers(1, &_vboID);
		}

		//Grabbing the texture from the filepath
		if (texturePath != "") {
			_texture = ResourceManager::getTexture(texturePath);
		}
		else {
			_texture.id = 0;
		}

		//Creating a dynamic array
		VertexOBJ* vertexData;
		_vertexAmount = _vertices.size();
		vertexData = new VertexOBJ[_vertexAmount];

		//Hard coded in the size of the object
		//VertexOBJ vertexData[36];

		//Filling our object data into the vertexData
		for (int i = 0; i < _vertices.size(); i++) {
			vertexData[i].setVerticies(_vertices[i].x, _vertices[i].y, _vertices[i].z);
			vertexData[i].setUV(_uvs[i].x, _uvs[i].y);
			vertexData[i].setNormals(_normals[i].x, _normals[i].y, _normals[i].z);
		}

		//Declaring the size of the vertex (cant use sizeof(vertexData) due to it now being a dynamic array aka a pointer
		_vertexSize = sizeof(VertexOBJ) * _vertexAmount;

		//Bind the buffer to ARRAY_BUFFER with our ID
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		//Tell the buffer what it will be drawing
		glBufferData(GL_ARRAY_BUFFER, _vertexSize, vertexData, GL_STATIC_DRAW);
		//Unbind the buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		delete[] vertexData;

	}

	//Draw some objects woo
	void Agent3D::draw() {

		//Bind the texture to the object.
		glBindTexture(GL_TEXTURE_2D, _texture.id);

		//Binding the buffer again - You can only have one bound at at time
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);

		//Enable attrib array
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//This is the vertex attribute pointer
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexOBJ), (void*)offsetof(VertexOBJ, vertices));

		//This is the uv attribute pointer
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexOBJ), (void*)offsetof(VertexOBJ, uv));

		//This is the normals attribute pointer
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexOBJ), (void*)offsetof(VertexOBJ, normals));

		//Draw all of the vertices to the screen
		glDrawArrays(GL_TRIANGLES, 0, _vertices.size());

		//Disable attrid array
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		//Unbind the buffer again
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

}
