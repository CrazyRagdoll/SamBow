#include "MainGame.h"

#include <iostream>


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

	gameLoop();
}


//Inialise everything needed to run the game
void MainGame::initSystems() {
	//initalise SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	//Create an SDL window
	_window = SDL_CreateWindow("SamBow Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
}


//The main game loop which will do all of the magic.
void MainGame::gameLoop(){
	while (_gameState != GameState::EXIT) {
		processInput();
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