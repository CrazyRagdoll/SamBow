#include "InputManager.h"

namespace Bowengine {

	InputManager::InputManager() : _mouseCoords(0.0f), _scrollValue(0.0f)
	{
	}


	InputManager::~InputManager()
	{
	}

	void InputManager::pressKey(unsigned int keyID) {
		//Map will check if key is in the map, if not it will create it then set it to true
		_keyMap[keyID] = true;
	}

	void InputManager::releaseKey(unsigned int keyID) {
		_keyMap[keyID] = false;
	}

	void InputManager::setMouseCoords(float x, float y) {
		_mouseCoords.x = x;
		_mouseCoords.y = y;
	}

	void InputManager::scrollWheel(float x) {
		_scrollValue = x;
	}

	bool InputManager::isKeyPressed(unsigned int keyID) {
		//Search for the key, if it was found return its state
		auto it = _keyMap.find(keyID);
		if (it != _keyMap.end()) {
			return it->second;
		}
		else {
		//otherwise return false
			return false;
		}
	}

}