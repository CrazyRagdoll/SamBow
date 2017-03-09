#include "Sprite.h"
#include "Vertex.h"

#include <cstddef>

Sprite::Sprite()
{
	_vboID = 0;
}


Sprite::~Sprite()
{
	if (_vboID != 0) {
		glDeleteBuffers(1, &_vboID);
	}
}

//Spirte initalise function
void Sprite::init(float x, float y, float width, float height) {
	_x = x; _y = y; _width = width; _height = height;

	//Generate the buffer
	if (_vboID == 0) {
		glGenBuffers(1, &_vboID);
	}

	Vertex vertexData[6];

	//First tiangle
	vertexData[0].position.x = x + width;
	vertexData[0].position.y = y + height;

	vertexData[1].position.x = x;
	vertexData[1].position.y = y + height;

	vertexData[2].position.x = x;
	vertexData[2].position.y = y;

	//Second triangle
	vertexData[3].position.x = x;
	vertexData[3].position.y = y;

	vertexData[4].position.x = x + width;
	vertexData[4].position.y = y;

	vertexData[5].position.x = x + width;
	vertexData[5].position.y = y + height;

	for (int i = 0; i < 6; i++) {
		vertexData[i].colour.r = 255;
		vertexData[i].colour.g = 0;
		vertexData[i].colour.b = 255;
		vertexData[i].colour.a = 255;
	}

	vertexData[1].colour.r = 0;
	vertexData[1].colour.g = 0;
	vertexData[1].colour.b = 255;
	vertexData[1].colour.a = 255;

	vertexData[4].colour.r = 255;
	vertexData[4].colour.g = 0;
	vertexData[4].colour.b = 0;
	vertexData[4].colour.a = 255;

	//Bind the buffer to ARRAY_BUFFER with our ID
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	//Tell the buffer what it will be drawing
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	//Unbind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

//sprite draw function
void Sprite::draw() {
	//Binding the buffer again - You can only have one bound at at time
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	//Enable attrib array
	glEnableVertexAttribArray(0);

	//This is the position attribute pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	//This is the colour attribute pointer
	glVertexAttribPointer(1, 3, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, colour));

	//Draw the 6 verticies to the screen
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Disable attrid array
	glDisableVertexAttribArray(0);

	//Unbind the buffer again
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}