#include <SDL/SDL.h>
#include <GL/glew.h>

#include "Bowengine.h"

namespace Bowengine {

	int init() {
		//initalise SDL
		SDL_Init(SDL_INIT_EVERYTHING);

		//Set OpenGL to use double buffering
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		return 0;
	}

}