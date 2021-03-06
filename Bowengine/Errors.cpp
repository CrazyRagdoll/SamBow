#include "Errors.h"

#include <cstdlib>

#include <iostream>
#include <SDL/SDL.h>

namespace Bowengine {

	//Prints an error
	void fatalError(std::string errorString) {
		std::cout << errorString << std::endl;
		std::cout << "Enter any key to quit...";
		int tmp;
		std::cin >> tmp;
		SDL_Quit();		//Close all SDL operations
		exit(69);		//Close the program
	}
}