#pragma once

#include <GL/glew.h>

//Using a position struct to allow us to have cleaner and more understandable code
//by utilizing composition.
struct Position {
	float x;
	float y;
};

struct Colour {
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
} colour;

struct UV {
	float u;
	float v;
};

struct Vertex {

	Position position;

	//4 byte struct for colour
	Colour colour;

	//UV texture coordinates 
	UV uv;

	void setPosition(float x, float y) {
		position.x = x;
		position.y = y;
	}

	void setColour(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
		colour.r = r;
		colour.g = g;
		colour.b = b;
		colour.a = a;
	}

	void setUV(float u, float v) {
		uv.u = u;
		uv.v = v;
	}
};