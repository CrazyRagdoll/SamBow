#include "Camera3D.h"

#include <glm/gtx/rotate_vector.hpp>

namespace Bowengine {

	Camera3D::Camera3D() :
		_position(0.0f),
		_target(0.0f),
		_direction(0.0f),
		_up(0.0f),
		_cameraRight(0.0f),
		_cameraUp(0.0f),
		_projectionMatrix(1.0f),
		_viewMatrix(1.0f),
		_modelMatrix(1.0f),
		_fov(45.0f),
		_aspect(4.0f/3.0f),
		_minView(0.1f),
		_maxView(1000.0f),
		_needsMatrixUpdate(true),
		_screenWidth(500),
		_screenHeight(500)
	{
	}


	Camera3D::~Camera3D()
	{
	}

	//Init function
	void Camera3D::init(int screenWidth, int screenHeight, glm::vec3& target, glm::vec3 position /*default values set in .h*/) {
		//set the screen width and height
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;

		//Setting up a target and camera direction
		_target = target;
		_position = position;
		_direction = _target - _position;

		//Up & Right vectors
		_up				= glm::vec3(0.0f, 1.0f, 0.0f);
		_cameraRight	= glm::cross(_up, _direction);
		_cameraUp		= glm::cross(_direction, _cameraRight);

		//Create the projection matrix
		_projectionMatrix = glm::perspective(_fov, _aspect, _minView, _maxView);

		//Create the view matrix
		_viewMatrix =	glm::lookAt(_position,				//Camera Position
									_position + _direction,	//Where we're looking
									_up);					//Up

	}

	//Camera update function
	void Camera3D::update() {

		if (_needsMatrixUpdate) {

			//Updating the projection matrix
			_projectionMatrix = glm::perspective(_fov, _aspect, _minView, _maxView);

			//Update the view matrix.
			_viewMatrix =	glm::lookAt(_position,				//Camera Position
										_position + _direction, //Where we're looking
										_up);					//Up

			_needsMatrixUpdate = false;
		}

	}

	//Camera rotate function
	void Camera3D::rotate(float angle, glm::vec3 axis) {
		//Rotate the direction around the different axis to change where the camera is looking.
		if (axis == glm::vec3(1.0f, 0.0f, 0.0f)) {
			_direction = glm::rotateX(_direction, angle);
		}
		else if (axis == glm::vec3(0.0f, 1.0f, 0.0f)) {
			_direction = glm::rotateY(_direction, angle);
		}
		else {
			_direction = glm::rotateZ(_direction, angle);
		}
		_needsMatrixUpdate = true;
	}

	void Camera3D::rotateTarget(float angle, glm::vec3 axis) {
		_viewMatrix = glm::rotate(_viewMatrix, angle, axis);
	}

	//Cameera zoom function
	void Camera3D::zoom(float zoom) {
		_modelMatrix *= zoom;
	}

}