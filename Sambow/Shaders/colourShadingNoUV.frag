#version 130
//The fragment shader operates on each pixel in a given polygon

in vec3 fragmentPosition;
in vec4 fragmentColour;

//This is a component float vector that gets outputted to the screen
out vec4 colour;

//Used to make crazy colours
uniform float time;

uniform sampler2D mySampler;

void main() {
	//Taking the colour from the vertex shader
	
	//colour = fragmentColour * time;
	colour = fragmentColour * time;
	
	
}