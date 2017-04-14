#include "Cube.h"

#include "Vertex.h"
#include "ResourceManager.h"

#include <cstddef>

namespace Bowengine {

	Cube::Cube()
	{
		_vboID = 0;
	}


	Cube::~Cube()
	{
		//Delete the buffers when used
		if (_vboID != 0) {
			glDeleteBuffers(1, &_vboID);
		}
	}


	void Cube::init(glm::vec3 position, float width, float height, float depth, std::string filePath) {
		//Setting the position and size variables
		_position = position;
		_width = width; _height = height; _depth = depth;

		if (filePath != "") {
			_texture = ResourceManager::getTexture(filePath);
		}
		else {
			_texture.id = 0;
		}


		//Generate the buffer
		if (_vboID == 0) {
			glGenBuffers(1, &_vboID);
		}

		//Define all 8 corners beforehand T=Top, B=Bottm, L=Left, R=Right
		glm::vec3 FrontTL = glm::vec3(_position.x - _width / 2, _position.y + _height / 2, _position.z + _depth / 2);
		glm::vec3 FrontBL = glm::vec3(_position.x - _width / 2, _position.y - _height / 2, _position.z + _depth / 2);
		glm::vec3 FrontTR = glm::vec3(_position.x + _width / 2, _position.y + _height / 2, _position.z + _depth / 2);
		glm::vec3 FrontBR = glm::vec3(_position.x + _width / 2, _position.y - _height / 2, _position.z + _depth / 2);

		glm::vec3 BackTL = glm::vec3(_position.x - _width / 2, _position.y + _height / 2, _position.z - _depth / 2);
		glm::vec3 BackBL = glm::vec3(_position.x - _width / 2, _position.y - _height / 2, _position.z - _depth / 2);
		glm::vec3 BackTR = glm::vec3(_position.x + _width / 2, _position.y + _height / 2, _position.z - _depth / 2);
		glm::vec3 BackBR = glm::vec3(_position.x + _width / 2, _position.y - _height / 2, _position.z - _depth / 2);

		//A cube is 6 faces of 2 triangles with 3 vertices each: 3*2*6 = 36
		Vertex3D vertexData[36];

		//Front face
		vertexData[0].setPosition(FrontTL.x, FrontTL.y, FrontTL.z);		//Front Top Left
		vertexData[0].setUV(1.0f, 0.0f);
		vertexData[1].setPosition(FrontBL.x, FrontBL.y, FrontBL.z);		//Front Bottom Left
		vertexData[2].setPosition(FrontBR.x, FrontBR.y, FrontBR.z);		//Front Bottom Right

		vertexData[3].setPosition(FrontBR.x, FrontBR.y, FrontBR.z);		//Front Bottom Right
		vertexData[4].setPosition(FrontTR.x, FrontTR.y, FrontTR.z);		//Front Top Right
		vertexData[5].setPosition(FrontTL.x, FrontTL.y, FrontTL.z);		//Front Top Left

		//Right face
		vertexData[6].setPosition(FrontTR.x, FrontTR.y, FrontTR.z);		//Front Top Right
		vertexData[7].setPosition(FrontBR.x, FrontBR.y, FrontBR.z);		//Front Bottom Right
		vertexData[8].setPosition(BackBR.x, BackBR.y, BackBR.z);		//Back Bottom Right

		vertexData[9].setPosition(BackBR.x, BackBR.y, BackBR.z);		//Back Bottom Right
		vertexData[10].setPosition(BackTR.x, BackTR.y, BackTR.z);		//Front Top Right
		vertexData[11].setPosition(FrontTR.x, FrontTR.y, FrontTR.z);	//Front Top Right

		//Back face
		vertexData[12].setPosition(BackTR.x, BackTR.y, BackTR.z);		//Back Top Right
		vertexData[13].setPosition(BackBR.x, BackBR.y, BackBR.z);		//Back Bottom Right
		vertexData[14].setPosition(BackBL.x, BackBL.y, BackBL.z);		//Back Bottom Left

		vertexData[15].setPosition(BackBL.x, BackBL.y, BackBL.z);		//Back Bottom Left
		vertexData[16].setPosition(BackTL.x, BackTL.y, BackTL.z);		//Back Top Left
		vertexData[17].setPosition(BackTR.x, BackTR.y, BackTR.z);		//Back Top Right

		//Left face
		vertexData[18].setPosition(BackTL.x, BackTL.y, BackTL.z);		//Back Top Left
		vertexData[19].setPosition(BackBL.x, BackBL.y, BackBL.z);		//Back Bottom Left
		vertexData[20].setPosition(FrontBL.x, FrontBL.y, FrontBL.z);	//Front Bottom Left

		vertexData[21].setPosition(FrontBL.x, FrontBL.y, FrontBL.z);	//Front Bottom Left
		vertexData[22].setPosition(FrontTL.x, FrontTL.y, FrontTL.z);	//Front Top Left
		vertexData[23].setPosition(BackTL.x, BackTL.y, BackTL.z);		//Back Top Left

		//Top face
		vertexData[24].setPosition(BackTL.x, BackTL.y, BackTL.z);		//Back Top Left
		vertexData[25].setPosition(FrontTL.x, FrontTL.y, FrontTL.z);	//Front Top Left
		vertexData[26].setPosition(FrontTR.x, FrontTR.y, FrontTR.z);	//Front Top Right

		vertexData[27].setPosition(FrontTR.x, FrontTR.y, FrontTR.z);	//Front Top Right
		vertexData[28].setPosition(BackTR.x, BackTR.y, BackTR.z);		//Back Top Right
		vertexData[29].setPosition(BackTL.x, BackTL.y, BackTL.z);		//Back Top Left

		//Bottom face
		vertexData[30].setPosition(FrontBL.x, FrontBL.y, FrontBL.z);	//Front Bottom Left
		vertexData[31].setPosition(BackBL.x, BackBL.y, BackBL.z);		//Back Bottom Left
		vertexData[32].setPosition(BackBR.x, BackBR.y, BackBR.z);		//Back Bottom Right

		vertexData[33].setPosition(BackBR.x, BackBR.y, BackBR.z);		//Back Bottom Right
		vertexData[34].setPosition(FrontBR.x, FrontBR.y, FrontBR.z);	//Front Bottom Right
		vertexData[35].setPosition(FrontBL.x, FrontBL.y, FrontBL.z);	//Front Bototm Left 

		_vertexSize = sizeof(vertexData);

		for (int i = 0; i < 36; i++) {
			vertexData[i].setColour(255, 0, 0, 255);
		}

		for (int i = 0; i < 36; i++) {
			vertexData[i].setUV(1.0f, 0.0f);
		}

		//Bind the buffer to ARRAY_BUFFER with our ID
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		//Tell the buffer what it will be drawing
		glBufferData(GL_ARRAY_BUFFER, _vertexSize, vertexData, GL_STATIC_DRAW);
		//Unbind the buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0); 

	}


	void Cube::draw() {

		//Bind the texture to the sprite.
		glBindTexture(GL_TEXTURE_3D, _texture.id);

		//Binding the buffer again - You can only have one bound at at time
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);

		//Enable attrib array
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//This is the position attribute pointer
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, position));

		//This is the colour attribute pointer
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, colour));

		//This is the UV attribute pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, uv));

		//Draw the 6 verticies to the screen
		glDrawArrays(GL_TRIANGLES, 0, _vertexSize);

		//Disable attrid array
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		//Unbind the buffer again
		glBindBuffer(GL_ARRAY_BUFFER, 0); 


	}

}