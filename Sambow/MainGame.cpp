#include "MainGame.h"
#include <Bowengine/Errors.h>

#include <iostream>
#include <string>

//Game Constructor, Currently initalizing private member variables
MainGame::MainGame() : 
		_screenWidth(1024), 
		_screenHeight(768), 
		_time(1),
		_gameState(GameState::PLAY), 
		_maxFPS(60.0f),
		_cameraState(CameraState::Camera3D)
{
	_camera2D.init(_screenWidth, _screenHeight);
	_camera3D.init(_screenWidth, _screenHeight);
}

//Destructor
MainGame::~MainGame()
{
}


//Run the game
void MainGame::run() {
	//initalise the systems
	initSystems();

	//Run the game loop
	gameLoop();
}
 

//Inialise everything needed to run the game
void MainGame::initSystems() {
	Bowengine::init();

	//Create the window
	_window.create("Sam Bowen's Engine", _screenWidth, _screenHeight, 0);

	//initalise the shaders
	initShaders();
	
	//initalise the sprite batch
	_spriteBatch.init();

	//inlitalise the FPS handler
	_fpsLimiter.init(_maxFPS);

	//Load a cube
	_cubeAgent.init("Objects/Cube.obj", "");

	//Create a cube
	//_cube.init(glm::vec3(0.0f, 2.0f, 0.0f), 2.0f, 2.0f, 2.0f, "Textures/Cube.png");

}

void MainGame::initShaders() {
	//Using colour program to compile, init, and link our fragment + vertex shaders
	_colourProgram.compileShaders("Shaders/colourShading.vs", "Shaders/colourShading.fs");
	_colourProgram.addAttribute("vertexPosition");
	_colourProgram.addAttribute("vertexColour");
	_colourProgram.addAttribute("VertexUV");
	_colourProgram.linkShaders();
}


//The main game loop which will do all of the magic.
void MainGame::gameLoop(){
	
	//Loops until the gamestate is set to exit
	while (_gameState != GameState::EXIT) {
		
		//Begining frame - get first tick
		_fpsLimiter.begin();

		//Process Input commands
		processInput();
		_time = 1.0f; //Time used for shader colour updating

		//Update the cameras
		if (_cameraState == CameraState::Camera2D) {
			_camera2D.update();
		} else if (_cameraState == CameraState::Camera3D) {
			_camera3D.update();
		}

		//Update Bullets
		for (int i = 0; i < _bullets.size();) {
			if (_bullets[i].update() == true) {
				_bullets[i] = _bullets.back();
				_bullets.pop_back();
			}
			else {
				i++;
			}
		}

		//Draw the game
		drawGame();

		//Calls the end function which returns the calculated fps
		_fps = _fpsLimiter.end();

		//print FPS every 10 frames
		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 1000) {
			std::cout << _fps << std::endl;
			frameCounter = 0;
		}
	}
}


