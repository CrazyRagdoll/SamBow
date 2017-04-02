#include "Camera3D.h"

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
		_scale(1.0f),
		_fov(45.0f),
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
	void Camera3D::init(int screenWidth, int screenHeight) {
		//set the screen width and height
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;

		//Setting up a target and camera direction
		_target = glm::vec3(0.0f, 0.0f, 0.0f);
		_position = glm::vec3(0.0f, 0.0f, 300.0f);
		_direction = _target - _position;

		//Up & Right vectors
		_up				= glm::vec3(0.0f, 1.0f, 0.0f);
		_cameraRight	= glm::cross(_up, _direction);
		_cameraUp		= glm::cross(_direction, _cameraRight);

		//Create the projection matrix
		_projectionMatrix = glm::perspective(_fov, 4.0f / 3.0f, _minView, _maxView);

		//Create the view matrix
		_viewMatrix =	glm::lookAt(_position,				//Camera Position
									_position + _direction,	//Where we're looking
									_up);					//Up

	}

	//Camera update function
	void Camera3D::update() {

		if (_needsMatrixUpdate) {

			//Updating the projection matrix
			_projectionMatrix = glm::perspective(_fov, 4.0f / 3.0f, _minView, _maxView);

			//Update the view matrix.
			_viewMatrix =	glm::lookAt(_position,				//Camera Position
										_position + _direction, //Where we're looking
										_up);					//Up

			_needsMatrixUpdate = false;
		}

	}

}