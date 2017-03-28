#pragma once  //Protects you from circular includes
#include <Windows.h>

#include <SDL/SDL.h>
#include <GL/glew.h>

#include <Bowengine/Bowengine.h>
#include <Bowengine/GLSLProgram.h>
#include <Bowengine/GLTexture.h>
#include <Bowengine/Sprite.h>
#include <Bowengine/Window.h>
#include <Bowengine/SpriteBatch.h>
#include <Bowengine/ResourceManager.h>
#include <Bowengine/GLTexture.h>
#include <Bowengine/InputManager.h>
#include <Bowengine/Timing.h>
#include <Bowengine/Camera2D.h>

#include <vector>

#include "Bullet.h"

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

	Bowengine::Window _window;	//The instance of the SDL_Window

	int _screenWidth;		//Screen's width
	int _screenHeight;		//Screen's height
	GameState _gameState;	//Current state of the game (enum class)

	Bowengine::GLSLProgram _colourProgram;
	Bowengine::Camera2D _camera2D;
	Bowengine::SpriteBatch _spriteBatch;
	Bowengine::InputManager _inputManager;
	Bowengine::FpsLimiter _fpsLimiter;


	std::vector<Bullet> _bullets;


	//Holds the fps value
	float _maxFPS, _fps;
	//Make shift time variable
	float _time;

};