//Processing input from the user
void MainGame::processInput() {

	SDL_Event evnt;

	const float CAMERA_SPEED = 0.20f;
	const float SCALE_SPEED = 0.25f;

	//max and min zooms
	float MAX_VIEW = 5.0f, MIN_VIEW = 1.0f;

	while (SDL_PollEvent(&evnt)) {	//While there is an event (returning 1/true)
		switch (evnt.type) {		//Which type of event was it.
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_KEYDOWN:
			_inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(evnt.button.button);
			break;
		case SDL_MOUSEMOTION:
			_inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
			//std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
			break;
		case SDL_MOUSEWHEEL:
			_inputManager.scrollWheel(evnt.wheel.y);
			break;
		}
	}

	//2D Camera - Checking if a cetain key is pressed.
	if (_cameraState == CameraState::Camera2D) {
		if (_inputManager.isKeyPressed(SDLK_w)) {	//Move up
			_camera2D.setPosition(_camera2D.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
		}
		if (_inputManager.isKeyPressed(SDLK_s)) {	//move Down
			_camera2D.setPosition(_camera2D.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
		}
		if (_inputManager.isKeyPressed(SDLK_a)) {	//Move Left
			_camera2D.setPosition(_camera2D.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
		}
		if (_inputManager.isKeyPressed(SDLK_d)) {	//Move right
			_camera2D.setPosition(_camera2D.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
		}
		if (_inputManager.isKeyPressed(SDLK_q)) {	//Zoom in
			_camera2D.setScale(_camera2D.getScale() + SCALE_SPEED);
		}
		if (_inputManager.isKeyPressed(SDLK_e)) {	//Zoom out
			_camera2D.setScale(_camera2D.getScale() - SCALE_SPEED);
		}
	}

	//3D Camera - Checking for key presses.
	if (_cameraState == CameraState::Camera3D) {
		if (_inputManager.isKeyPressed(SDLK_w)) {
			_camera3D.setPosition(_camera3D.getPosition() + (_camera3D.getDirection() * glm::vec3(CAMERA_SPEED)));
		}
		if (_inputManager.isKeyPressed(SDLK_s)) {
			_camera3D.setPosition(_camera3D.getPosition() - (_camera3D.getDirection() * glm::vec3(CAMERA_SPEED)));
		}
		if (_inputManager.isKeyPressed(SDLK_a)) {
			_camera3D.setPosition(_camera3D.getPosition() - (_camera3D.getDirectionRight() * glm::vec3(CAMERA_SPEED)));
		}
		if (_inputManager.isKeyPressed(SDLK_d)) {
			_camera3D.setPosition(_camera3D.getPosition() + (_camera3D.getDirectionRight() * glm::vec3(CAMERA_SPEED)));
		}
		if (_inputManager.isKeyPressed(SDLK_SPACE)) {
			_camera3D.setPosition(_camera3D.getPosition() + glm::vec3(0.0f, CAMERA_SPEED, 0.0f));
		}
		if (_inputManager.isKeyPressed(SDLK_z)) {
			_camera3D.setPosition(_camera3D.getPosition() + glm::vec3(0.0f, -CAMERA_SPEED, 0.0f));
		}

		//Using the mouse to rotate the camera
		static float keyPressDuration;
		static glm::vec2 startMouseCoords;
		if (_inputManager.isKeyPressed(SDL_BUTTON_RIGHT)) {
			//Hiding the mouse where it was clicked.
			if (keyPressDuration == 0.0f) {
				startMouseCoords = _inputManager.getMouseCoords();
				SDL_ShowCursor(0);
			}
			//Warping to mouse to where it was first clicked
			SDL_WarpMouseInWindow(_window.getWindow(), startMouseCoords.x, startMouseCoords.y);
			
			//get the current mouse coordinates
			glm::vec2 currentMouseCoords = _inputManager.getMouseCoords();
			//Work out the difference between this frame and last frame
			glm::vec2 difMouseCoords = startMouseCoords - currentMouseCoords;

			//Rotating the camera 
			_camera3D.rotateDirection(difMouseCoords.x / 1000, difMouseCoords.y / 1000);

			//Counting how long the click is held down.
			keyPressDuration += 0.1f;
		}
		else {
			//if the right mouse button is not held down
			SDL_ShowCursor(1);
			keyPressDuration = 0.0f;
		}


	}


	//Regulating the view distance with scroll wheel
	float newView;
	newView = _camera2D.getScale() + _inputManager.getScrollValue() * SCALE_SPEED;
	//Zooming in and out with scroll wheel
	if (newView > MIN_VIEW && newView < MAX_VIEW) {
		_camera2D.setScale(_camera2D.getScale() + _inputManager.getScrollValue() * SCALE_SPEED);
		_inputManager.resetScrollValue();		
	}

	/*//Checking for the left mouse button and generating bullets
	if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
		glm::vec2 mouseCoords = _inputManager.getMouseCoords();
		mouseCoords = _camera2D.convertScreenToWorld(mouseCoords);
		
		glm::vec2 playerPosition(0.0f);
		glm::vec2 direction = mouseCoords - playerPosition;
		direction = glm::normalize(direction);

		_bullets.emplace_back(playerPosition, direction, 5.0f, 1000);

	}*/

	//Quit the game with escape
	if (_inputManager.isKeyPressed(SDLK_ESCAPE)) {
		SDL_Quit();		//Close all SDL operations
		exit(69);		//Close the program
	}

}

void MainGame::drawGame() {		//Draw content to the game

	glClearDepth(1.0);
	//Clear the colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//enable the shaders
	_colourProgram.use();

	//Using texture unit 0
	glActiveTexture(GL_TEXTURE0);
	//Get the uniform location
	GLint textureLocation = _colourProgram.getUniformLocation("mySampler");
	//tell the shader that the texture is in texture unit 0
	glUniform1i(textureLocation, 0);

	//Set a time variable we can change to change shader values
	//GLint timeLocation = _colourProgram.getUniformLocation("time");
	//glUniform1f(timeLocation, _time);

	//Set the camera matrix
	if (_cameraState == CameraState::Camera2D) {
		GLint pLocation = _colourProgram.getUniformLocation("P");
		glm::mat4 cameraMatrix = _camera2D.getCameraMatrix();
		glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));
	}

	//Set the 3D camera
	if (_cameraState == CameraState::Camera3D) {
		GLint pLocation = _colourProgram.getUniformLocation("P");
		glm::mat4 projectionMatrix = _camera3D.getProjectionMatrix();
		glm::mat4 viewMatrix = _camera3D.getViewMatrix();
		glm::mat4 modelMatrix = _camera3D.getModelMatrix();
		glm::mat4 cameraMatrix = projectionMatrix * viewMatrix * modelMatrix;
		glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));
	}

	//Drawing the agent
	_cubeAgent.draw();

	//Drawing a cube.
	//_cube.draw();

	/*//Calling the spritebatch
	_spriteBatch.begin();

	glm::vec4 pos(-25.0f, -25.0f, 50.0f, 50.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static Bowengine::GLTexture texture = Bowengine::ResourceManager::getTexture("Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png"); 
	Bowengine::Colour colour;
	colour.r = 255; colour.g = 255; colour.b = 255; colour.a = 255;

	_spriteBatch.draw(pos, uv, texture.id, 0.0f, colour);

	for (int i = 0; i < _bullets.size(); i++) {
		_bullets[i].draw(_spriteBatch);
	}

	_spriteBatch.end();

	_spriteBatch.renderBatch();*/

	//unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);
	
	//disable the shader
	_colourProgram.unuse();

	//Cull triangles 
	glEnable(GL_CULL_FACE);

	//Swap our buffer and draw everything to the screen
	_window.swapBuffer();
}
