#include "Camera2D.h"

namespace Bowengine {

	//initalise all the things
	Camera2D::Camera2D() :
		_position(0.0f),
		_cameraMatrix(1.0f),
		_orthoMatrix(1.0f),
		_scale(1.0f),
		_needsMatrixUpdate(true),
		_screenWidth(500),
		_screenHeight(500)
	{
	}


	Camera2D::~Camera2D()
	{
	}

	//initalize the camera
	void Camera2D::init(int screenWidth, int screenHeight) {
		//set the screen width and height
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;
		//Create an orthographic matrix
		_orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
	}

	//update the camera
	void Camera2D::update() {

		if (_needsMatrixUpdate) {
			//Translate the camera matrix - Setting the focus point to the center half screen height/width
			glm::vec3 translate(-_position.x + _screenWidth / 2, -_position.y + _screenHeight / 2, 0.0f);
			_cameraMatrix = glm::translate(_orthoMatrix, translate);

			//Scale the camera matrix
			glm::vec3 scale(_scale, _scale, 0.0f);
			_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;

			_needsMatrixUpdate = false;
		}

	}

}