#include "Enemy.h"
#include "TextureManager.h"
#include "Util.h"

Enemy::Enemy() : m_currentAnimationState(IDLE_RIGHT) 
{
	TextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/enemy-spritesheet.txt",
		"../Assets/sprites/enemy-spritesheet.png",
		"enemySpriteSheet");

	setSpriteSheet(TextureManager::Instance()->getSpriteSheet("enemySpriteSheet"));

	// set frame width
	setWidth(53);

	// set frame height
	setHeight(58);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
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

	// draw the enemy according to animation state
	switch (m_currentAnimationState)
	{
	// ------------------ Idle ------------------- //
	case IDLE_UP:
		TextureManager::Instance()->playAnimation("enemySpriteSheet", getAnimation("idleUp"),
			x, y, 0.12f, 0, 255, true);
		break;
	case IDLE_RIGHT:
		TextureManager::Instance()->playAnimation("enemySpriteSheet", getAnimation("idleRight"),
			x, y, 0.12f, 0, 255, true);
		break;
	case IDLE_DOWN:
		TextureManager::Instance()->playAnimation("enemySpriteSheet", getAnimation("idleDown"),
			x, y, 0.12f, 0, 255, true);
		break;
	case IDLE_LEFT:
		TextureManager::Instance()->playAnimation("enemySpriteSheet", getAnimation("idleLeft"),
			x, y, 0.12f, 0, 255, true);
		break;

	// ------------------ Patrol ------------------- //
	case PATROL:
		TextureManager::Instance()->playAnimation("enemySpriteSheet", getAnimation("patrol"),
			x, y, 0.12f, 0, 255, true);
		break;


	case DAMAGE:
		TextureManager::Instance()->playAnimation("enemySpriteSheet", getAnimation("damage"),
			x, y, 0.25f, 0, 255, true);
		break;
	case DEATH:
		TextureManager::Instance()->playAnimation("enemySpriteSheet", getAnimation("death"),
			x, y, 0.25f, 0, 255, true);
		break;
	default:
		TextureManager::Instance()->playAnimation("enemySpriteSheet", getAnimation("idle"),
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
	// ------------------------- Idle -----------------------
	// Left
		Animation idleLeftAnimation = Animation();
	idleLeftAnimation.name = "idleLeft";

	std::string tmp_str = "enemy-idle-left-";
	for (int i = 0; i < 2; i++)
		idleLeftAnimation.frames.push_back(getSpriteSheet()->getFrame(tmp_str + std::to_string(i)));
	setAnimation(idleLeftAnimation);

	// Right
	Animation idleRightAnimation = Animation();
	idleRightAnimation.name = "idleRight";

	tmp_str = "enemy-idle-right-";
	for (int i = 0; i < 2; i++)
		idleRightAnimation.frames.push_back(getSpriteSheet()->getFrame(tmp_str + std::to_string(i)));
	setAnimation(idleRightAnimation);

	// Up
	Animation idleUpAnimation = Animation();
	idleUpAnimation.name = "idleRight";

	tmp_str = "enemy-idle-up-";
	for (int i = 0; i < 2; i++)
		idleUpAnimation.frames.push_back(getSpriteSheet()->getFrame(tmp_str + std::to_string(i)));
	setAnimation(idleUpAnimation);

	// Down
	Animation idleDownAnimation = Animation();
	idleDownAnimation.name = "idleDown";

	tmp_str = "enemy-idle-Down-";
	for (int i = 0; i < 2; i++)
		idleDownAnimation.frames.push_back(getSpriteSheet()->getFrame(tmp_str + std::to_string(i)));
	setAnimation(idleDownAnimation);
	
	// Run
	Animation patrolAnimation = Animation();
	patrolAnimation.name = "patrol";

	tmp_str = "enemy-run-";
	for (int i = 0; i < 3; i++)
		patrolAnimation.frames.push_back(getSpriteSheet()->getFrame(tmp_str + std::to_string(i)));
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