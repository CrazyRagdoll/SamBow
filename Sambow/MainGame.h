#pragma once  //Protects you from circular includes
#include <Windows.h>

#include <SDL/SDL.h>
#include <GL/glew.h>

#include "GLSLProgram.h"
#include "GLTexture.h"

#include "Sprite.h"

#include <vector>

enum class GameState{PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	//Run the game
	void run();

private:
	void initSystems();		//Inialise everything needed to run the game
	void initShaders();
	void gameLoop();		//The main game loop which will do all of the magic.
	void processInput();	//Processing input from the user
	void drawGame();		//Draw content to the game
	void calculateFPS();	//Calculate the fps of the game

	SDL_Window* _window;	//The instance of the SDL_Window
	int _screenWidth;		//Screen's width
	int _screenHeight;		//Screen's height
	GameState _gameState;	//Current state of the game (enum class)

	std::vector <Sprite*> _sprites;

	GLSLProgram _colourProgram;

	//FPS calculating variables
	float _fps, _maxFPS, _frameTime;

	//Make shift time variable
	float _time;

};

