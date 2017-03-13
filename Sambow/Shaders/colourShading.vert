#version 130
//The vertex shader operates on each vertex

//input data from the VBO. Each vertex is 2 floats
in vec2 vertexPosition;
in vec4 vertexColour;
in vec2 vertexUV;

out vec2 fragmentPosition;
out vec4 fragmentColour;
out vec2 fragmentUV;

void main() {
	//Set the x,y position on the screen
	gl_Position.xy = vertexPosition;
	//the z position is zero at the moment since we are in 2D
	gl_Position.z = 0.0;
	
	//Indicate that the coordinates are normalized
	gl_Position.w = 1.0;
	
	fragmentPosition = vertexPosition;
	
	fragmentColour = vertexColour;
	
	fragmentUV = vec2(vertexUV.x, 1.0 - vertexUV.y);
}