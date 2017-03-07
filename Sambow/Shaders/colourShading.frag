#version 130
//The fragment shader operates on each pixel in a given polygon

//This is a component float vector that gets outputted to the screen
out vec3 colour;

void main() {
	//Hard coding the colour to red
	colour = vec3(1.0, 0.0, 1.0);
}