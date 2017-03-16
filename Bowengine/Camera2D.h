#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Bowengine {

	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		//Init function
		void init(int screenWidth, int screenHeight);

		//Camera update function
		void update();

		//Setters
		void setPosition(const glm::vec2& newPosition) { _position = newPosition; _needsMatrixUpdate = true; }
		void setScale(float newScale) {	_scale = newScale; _needsMatrixUpdate = true; }

		//Getters
		glm::vec2 getPosition() { return _position; }
		float getScale() { return _scale; }
		glm::mat4 getCameraMatrix() { return _cameraMatrix; }

	private:

		//holds the screen height and width
		int _screenWidth, _screenHeight;

		//bool for camera update
		bool _needsMatrixUpdate;
		//camera scale
		float _scale;
		//Camera position
		glm::vec2 _position;
		glm::mat4 _cameraMatrix, _orthoMatrix;

	};

}