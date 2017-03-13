#include "MainGame.h"
#include "Errors.h"
#include "ImageLoader.h"

#include <iostream>
#include <string>

MainGame::MainGame() : 
		_window(nullptr), 
		_screenWidth(1024), 
		_screenHeight(768), 
		_gameState(GameState::PLAY), 
		_time(0)
{

}


MainGame::~MainGame()
{
}


//Run the game
void MainGame::run() {
	//initalise the systems
	initSystems();

	//hard code the sprite into the game (Bad)
	_sprite.init(-1.0f, -1.0f, 2.0f, 2.0f);

	_playerTexture = ImageLoader::loadPNG("Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");

	//Run the game loop
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

	//Set OpenGL to use double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//Clear the background
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	//initalise the shaders
	initShaders();

}

void MainGame::initShaders() {
	//Using colour program to compile, init, and link our fragment + vertex shaders
	_colourProgram.compileShaders("Shaders/colourShading.vert", "Shaders/colourShading.frag");
	_colourProgram.addAttribute("vertexPosition");
	_colourProgram.addAttribute("vertexColour");
	_colourProgram.addAttribute("VertexUV");
	_colourProgram.linkShaders();
}


//The main game loop which will do all of the magic.
void MainGame::gameLoop(){
	while (_gameState != GameState::EXIT) {
		processInput();
		_time += 0.05;
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

	_colourProgram.use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _playerTexture.id);
	GLint textureLocation = _colourProgram.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	GLint timeLocation = _colourProgram.getUniformLocation("time");
	glUniform1f(timeLocation, _time);

	//draw the sprite
	_sprite.draw();

	glBindTexture(GL_TEXTURE_2D, 0);
	_colourProgram.unuse();

	//Swap our buffer and draw everything to the screen
	SDL_GL_SwapWindow(_window);
}