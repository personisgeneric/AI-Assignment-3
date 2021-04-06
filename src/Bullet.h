#pragma once
#ifndef __BULLET_H__
#define __BULLET_H__

#include <glm/vec4.hpp>
#include "Sprite.h"
#include "SpriteSheet.h"

class Bullet : public Sprite {
private:
	glm::vec2 m_direction;
	float m_rotation;
public:
	Bullet();
	Bullet(glm::vec2 _pos, glm::vec2 _dir, float _angle);

	void draw() override;
	void update() override;
	void clean() override;
};

#endif