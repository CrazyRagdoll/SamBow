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
		void init(int screenWidth, int screenHeight, glm::vec3& target = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 position = glm::vec3(0.0f, 0.0f, 50.0f));

		//Camera update function
		void update();

		//Movement Functions
		void rotateDirection(float x, float y);
		void rotateAxis(float angle, glm::vec3 axis);
		void rotateTarget(float angle, glm::vec3 axis);
		void zoom(float zoom);

		//Setters
		void setPosition(const glm::vec3& newPosition) { _position = newPosition; _needsMatrixUpdate = true; }
		void setDirection(const glm::vec3& newDirection) { _direction = newDirection; _needsMatrixUpdate = true; }
		void setTarget(const glm::vec3& newTarget) { _target = newTarget; _needsMatrixUpdate = true; }

		//Getters
		glm::vec3 getPosition() { return _position; }
		glm::vec3 getTarget() { return _target; }
		glm::vec3 getDirection() { return _direction; }
		glm::vec3 getDirectionRight() { return glm::cross(_direction, _up); }
		glm::mat4 getProjectionMatrix() { return _projectionMatrix; }
		glm::mat4 getViewMatrix() { return _viewMatrix; }
		glm::mat4 getModelMatrix() { return _modelMatrix; }

	private:

		//holds the screen height and width
		int _screenWidth, _screenHeight;

		//bool for camera update
		bool _needsMatrixUpdate;

		//camera field of view
		float _fov;

		//Camera Aspect Ration
		float _aspect;

		//camera min/max view distance
		float _minView, _maxView;

		//Angles for rotation calculations
		float _horizontalAngle, _verticalAngle;

		//Camera position
		glm::vec3 _position;
		glm::vec3 _target;
		glm::vec3 _direction;
		glm::vec3 _cameraRight, _cameraUp, _up;

		//Matricies
		glm::mat4 _projectionMatrix;
		glm::mat4 _viewMatrix;
		glm::mat4 _modelMatrix;
	};

}