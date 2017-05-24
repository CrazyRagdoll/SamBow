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
		glm::vec3 FrontTL = glm::vec3(_position.x - _width / 2, _position.y + _height / 2, _position.z + _depth / 2);	// -1,  1,  1
		glm::vec3 FrontBL = glm::vec3(_position.x - _width / 2, _position.y - _height / 2, _position.z + _depth / 2);	// -1, -1,  1
		glm::vec3 FrontTR = glm::vec3(_position.x + _width / 2, _position.y + _height / 2, _position.z + _depth / 2);	//  1,  1,  1
		glm::vec3 FrontBR = glm::vec3(_position.x + _width / 2, _position.y - _height / 2, _position.z + _depth / 2);	//  1, -1,  1

		glm::vec3 BackTL = glm::vec3(_position.x - _width / 2, _position.y + _height / 2, _position.z - _depth / 2);	// -1,  1, -1
		glm::vec3 BackBL = glm::vec3(_position.x - _width / 2, _position.y - _height / 2, _position.z - _depth / 2);	// -1, -1, -1
		glm::vec3 BackTR = glm::vec3(_position.x + _width / 2, _position.y + _height / 2, _position.z - _depth / 2);	//  1,  1, -1
		glm::vec3 BackBR = glm::vec3(_position.x + _width / 2, _position.y - _height / 2, _position.z - _depth / 2);	//  1, -1, -1

		//A cube is 6 faces of 2 triangles with 3 vertices each: 3*2*6 = 36
		Vertex3D vertexData[36];

		vertexData[0].setPosXYZ(glm::vec3(-1.0f, -1.0f, -1.0f));	
		vertexData[1].setPosXYZ(glm::vec3(-1.0f, -1.0f, 1.0f));		
		vertexData[2].setPosXYZ(glm::vec3(-1.0f, 1.0f, 1.0f));	

		vertexData[3].setPosXYZ(glm::vec3(1.0f, 1.0f, -1.0f));
		vertexData[4].setPosXYZ(glm::vec3(-1.0f, -1.0f, -1.0f));
		vertexData[5].setPosXYZ(glm::vec3(-1.0f, 1.0f, -1.0f));	

		vertexData[6].setPosXYZ(glm::vec3(1.0f, -1.0f, 1.0f));	
		vertexData[7].setPosXYZ(glm::vec3(-1.0f, -1.0f, -1.0f));	
		vertexData[8].setPosXYZ(glm::vec3(1.0f, -1.0f, -1.0f));

		vertexData[9].setPosXYZ(glm::vec3(1.0f, 1.0f, -1.0f));
		vertexData[10].setPosXYZ(glm::vec3(1.0f, -1.0f, -1.0f));	
		vertexData[11].setPosXYZ(glm::vec3(-1.0f, -1.0f, -1.0f));	

		vertexData[12].setPosXYZ(glm::vec3(-1.0f, -1.0f, -1.0f));	
		vertexData[13].setPosXYZ(glm::vec3(-1.0f, 1.0f, 1.0f));		
		vertexData[14].setPosXYZ(glm::vec3(-1.0f, 1.0f, -1.0f));	

		vertexData[15].setPosXYZ(glm::vec3(1.0f, -1.0f, 1.0f));	
		vertexData[16].setPosXYZ(glm::vec3(-1.0f, -1.0f, 1.0f));	
		vertexData[17].setPosXYZ(glm::vec3(-1.0f, -1.0f, -1.0f));

		vertexData[18].setPosXYZ(glm::vec3(-1.0f, 1.0f, 1.0f));	
		vertexData[19].setPosXYZ(glm::vec3(-1.0f, -1.0f, 1.0f));	
		vertexData[20].setPosXYZ(glm::vec3(1.0f, -1.0f, 1.0f));	

		vertexData[21].setPosXYZ(glm::vec3(1.0f, 1.0f, 1.0f));	
		vertexData[22].setPosXYZ(glm::vec3(1.0f, -1.0f, -1.0f));
		vertexData[23].setPosXYZ(glm::vec3(1.0f, 1.0f, -1.0f));	

		vertexData[24].setPosXYZ(glm::vec3(1.0f, -1.0f, -1.0f));	
		vertexData[25].setPosXYZ(glm::vec3(1.0f, 1.0f, 1.0f));	
		vertexData[26].setPosXYZ(glm::vec3(1.0f, -1.0f, 1.0f));		

		vertexData[27].setPosXYZ(glm::vec3(1.0f, 1.0f, 1.0f));	
		vertexData[28].setPosXYZ(glm::vec3(1.0f, 1.0f, -1.0f));		
		vertexData[29].setPosXYZ(glm::vec3(-1.0f, 1.0f, -1.0f));	

		vertexData[30].setPosXYZ(glm::vec3(1.0f, 1.0f, 1.0f));	
		vertexData[31].setPosXYZ(glm::vec3(-1.0f, 1.0f, -1.0f));
		vertexData[32].setPosXYZ(glm::vec3(-1.0f, 1.0f, 1.0f));	

		vertexData[33].setPosXYZ(glm::vec3(1.0f, 1.0f, 1.0f));	
		vertexData[34].setPosXYZ(glm::vec3(-1.0f, 1.0f, 1.0f));	
		vertexData[35].setPosXYZ(glm::vec3(1.0f, -1.0f, 1.0f));	

		vertexData[0].setUV(0.000059f, 1.0f - 0.000004f);
		vertexData[1].setUV(0.000103f, 1.0f - 0.336048f);
		vertexData[2].setUV(0.335973f, 1.0f - 0.335903f);
		vertexData[3].setUV(1.000023f, 1.0f - 0.000013f);
		vertexData[4].setUV(0.667979f, 1.0f - 0.335851f);
		vertexData[5].setUV(0.999958f, 1.0f - 0.336064f);
		vertexData[6].setUV(0.667979f, 1.0f - 0.335851f);
		vertexData[7].setUV(0.336024f, 1.0f - 0.671877f);
		vertexData[8].setUV(0.667969f, 1.0f - 0.671889f);
		vertexData[9].setUV(1.000023f, 1.0f - 0.000013f);
		vertexData[10].setUV(0.668104f, 1.0f - 0.000013f);
		vertexData[11].setUV(0.667979f, 1.0f - 0.335851f);
		vertexData[12].setUV(0.000059f, 1.0f - 0.000004f);
		vertexData[13].setUV(0.335973f, 1.0f - 0.335903f);
		vertexData[14].setUV(0.336098f, 1.0f - 0.000071f);
		vertexData[15].setUV(0.667979f, 1.0f - 0.335851f);
		vertexData[16].setUV(0.335973f, 1.0f - 0.335903f);
		vertexData[17].setUV(0.336024f, 1.0f - 0.671877f);
		vertexData[18].setUV(1.000004f, 1.0f - 0.671847f);
		vertexData[19].setUV(0.999958f, 1.0f - 0.336064f);
		vertexData[20].setUV(0.667979f, 1.0f - 0.335851f);
		vertexData[21].setUV(0.668104f, 1.0f - 0.000013f);
		vertexData[22].setUV(0.335973f, 1.0f - 0.335903f);
		vertexData[23].setUV(0.667979f, 1.0f - 0.335851f);
		vertexData[24].setUV(0.335973f, 1.0f - 0.335903f);
		vertexData[25].setUV(0.668104f, 1.0f - 0.000013f);
		vertexData[26].setUV(0.336098f, 1.0f - 0.000071f);
		vertexData[27].setUV(0.000103f, 1.0f - 0.336048f);
		vertexData[28].setUV(0.000004f, 1.0f - 0.671870f);
		vertexData[29].setUV(0.336024f, 1.0f - 0.671877f);
		vertexData[30].setUV(0.000103f, 1.0f - 0.336048f);
		vertexData[31].setUV(0.336024f, 1.0f - 0.671877f);
		vertexData[32].setUV(0.335973f, 1.0f - 0.335903f);
		vertexData[33].setUV(0.667969f, 1.0f - 0.671889f);
		vertexData[34].setUV(1.000004f, 1.0f - 0.671847f);
		vertexData[35].setUV(0.667979f, 1.0f - 0.335851f);

		_vertexSize = sizeof(vertexData);

		for (int i = 0; i < 36; i++) {
			vertexData[i].setColour(255, 255, 255, 255);
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
		glBindTexture(GL_TEXTURE_2D, _texture.id);

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