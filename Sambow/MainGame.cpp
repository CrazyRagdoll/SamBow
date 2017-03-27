#include "MainGame.h"
#include <Bowengine/Errors.h>

#include <iostream>
#include <string>

//Game Constructor, Currently initalizing private member variables
MainGame::MainGame() : 
		_screenWidth(1024), 
		_screenHeight(768), 
		_time(0),
		_gameState(GameState::PLAY), 
		_maxFPS(60.0f)
{
	_camera2D.init(_screenWidth, _screenHeight);
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
	_window.create("SamBow Game", _screenWidth, _screenHeight, 0);

	//initalise the shaders
	initShaders();
	
	//initalise the sprite batch
	_spriteBatch.init();

	//inlitalise the FPS handler
	_fpsLimiter.init(_maxFPS);

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
	
	//Loops until the gamestate is set to exit
	while (_gameState != GameState::EXIT) {
		
		//Begining frame - get first tick
		_fpsLimiter.begin();

		processInput();
		//_time += 0.1; //Time used for shader colour updating

		_camera2D.update();

		drawGame();

		//Calls the end function which returns the calculated fps
		_fps = _fpsLimiter.end();

		//print FPS every 10 frames
		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 10) {
			std::cout << _fps << std::endl;
			frameCounter = 0;
		}
	}
}


//Processing input from the user
void MainGame::processInput() {

	SDL_Event evnt;

	const float CAMERA_SPEED = 2.0f;
	const float SCALE_SPEED = 0.1f;

	while (SDL_PollEvent(&evnt)) {	//While there is an event (returning 1/true)
		switch (evnt.type) {		//Which type of event was it.
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			//std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
			break;
		case SDL_KEYDOWN:
			_inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		}
	}

	//Checking if a cetain key is pressed.
	if (_inputManager.isKeyPressed(SDLK_w)) {
		_camera2D.setPosition(_camera2D.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
	}
	if (_inputManager.isKeyPressed(SDLK_s)) {
		_camera2D.setPosition(_camera2D.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
	}
	if (_inputManager.isKeyPressed(SDLK_a)) {
		_camera2D.setPosition(_camera2D.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
	}
	if (_inputManager.isKeyPressed(SDLK_d)) {
		_camera2D.setPosition(_camera2D.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
	}
	if (_inputManager.isKeyPressed(SDLK_q)) {
		_camera2D.setScale(_camera2D.getScale() + SCALE_SPEED);
	}
	if (_inputManager.isKeyPressed(SDLK_e)) {
		_camera2D.setScale(_camera2D.getScale() - SCALE_SPEED);
	}

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
	
	//tell the sader that the texture is in texture unit 0
	glUniform1i(textureLocation, 0);

	//Set the constnatly changing time varaible
	//GLint timeLocation = _colourProgram.getUniformLocation("time");
	//glUniform1f(timeLocation, _time);

	//Set the camera matrix
	GLint pLocation = _colourProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera2D.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	//Calling the spritebatch
	_spriteBatch.begin();

	glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static Bowengine::GLTexture texture = Bowengine::ResourceManager::getTexture("Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");
	Bowengine::Colour colour;
	colour.r = 255; colour.g = 255; colour.b = 255; colour.a = 255;

	_spriteBatch.draw(pos, uv, texture.id, 0.0f, colour);

	_spriteBatch.draw(pos + glm::vec4(50.0f, 0.0f, 0.0f, 0.0f), uv, texture.id, 0.0f, colour);

	_spriteBatch.end();

	_spriteBatch.renderBatch();

	//unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);
	
	//disable the shader
	_colourProgram.unuse();

	//Swap our buffer and draw everything to the screen
	_window.swapBuffer();
}
