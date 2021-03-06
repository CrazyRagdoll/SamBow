#include "ImageLoader.h"
#include "picoPNG.h"
#include "IOManager.h"
#include "Errors.h"
#include <iostream>

namespace Bowengine {

	GLTexture ImageLoader::loadImage(std::string filePath) {

		//Grab the extension
		std::string extension = filePath;
		std::string ext4 = "";	//A 4 character long extension ".png"

		//A for loop to grab the last4 characters
		for (int i = 4; i > 0; i--) {
			ext4 += extension.at(extension.size() - i);
		}

		if (ext4 == ".png") {
			return loadPNG(filePath);
		}
		else if (ext4 == ".bmp") {
			return loadBMP(filePath);
		}
		else if (ext4 == ".dds") {
			/*return loadDDS(filePath);*/
		} else {
			fatalError("Unknown File Path");
		}

	}

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

		//return a copy of the texture data
		return texture;
	}

	GLTexture ImageLoader::loadBMP(std::string filePath) {
		// Create one OpenGL texture
		GLTexture texture = {};

		//Loading function
		GLuint loadBMP(const char * filePath);

		// Data read from the header of the BMP file
		unsigned char header[54]; // Each BMP file begins by a 54-bytes header
		unsigned int dataPos;     // Position in the file where the actual data begins
		unsigned int width, height;
		unsigned int imageSize;   // = width*height*3
								  // Actual RGB data
		unsigned char * data;

		// Open the file
		FILE * file;
		std::cout << filePath.c_str();

		errno_t errorCode = fopen_s(&file, filePath.c_str(), "rb");
		if (errorCode != 0) {
			fatalError("File opener failed with error: " + std::to_string(errorCode));
		}

		if (fread(header, 1, 54, file) != 54) { // If not 54 bytes read : problem
			fatalError("Not correct BMP file format");
		}

		if (header[0] != 'B' || header[1] != 'M') {	//More error checking - BMP files have B and M as their first values
			fatalError("Not correct BMP file format");
		}

		// Read ints from the byte array
		dataPos = *(int*)&(header[0x0A]);
		imageSize = *(int*)&(header[0x22]);
		width = *(int*)&(header[0x12]);
		height = *(int*)&(header[0x16]);

		// Some BMP files are misformatted, guess missing information
		if (imageSize == 0)    imageSize = width*height * 3; // 3 : one byte for each Red, Green and Blue component
		if (dataPos == 0)      dataPos = 54; // The BMP header is done that way

		// Create a buffer
		data = new unsigned char[imageSize];

		// Read the actual data from the file into the buffer
		fread(data, 1, imageSize, file);

		//Everything is in memory now, the file can be closed
		fclose(file);

		//generate the openGL texture object 
		glGenTextures(1, &(texture.id));

		// "Bind" the newly created texture : all future texture functions will modify this texture
		glBindTexture(GL_TEXTURE_2D, texture.id);

		// Give the image to OpenGL
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

		//Set some texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// When MAGnifying the image (no bigger mipmap available), use LINEAR filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// When MINifying the image, use a LINEAR blend of two mipmaps, each filtered LINEARLY too
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		// Generate mipmaps, by the way.
		glGenerateMipmap(GL_TEXTURE_2D);

		//Unbind the texture
		glBindTexture(GL_TEXTURE_2D, 0);

		//return a copy of the texture data
		return texture;

	}

	/*
	#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
	#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
	#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

	GLTexture loadDDS(std::string filepath) {
		
		// Create one OpenGL texture
		GLTexture texture = {};

		unsigned char header[124];

		FILE * file;

		// try to open the file 
		errno_t errorCode = fopen_s(&file, filepath.c_str(), "rb");
		if (errorCode != 0) {
			fatalError("File opener failed with error: " + std::to_string(errorCode));
		}

		// get the surface desc 
		fread(&header, 124, 1, file);

		unsigned int height = *(unsigned int*)&(header[8]);
		unsigned int width = *(unsigned int*)&(header[12]);
		unsigned int linearSize = *(unsigned int*)&(header[16]);
		unsigned int mipMapCount = *(unsigned int*)&(header[24]);
		unsigned int fourCC = *(unsigned int*)&(header[80]);


		unsigned char * buffer;
		unsigned int bufsize;
		// how big is it going to be including all mipmaps? 
		bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
		buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
		fread(buffer, 1, bufsize, file);
		// close the file pointer 
		fclose(file);

		unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
		unsigned int format;
		switch (fourCC)
		{
		case FOURCC_DXT1:
			format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
			break;
		case FOURCC_DXT3:
			format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
			break;
		case FOURCC_DXT5:
			format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
			break;
		default:
			free(buffer);
		}

		// Create one OpenGL texture
		glGenTextures(1, &texture.id);

		// "Bind" the newly created texture : all future texture functions will modify this texture
		glBindTexture(GL_TEXTURE_2D, texture.id);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
		unsigned int offset = 0;

		// load the mipmaps
		for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
		{
			unsigned int size = ((width + 3) / 4)*((height + 3) / 4)*blockSize;
			glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
				0, size, buffer + offset);

			offset += size;
			width /= 2;
			height /= 2;

			// Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
			if (width < 1) width = 1;
			if (height < 1) height = 1;

		}

		free(buffer);

		return texture;

	} */

}