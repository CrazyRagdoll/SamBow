#include "IOManager.h"

#include <fstream>

bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer) {
	//reading the file in as binary
	std::ifstream file(filePath, std::ios::binary);
	//error checking
	if (file.fail()) {
		perror(filePath.c_str());
		return false;
	}

	//seek to the end of the file
	file.seekg(0, std::ios::end);

	//Get the file size
	int fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	//Reduce the file size by any header bytes that might be present
	fileSize -= file.tellg();

	//resize the buffer to the file size
	buffer.resize(fileSize);
	//Reads a number of bytes into a buffer
	file.read((char *)&(buffer[0]), fileSize);
	//Close the file
	file.close();

	return true;

}