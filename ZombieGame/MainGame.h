#pragma once

#include <Bowengine\Window.h>
#include <Bowengine\GLSLProgram.h>
#include <Bowengine\Camera2D.h>
#include <Bowengine\InputManager.h>


class MainGame
{
public:
	MainGame();
	~MainGame();

	/// Runs the game
	void run();

private:
	/// Initializes the core systems
	void initSystems();

	/// Initializes the shaders
	void initShaders();

	/// Main game loop for the program
	void gameLoop();

	/// Handles input processing
	void processInput();

	/// Renders the game
	void drawGame();

private:
	/// Member Variables
	Bowengine::Window _window; ///< The game window
	Bowengine::GLSLProgram _textureProgram; ///< The shader program
	Bowengine::InputManager _inputManager; ///< Handles input
	Bowengine::Camera2D _camera; ///< Main Camera
};

