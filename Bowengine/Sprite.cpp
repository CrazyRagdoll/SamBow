#include "Sprite.h"
#include "Vertex.h"
#include "ResourceManager.h"

#include <cstddef>

namespace Bowengine {

	Sprite::Sprite()
	{
		_vboID = 0;
	}


	Sprite::~Sprite()
	{
		//Delete the buffers when used
		if (_vboID != 0) {
			glDeleteBuffers(1, &_vboID);
		}
	}

	//Spirte initalise function. Initalising the VBO, x, y, width, height.
	void Sprite::init(float x, float y, float width, float height, std::string texturePath) {
		_x = x;
		_y = y;
		_width = width;
		_height = height;

		_texture = ResourceManager::getTexture(texturePath);

		//Generate the buffer
		if (_vboID == 0) {
			glGenBuffers(1, &_vboID);
		}

		Vertex vertexData[6];

		//First tiangle
		vertexData[0].setPosition(x + width, y + height);
		vertexData[0].setUV(1.0f, 1.0f);

		vertexData[1].setPosition(x, y + height);
		vertexData[1].setUV(0.0f, 1.0f);

		vertexData[2].setPosition(x, y);
		vertexData[2].setUV(0.0f, 0.0f);

		//Second triangle
		vertexData[3].setPosition(x, y);
		vertexData[3].setUV(0.0f, 0.0f);

		vertexData[4].setPosition(x + width, y);
		vertexData[4].setUV(1.0f, 0.0f);

		vertexData[5].setPosition(x + width, y + height);
		vertexData[5].setUV(1.0f, 1.0f);


		for (int i = 0; i < 6; i++) {
			vertexData[i].setColour(255, 0, 255, 255);
		}

		vertexData[1].setColour(0, 0, 255, 255);

		vertexData[4].setColour(0, 255, 0, 255);

		//Bind the buffer to ARRAY_BUFFER with our ID
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		//Tell the buffer what it will be drawing
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
		//Unbind the buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	//sprite draw function
	void Sprite::draw() {

		//Bind the texture to the sprite.
		glBindTexture(GL_TEXTURE_2D, _texture.id);

		//Binding the buffer again - You can only have one bound at at time
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);

		//Enable attrib array
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//This is the position attribute pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

		//This is the colour attribute pointer
		glVertexAttribPointer(1, 3, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, colour));

		//This is the UV attribute pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		//Draw the 6 verticies to the screen
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//Disable attrid array
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		//Unbind the buffer again
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

}