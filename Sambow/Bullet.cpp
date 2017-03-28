#include "Bullet.h"
#include <Bowengine/ResourceManager.h>


Bullet::Bullet(glm::vec2 position, glm::vec2 direction, float speed, int lifetime)
{
	_position = position;
	_direction = direction;
	_speed = speed;
	_lifeTime = lifetime;
}


Bullet::~Bullet()
{
}

void Bullet::draw(Bowengine::SpriteBatch& spriteBatch) {
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static Bowengine::GLTexture texture = Bowengine::ResourceManager::getTexture("Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");
	Bowengine::Colour colour;
	colour.r = 255; colour.g = 255; colour.b = 255; colour.a = 255;

	glm::vec4 posAndSize = glm::vec4(_position.x, _position.y, 30, 30);

	spriteBatch.draw(posAndSize, uv, texture.id, 0.0f, colour);
}

bool Bullet::update() {
	_position += _direction * _speed;
	_lifeTime--;
	if (_lifeTime == 0) {
		return true;
	}
	return false;
}