#pragma once

#include <vector>

namespace Bowengine {

	//Static class, there will only be one instance of this class. There is no reason to have multiple readers
	class IOManager
	{
	public:
		static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
	};

}