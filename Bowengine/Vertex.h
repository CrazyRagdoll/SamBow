#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace Bowengine {

	//Using a position struct to allow us to have cleaner and more understandable code
	//by utilizing composition.
	struct Position {
		float x;
		float y;
		float z;
	};

	struct Colour {
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	};

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

	struct Vertex3D {

		Position position;

		//4 byte struct for colour
		Colour colour;

		//UV texture coordinates 
		UV uv;

		void setPosition(float x, float y, float z) {
			position.x = x;
			position.y = y;
			position.z = z;
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

		void setPosXYZ(glm::vec3 pos) {
			position.x = pos.x;
			position.y = pos.y;
			position.z = pos.z;
		}

	};

	//Making a struct for our simple object loader
	struct VertexOBJ {

		Position vertices, normals;

		UV uv;

		void setVerticies(float x, float y, float z) {
			vertices.x = x;
			vertices.y = y;
			vertices.z = z;
		}

		void setUV(float u, float v) {
			uv.u = u;
			uv.v = v;
		}
		
		void setNormals(float x, float y, float z) {
			normals.x = x;
			normals.y = y;
			normals.z = z;
		}

	};

}