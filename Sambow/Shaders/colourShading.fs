#version 130
//The fragment shader operates on each pixel in a given polygon

in vec3 fragmentPosition;
in vec4 fragmentColour;
in vec2 fragmentUV;

//This is a component float vector that gets outputted to the screen
out vec4 colour;

//Used to make crazy colours
//uniform float time;

uniform sampler2D mySampler;

void main() {
	//Taking the colour from the vertex shader
	
	vec4 textureColour = texture(mySampler, fragmentUV);
	
	//colour = fragmentColour * time;
	colour = textureColour * fragmentColour;
	
	
	
}