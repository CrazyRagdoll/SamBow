#include "ImageLoader.h"
#include "picoPNG.h"
#include "IOManager.h"
#include "Errors.h"

GLTexture ImageLoader::loadPNG(std::string filePath) {
	//Ceate a GLTexture and initalize all of its fields to 0
	GLTexture texture = {};

	//This is the input data to decodePNG, which we load from a file
	std::vector<unsigned char> in;
	//This is the output data from decodePNG, which is the pixel data for our texture
	std::vector<unsigned char> out;

	unsigned long width, height;

	//Read in the image file contents into a uffer
	if (IOManager::readFileToBuffer(filePath, in) == false) {
		fatalError("Failed to load PNG file to buffer!");
	}

	//Decode the .png format into an array of pixles + error checking
	int errorCode = decodePNG(out, width, height, &(in[0]), in.size(), true);
	if (errorCode != 0) {
		fatalError("decodePNG failed with error: " + std::to_string(errorCode));
	}

	//generate the openGL texture object 
	glGenTextures(1, &(texture.id));

	//Bind the texture
	glBindTexture(GL_TEXTURE_2D, texture.id);
	//Upload the pixels to the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

	//Set some texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//Generate the mipmaps
	glGenerateMipmap(GL_TEXTURE_2D);

	//Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);

	//Set the width and height of the GLTexture
	texture.width = width;
	texture.height = height;

	//returnm a copy of the texture data
	return texture;

}