#include "Enemy.h"
#include "TextureManager.h"
#include "Util.h"

Enemy::Enemy() : m_currentAnimationState(IDLE) {
	/*TextureManager::Instance()->loadSpriteSheet();*/


	setSpriteSheet(TextureManager::Instance()->getSpriteSheet("spritesheet"));

	//// set frame width
	//setWidth(53);

	//// set frame height
	//setHeight(58);

	//getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(ENEMY);

	m_buildAnimation();
}

Enemy::~Enemy()
= default;

void Enemy::draw() {
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the player according to animation state
	switch (m_currentAnimationState)
	{
	case IDLE:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("idle"),
			x, y, 0.12f, 0, 255, true);
		break;
	case PATROL:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("patrol"),
			x, y, 0.12f, 0, 255, true);
		break;
	case DAMAGE:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("damage"),
			x, y, 0.25f, 0, 255, true);
		break;
	case DEATH:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("death"),
			x, y, 0.25f, 0, 255, true);
		break;
	default:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("idle"),
			x, y, 0.12f, 0, 255, true);
		break;
	}

	Util::DrawLine(getTransform()->position, getTransform()->position + getCurrentDirection() * m_LOSDistance, m_LOSColour);
}

void Enemy::update() {

}






void Enemy::clean()
{
}

void Enemy::setAnimationState(const EnemyAnimationState new_state)
{
	m_currentAnimationState = new_state;
}

float Enemy::getLOSDistance() const
{
	return m_LOSDistance;
}

bool Enemy::hasLOS() const
{
	return m_hasLOS;
}

float Enemy::getCurrentHeading() const
{
	return m_currentHeading;
}

glm::vec2 Enemy::getCurrentDirection() const
{
	return m_currentDirection;
}

void Enemy::setCurrentHeading(const float heading)
{
	m_currentHeading = heading;
	m_changeDirection();
}

void Enemy::setLOSDistance(const float distance)
{
	m_LOSDistance = distance;
}

void Enemy::setHasLOS(const bool state)
{
	m_hasLOS = state;
	m_LOSColour = (m_hasLOS) ? glm::vec4(0, 1, 0, 1) : glm::vec4(1, 0, 0, 1);
}

void Enemy::m_buildAnimation()
{
	Animation idleAnimation = Animation();

	idleAnimation.name = "Idle";
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-idle-0"));
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-idle-1"));
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-idle-2"));
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-idle-3"));

	setAnimation(idleAnimation);

	Animation patrolAnimation = Animation();

	patrolAnimation.name = "Patrol";
	patrolAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-0"));
	patrolAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-1"));
	patrolAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-2"));
	patrolAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-3"));

	setAnimation(patrolAnimation);

	Animation damageAnimation = Animation();

	damageAnimation.name = "Damage";
	damageAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-0"));
	damageAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-1"));
	damageAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-2"));
	damageAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-3"));

	setAnimation(damageAnimation);

	Animation deathAnimation = Animation();

	deathAnimation.name = "Death";
	deathAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-0"));
	deathAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-1"));
	deathAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-2"));
	deathAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-3"));

	setAnimation(deathAnimation);

	


}

void Enemy::m_changeDirection()
{
	const auto x = cos(m_currentHeading * Util::Deg2Rad);
	const auto y = sin(m_currentHeading * Util::Deg2Rad);
	m_currentDirection = glm::vec2(x, y);

	glm::vec2 size = TextureManager::Instance()->getTextureSize("ship");
}