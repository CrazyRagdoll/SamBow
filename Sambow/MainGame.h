#pragma once  //Protects you from circular includes

#include <SDL/SDL.h>
#include <GL/glew.h>


class MainGame
{
public:
	MainGame();
	~MainGame();

	//Run the game
	void run();

	//Inialise everything needed to run the game
	void initSystems();


private:
	SDL_Window* _window;
	int _screenWidth;
	int _screenHeight;


};

