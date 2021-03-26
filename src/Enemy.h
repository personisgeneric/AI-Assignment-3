#pragma once
#include "Sprite.h"
#include "EnemyAnimationState.h"
#include "Util.h"

class Enemy : public Sprite{
public:
	Enemy();
	~Enemy();

	void draw() override;
	void update() override;
	void clean() override;
	void setAnimationState(EnemyAnimationState state);

	glm::vec2 getCurrentDirection() const;
	float getLOSDistance() const;
	bool hasLOS() const;
	void setCurrentHeading(float heading);
	float getCurrentHeading() const;

	void setLOSDistance(float distance);
	void setHasLOS(bool state);
	

private:
	//void m_buildAnimation();
	EnemyAnimationState m_currentAnimationState;

	float m_currentHeading;
	glm::vec2 m_currentDirection;
	glm::vec2 m_targetPosition;

	// LOS
	void m_changeDirection();
	float m_LOSDistance;
	bool m_hasLOS;
	glm::vec4 m_LOSColour;
	int health = 2;

};
