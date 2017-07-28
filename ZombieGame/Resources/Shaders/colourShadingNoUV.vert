#version 130
//The vertex shader operates on each vertex

//input data from the VBO. Each vertex is 2 floats
in vec3 vertexPosition;
in vec4 vertexColour;

out vec3 fragmentPosition;
out vec4 fragmentColour;

//Orthographic matrix
uniform mat4 P;

void main() {
	//Set the x,y position on the screen
	gl_Position = P * vec4(vertexPosition, 1.0);
		
	fragmentPosition = vertexPosition;
	
	fragmentColour = vertexColour;
	
}