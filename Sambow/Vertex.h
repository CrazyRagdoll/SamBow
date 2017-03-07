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

struct Vertex {

	Position position;

	//4 byte struct for colour
	Colour colour;
};