#pragma once
#include <GL/glew.h>


class Sprite
{
public:
	Sprite();
	~Sprite();

	//Spirte initalise function
	void init(float x, float y, float width, float height);

	//sprite draw function
	void draw();

private:
	//Dimentions and position of sprite
	float _x, _y, _width, _height;
	//GL int garanteed to be 32bits.
	GLuint _vboID;

};

