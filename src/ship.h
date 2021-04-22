#pragma once
#ifndef __SHIP__
#define __SHIP__

#include <glm/vec4.hpp>
#include "DisplayObject.h"
#include "Bullet.h"
#include "TextureManager.h"
#include "PlayerAnimationState.h"
#include "Sprite.h"

class Ship final : public Sprite {
public:
	Ship();
	~Ship();

	// Inherited via GameObject
	void draw() override;
	void update() override;
	void clean() override;

	void turnRight();
	void turnLeft();
	void moveForward();
	void moveBack();
	
	void move();
	void m_buildAnimations();

	// getters
	glm::vec2 getTargetPosition() const;
	glm::vec2 getCurrentDirection() const;
	float getMaxSpeed() const;
	
	float getLOSDistance() const;
	bool hasLOS() const;
	float getCurrentHeading() const;
	Bullet* getBullet();

	// setters
	void setTargetPosition(glm::vec2 newPosition);
	void setCurrentDirection(glm::vec2 newDirection);
	void setMaxSpeed(float newSpeed);

	void setLOSDistance(float distance);
	void setHasLOS(bool state);
	void setCurrentHeading(float heading);
	void setAnimationState(const PlayerAnimationState new_state);

	void shoot();
	void deleteBullet(int _pos);
	void updateRotation();

private:
	void m_checkBounds();
	void m_reset();

	int m_health; // This will hold the player's m_health

	// steering behaviours
	float m_maxSpeed;
	float m_turnRate;

	void m_changeDirection();
	float m_currentHeading;
	glm::vec2 m_currentDirection;
	glm::vec2 m_targetPosition;

	PlayerAnimationState m_currentAnimationState;
	std::vector <Bullet*> m_playerBullets; 
	// LOS
	float m_LOSDistance;
	bool m_hasLOS;
	glm::vec4 m_LOSColour;
};

#endif /* defined (__SHIP__) */

