#pragma once
#ifndef __BULLET_H__
#define __BULLET_H__

#include <glm/vec4.hpp>
#include "../src/Sprite.h"

class bullet : public Sprite
{
private:
	glm::vec2 m_direction;
	
public:
	bullet(glm::vec2 _dir);
	
	void draw() override;
	void update() override;
	void clean() override;
};

#endif