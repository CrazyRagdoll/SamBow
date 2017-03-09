#pragma once

#include <vector>

//Static class, there will only be one instance of this class. There is no reason to have multiple readers
class IOManager
{
public:
	static bool readFileToBuffer(std::string filePath, std::vector<char>& buffer);
};

