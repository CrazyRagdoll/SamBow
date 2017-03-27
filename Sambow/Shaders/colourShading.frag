#version 130
//The fragment shader operates on each pixel in a given polygon

in vec2 fragmentPosition;
in vec4 fragmentColour;
in vec2 fragmentUV;

//This is a component float vector that gets outputted to the screen
out vec4 colour;

//uniform float time;
uniform sampler2D mySampler;

void main() {
	//Taking the colour from the vertex shader
	//colour = fragmentColour;
	
	vec4 textureColour = texture(mySampler, fragmentUV);
	
	colour = textureColour * fragmentColour;
	
	//Making crazy looking colours using time and position variables
	//colour = vec4(fragmentColour.r * (cos(fragmentPosition.x * 4.0 + time) + 1) * 0.5,
	//			  fragmentColour.g * (cos(fragmentPosition.y * 8.0 + time) + 1) * 0.5,
	//			fragmentColour.b * (cos(fragmentPosition.x*0.4 * 2.0 + time) + 1) * 0.5, fragmentColour.a) * textureColour;
}