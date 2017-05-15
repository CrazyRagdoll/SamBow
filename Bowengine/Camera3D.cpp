#include "Camera3D.h"

#include <glm/gtx/rotate_vector.hpp>

#include <iostream>

namespace Bowengine {

	double PI = 3.141592653589793238462643383279502884197169399375105820974f;
	double TO_DEG = 180 / PI;
	
	Camera3D::Camera3D() :
		_horizontalAngle(PI),
		_verticalAngle(0.0f),
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
		_direction = glm::normalize(_target - _position);

		//Up & Right vectors
		_up				= glm::vec3(0.0f, 1.0f, 0.0f);
		_cameraRight	= glm::cross(_up, _direction);
		_cameraUp		= glm::cross(_direction, _cameraRight);

		//Update the horizontal and vertical angles based on current direction
		_horizontalAngle = PI + atan(_direction.x / _direction.z);
		_verticalAngle	 = atan(_direction.y / -_direction.z);

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

	//Camera direction rotation function
	void Camera3D::rotateDirection(float x, float y) {
		//incrementing the angles
		_horizontalAngle += x;
		_verticalAngle += y;

		_cameraRight = glm::vec3(
			sin(_horizontalAngle - PI / 2.0f),		// x axis, sin(Pi - pi/2) = 1
			0,
			cos(_horizontalAngle - PI / 2.0f));	// z axis, cos(pi - pi/2) = 0

		_direction = glm::vec3(
			cos(_verticalAngle) * sin(_horizontalAngle),
			sin(_verticalAngle),
			cos(_verticalAngle) * cos(_horizontalAngle)
		);

		_up = glm::cross(_cameraRight, _direction);

		std::cout << _horizontalAngle << " " << _verticalAngle << std::endl;

		_needsMatrixUpdate = true;
	}

	//Camera rotate function around an axis
	void Camera3D::rotateAxis(float angle, glm::vec3 axis) {
		//Rotate the direction around the different axis to change where the camera is looking.
		if (axis == glm::vec3(1.0f, 0.0f, 0.0f)) {
			_direction = glm::rotateX(_direction, angle);
		}
		else if (axis == glm::vec3(0.0f, 1.0f, 0.0f)) {
			_direction = glm::rotateY(_direction, angle);
		}
		else if (axis == glm::vec3(0.0f, 0.0f, 1.0f)) {
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