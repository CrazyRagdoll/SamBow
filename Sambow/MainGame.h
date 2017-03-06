#pragma once  //Protects you from circular includes

#include <SDL/SDL.h>
#include <GL/glew.h>

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
	void gameLoop();		//The main game loop which will do all of the magic.
	void processInput();	//Processing input from the user

	SDL_Window* _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;

};

