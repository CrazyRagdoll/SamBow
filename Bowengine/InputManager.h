#pragma once

#include <unordered_map>
#include <glm/glm.hpp>

namespace Bowengine {

	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void pressKey(unsigned int keyID);

		void releaseKey(unsigned int keyID);

		void setMouseCoords(float x, float y);

		void scrollWheel(float x);

		bool isKeyPressed(unsigned int keyID);

		//getters
		glm::vec2 getMouseCoords() const { return _mouseCoords; }
		float getScrollValue() { return _scrollValue; }

		//Reset
		void resetScrollValue() { _scrollValue = 0; }

	private:
		std::unordered_map<unsigned int, bool> _keyMap;

		glm::vec2 _mouseCoords;

		float _scrollValue;
	};

}