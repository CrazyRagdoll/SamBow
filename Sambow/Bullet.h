#pragma once

#include <glm/glm.hpp>
#include <Bowengine/SpriteBatch.h>

class Bullet
{
public:
	Bullet(glm::vec2 position, glm::vec2 direction, float speed, int lifetime);
	~Bullet();

	void draw(Bowengine::SpriteBatch& spriteBatch);
	//Returns true when out of life
	bool update();


private:
	float _speed;
	glm::vec2 _direction;
	glm::vec2 _position;
	int _lifeTime;
};

