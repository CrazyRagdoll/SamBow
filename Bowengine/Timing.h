#pragma once

namespace Bowengine {

	class FpsLimiter {
	public:
		FpsLimiter();

		void init(float maxFPS);

		void setMaxFPS(float maxFPS);

		void begin();

		//end will return the fps
		float end();

	private:
		void calculateFPS();	//Calculate the fps of the game

		float _fps, _maxFPS, _frameTime;
		unsigned int _startTicks;

	};

}