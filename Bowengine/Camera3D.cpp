#include "Camera3D.h"

namespace Bowengine {

	Camera3D::Camera3D() :
		_position(0.0f),
		_target(0.0f),
		_direction(0.0f),
		_projectionMatrix(1.0f),
		_viewMatrix(1.0f),
		_scale(1.0f),
		_fov(45.0f),
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
		_direction = glm::normalize(_position - _target);

		//Up & Right vectors
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 cameraRight = glm::normalize(glm::cross(up, _direction));
		glm::vec3 cameraUp = glm::cross(_direction, cameraRight);

		//Create the projection matrix
		_projectionMatrix = glm::perspective(_fov, 4.0f / 3.0f, 0.1f, _maxView);

		//Create the view matrix
		_viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 300.0f),
					 glm::vec3(0.0f, 0.0f, 0.0f),
					 glm::vec3(0.0f, 1.0f, 0.0f));

	}

	//Camera update function
	void Camera3D::update() {

		if (_needsMatrixUpdate) {

			_needsMatrixUpdate = false;
		}
	}

}