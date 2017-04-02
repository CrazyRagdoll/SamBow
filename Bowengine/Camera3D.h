#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Bowengine {

	class Camera3D
	{
	public:
		Camera3D();
		~Camera3D();

		//Init function
		void init(int screenWidth, int screenHeight);

		//Camera update function
		void update();

		//Setters
		void setPosition(const glm::vec3& newPosition) { _position = newPosition; _needsMatrixUpdate = true; }
		void setScale(float newScale) { _scale = newScale; _needsMatrixUpdate = true; }
		void setDirection(const glm::vec3& newDirection) { _direction = newDirection; _needsMatrixUpdate = true; }
		void setTarget(const glm::vec3& newTarget) { _target = newTarget; _needsMatrixUpdate = true; }

		//Getters
		glm::vec3 getPosition() { return _position; }
		glm::vec3 getTarget() { return _target; }
		glm::vec3 getDirection() { return _direction; }
		float getScale() { return _scale; }
		glm::mat4 getProjectionMatrix() { return _projectionMatrix; }
		glm::mat4 getViewMatrix() { return _viewMatrix; }

	private:

		//holds the screen height and width
		int _screenWidth, _screenHeight;

		//bool for camera update
		bool _needsMatrixUpdate;

		//camera scale
		float _scale;

		//camera field of view
		float _fov;

		//camera min/max view distance
		float _minView, _maxView;

		//Camera position
		glm::vec3 _position;
		glm::vec3 _target;
		glm::vec3 _direction;
		glm::vec3 _cameraRight, _cameraUp, _up;

		//Matricies
		glm::mat4 _projectionMatrix;
		glm::mat4 _viewMatrix;
	};

}