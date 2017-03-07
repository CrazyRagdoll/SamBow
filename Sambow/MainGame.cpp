#include "MainGame.h"

#include <iostream>
#include <string>

void fatalError(std::string errorString) {
	std::cout << errorString << std::endl;
	std::cout << "Enter any key to quit...";
	int tmp;
	std::cin >> tmp;
	SDL_Quit();
}

MainGame::MainGame()
{
	_window = nullptr;
	_screenWidth = 1024;
	_screenHeight = 768;
	_gameState = GameState::PLAY;
}


MainGame::~MainGame()
{
}


//Run the game
void MainGame::run() {
	initSystems();

	_sprite.init(-1.0f, -1.0f, 1.0f, 1.0f);

	gameLoop();
}


//Inialise everything needed to run the game
void MainGame::initSystems() {
	//initalise SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	//Create an SDL window
	_window = SDL_CreateWindow("SamBow Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
	if (_window == nullptr) {
		fatalError("SDL Window could no be created!");
	}

	//Set up our OpenGL context
	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr) {
		fatalError("SDL_GL context could not be created!");
	}

	//Set up glew (optional but recommended)
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		fatalError("Could not initialize glew!");
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

}


//The main game loop which will do all of the magic.
void MainGame::gameLoop(){
	while (_gameState != GameState::EXIT) {
		processInput();
		drawGame();
	}
}


//Processing input from the user
void MainGame::processInput() {

	SDL_Event evnt;

	while (SDL_PollEvent(&evnt)) {	//While there is an event (returning 1/true)
		switch (evnt.type) {		//Which type of event was it.
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
			break;
		}
	}
}

void MainGame::drawGame() {		//Draw content to the game
	glClearDepth(1.0);
	//Clear the colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_sprite.draw();

	//Swap our buffer and draw everything to the screen
	SDL_GL_SwapWindow(_window);
}