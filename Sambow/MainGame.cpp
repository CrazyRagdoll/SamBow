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

	//hard code the sprite into the game (Bad)
	_sprites.push_back(new Bowengine::Sprite());
	_sprites.back()->init(0.0f, 0.0f, _screenWidth/2, _screenHeight/2, "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");

	_sprites.push_back(new Bowengine::Sprite());
	_sprites.back()->init(_screenWidth / 2, 0.0f, _screenWidth/2, _screenHeight/2, "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");

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
		//Used for frame time measuring
		float startTicks = SDL_GetTicks();

		processInput();
		_time += 0.01;

		_camera2D.update();

		drawGame();
		calculateFPS();

		//print FPS every 10 frames
		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 10) {
			std::cout << _fps << std::endl;
			frameCounter = 0;
		}

		//How long the programe took to loop once.
		float frameTicks = SDL_GetTicks() - startTicks;

		//Limit the FPS to the max FPS
		if (1000.0f / _maxFPS > frameTicks) {
			SDL_Delay(1000.0f / _maxFPS - frameTicks);
		}

	}
}


//Processing input from the user
void MainGame::processInput() {

	SDL_Event evnt;

	const float CAMERA_SPEED = 20.0f;
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
			switch (evnt.key.keysym.sym) {
			case SDLK_w:
				_camera2D.setPosition(_camera2D.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
				break;
			case SDLK_s:
				_camera2D.setPosition(_camera2D.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
				break;
			case SDLK_a:
				_camera2D.setPosition(_camera2D.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
				break;
			case SDLK_d:
				_camera2D.setPosition(_camera2D.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
				break;
			case SDLK_q:
				_camera2D.setScale(_camera2D.getScale() + SCALE_SPEED);
				break;
			case SDLK_e:
				_camera2D.setScale(_camera2D.getScale() - SCALE_SPEED);
				break;
			}
		}
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
	GLint timeLocation = _colourProgram.getUniformLocation("time");
	glUniform1f(timeLocation, _time);

	//Set the camera matrix
	GLint pLocation = _colourProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera2D.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	//draw the sprite
	for (int i = 0; i < _sprites.size(); i++)
	{
		_sprites[i]->draw();
	}

	//unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);
	
	//disable the shader
	_colourProgram.unuse();

	//Swap our buffer and draw everything to the screen
	_window.swapBuffer();
}

//A function to calculate the FPS
void MainGame::calculateFPS() {
	//Average the last 10 frames for a more stable value
	static const int NUM_SAMPLES = 10;
	//Make an array of floats to hold the frame values
	static float frameTimes[NUM_SAMPLES];
	//Current frame
	static int currentFrame = 0;
	
	//Using SDL_GetTicks to calcualte the difference in ticks between frames.
	//The tics from the first frame
	static float prevTicks = SDL_GetTicks();

	//The tics form the current frame
	float currentTicks;
	currentTicks = SDL_GetTicks();

	//The difference between the two frames in tics
	_frameTime = currentTicks - prevTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

	prevTicks = currentTicks;

	//Setting a count to calculate average FPS
	int count;
	currentFrame++;
	if (currentFrame < NUM_SAMPLES) {
		count = currentFrame;
	}
	else {
		count = NUM_SAMPLES;
	}

	//Calculating the average Fps
	float frameTimeAverage = 0;
	for (int i = 0; i < count; i++) {
		frameTimeAverage += frameTimes[i];
	}
	frameTimeAverage /= count;

	if (frameTimeAverage > 0) {
		_fps = 1000.0f / frameTimeAverage;
	}
	else {
		_fps = 60.0f;
	}

}