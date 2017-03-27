#include "Timing.h"

#include <SDL/SDL.h>

namespace Bowengine {

	FpsLimiter::FpsLimiter() {

	}

	void FpsLimiter::init(float maxFPS) {
		setMaxFPS(maxFPS);
	}

	void FpsLimiter::setMaxFPS(float maxFPS) {
		_maxFPS = maxFPS;
	}

	void FpsLimiter::begin() {
		_startTicks = SDL_GetTicks();
	}

	float FpsLimiter::end() {
		calculateFPS();
		
		//How long the programe took to loop once.
		float frameTicks = SDL_GetTicks() - _startTicks;

		//Limit the FPS to the max FPS
		if (1000.0f / _maxFPS > frameTicks) {
			SDL_Delay(1000.0f / _maxFPS - frameTicks);
		}

		return _fps;
	}

	void FpsLimiter::calculateFPS() {
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

}