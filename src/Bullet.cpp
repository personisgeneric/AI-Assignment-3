#include "Bullet.h"
#include "TextureManager.h"
#include "Util.h"

Bullet::Bullet(glm::vec2 _pos, glm::vec2 _dir, float _angle)
{
	m_direction = _dir / Util::magnitude(_dir);
	getTransform()->position = _pos;
	m_rotation = _angle;

	TextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/playerBullet.txt",
		"../Assets/sprites/playerBullet.png",
		"playerBullet");
}

void Bullet::draw() {
	TextureManager::Instance()->draw("playerBullet", getTransform()->position.x, getTransform()->position.y, m_rotation - 90.0f, 255, false);
}


void Bullet::update() {
	getTransform()->position += (m_direction * 10.0f);
}

void Bullet::clean() { delete this; }