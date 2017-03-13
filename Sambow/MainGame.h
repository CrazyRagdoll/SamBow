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
	void calculateFPS();

	SDL_Window* _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;

	std::vector <Sprite*> _sprites;

	GLSLProgram _colourProgram;

	float _fps;
	float _maxFPS;
	float _frameTime;


	float _time;

};

