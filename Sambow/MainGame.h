#pragma once  //Protects you from circular includes
#include <Windows.h>

#include <SDL/SDL.h>
#include <GL/glew.h>

#include <Bowengine/Bowengine.h>
#include <Bowengine/GLSLProgram.h>
#include <Bowengine/GLTexture.h>
#include <Bowengine/Sprite.h>
#include <Bowengine/Window.h>

#include <Bowengine/Camera2D.h>

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

	Bowengine::Window _window;	//The instance of the SDL_Window

	int _screenWidth;		//Screen's width
	int _screenHeight;		//Screen's height
	GameState _gameState;	//Current state of the game (enum class)

	std::vector <Bowengine::Sprite*> _sprites;

	Bowengine::GLSLProgram _colourProgram;

	Bowengine::Camera2D _camera2D;

	//FPS calculating variables
	float _fps, _maxFPS, _frameTime;

	//Make shift time variable
	float _time;

};

