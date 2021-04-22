#include "ship.h"

#include "EventManager.h"
#include "glm/gtx/string_cast.hpp"
#include "PlayScene.h"
#include "TextureManager.h"
#include "Util.h"
#include "Sprite.h"

Ship::Ship() : m_currentAnimationState(PLAYER_IDLE) {
	// Load the player and health bar sprites
	TextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/LudicoloSpriteSheet.txt",
		"../Assets/Sprites/LudicoloSpritesheet.png",
		"playerSpriteSheet");
	TextureManager::Instance()->load("../Assets/textures/healthbarGreen.png", "greenHealth");
	TextureManager::Instance()->load("../Assets/textures/healthbarRed.png", "redHealth");

	setSpriteSheet(TextureManager::Instance()->getSpriteSheet("playerSpriteSheet"));

	// Set frame width and height for the player and healthbars
	setWidth(31);
	setHeight(31);

	auto size = TextureManager::Instance()->getTextureSize("greenHealth");
	setWidth(size.x);
	setHeight(size.y);
	
	size = TextureManager::Instance()->getTextureSize("redHealth");
	setWidth(size.x);
	setHeight(size.y);
	
	
	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setMaxSpeed(3.0f);
	setType(SHIP);

	m_health = 3;
	
	m_currentHeading = 0.0f; // current facing angle
	m_currentDirection = glm::vec2(1.0f, 0.0f); // facing right
	m_turnRate = 5.0f; // 5 degrees per frame

	m_LOSDistance = 400.0f; // 5 ppf x 80 feet
	m_LOSColour = glm::vec4(1, 0, 0, 1);
	m_buildAnimations();
}


Ship::~Ship()
= default;

void Ship::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// Draw the player's health
	TextureManager::Instance()->draw("redHealth", getTransform()->position.x, getTransform()->position.y - getHeight(), 0, 255, true);	// Red bar underneath
	// Draw the amount of health the player currently has
	for (int i = 0; i < m_health; i++)
		TextureManager::Instance()->draw("greenHealth", getTransform()->position.x + ((i * 30) - 30), getTransform()->position.y - getHeight(), 0, 255, true); // Green portion of the health bar
	
	// draw the ship based on the animation state
	TextureManager::Instance()->draw("ship", x, y, m_currentHeading, 255, true);
	switch (m_currentAnimationState) {
	// Idle animations
	case PLAYER_IDLE:
		TextureManager::Instance()->playAnimation("playerSpriteSheet", getAnimation("idle"), 
			x, y, 0.05, m_currentHeading, 255, false, SDL_FLIP_NONE);
		break;
	case PLAYER_RUN:
		TextureManager::Instance()->playAnimation("playerSpriteSheet", getAnimation("run"),
			x, y, 0.05, m_currentHeading, 255, false, SDL_FLIP_NONE);
	case PLAYER_HURT:
		TextureManager::Instance()->playAnimation("playerSpriteSheet", getAnimation("hurt"),
			x, y, 0.05, 0, 255, false, SDL_FLIP_NONE);
	case PLAYER_MELEE:
		TextureManager::Instance()->playAnimation("playerSpriteSheet", getAnimation("melee"),
			x, y, 0.05, m_currentHeading, 255, false, SDL_FLIP_NONE);
	}

	// draw LOS
	Util::DrawLine(getTransform()->position, getTransform()->position + getCurrentDirection() * m_LOSDistance, m_LOSColour);
}


void Ship::update()
{
	if (SDL_NumJoysticks() > 1)
		SDL_JoystickOpen;
	move();
	updateRotation();
	/*m_checkBounds();*/
}

void Ship::clean() { }

void Ship::turnRight()
{
	m_currentHeading += m_turnRate;
	if (m_currentHeading >= 360) 
	{
		m_currentHeading -= 360.0f;
	}
	m_changeDirection();
}

void Ship::turnLeft()
{
	m_currentHeading -= m_turnRate;
	if (m_currentHeading < 0)
	{
		m_currentHeading += 360.0f;
	}

	m_changeDirection();
}

void Ship::moveForward()
{
	getRigidBody()->velocity = m_currentDirection * m_maxSpeed;
}

void Ship::moveBack()
{
	getRigidBody()->velocity = m_currentDirection * -m_maxSpeed;
}

void Ship::move() {
	setAnimationState(PLAYER_IDLE);
	// Movement without controller
	if (SDL_NumJoysticks() < 1) {
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D)) {

			if (getTransform()->position.x + m_maxSpeed < 800 - 32)
				getTransform()->position.x += m_maxSpeed;
			setAnimationState(PLAYER_RUN);
		}
		// left
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A)) {
			if (getTransform()->position.x - m_maxSpeed > 0)
				getTransform()->position.x -= m_maxSpeed;
			setAnimationState(PLAYER_RUN);
		}
		// up
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W)) {
			if (getTransform()->position.y - m_maxSpeed > 0)
				getTransform()->position.y -= m_maxSpeed;
			setAnimationState(PLAYER_RUN);
		}
		// down
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S)) {
			if (getTransform()->position.y + m_maxSpeed < 600 - 32)
				getTransform()->position.y += m_maxSpeed;
			setAnimationState(PLAYER_RUN);
		}
	}
	else
	{
		int deadzone = 10000;
		if (EventManager::Instance().getGameController(0)->LEFT_STICK_X > 0 || EventManager::Instance().getGameController(0)->LEFT_STICK_X < 0 || EventManager::Instance().getGameController(0)->LEFT_STICK_Y  > 0 || EventManager::Instance().getGameController(0)->LEFT_STICK_Y < 0) {
			if (EventManager::Instance().getGameController(0)->LEFT_STICK_X > deadzone) {
				setAnimationState(PLAYER_RUN);
				getTransform()->position.x += m_maxSpeed;
			}
			else if (EventManager::Instance().getGameController(0)->LEFT_STICK_X < -deadzone) {
				setAnimationState(PLAYER_RUN);
				getTransform()->position.x -= m_maxSpeed;
			}
			if (EventManager::Instance().getGameController(0)->LEFT_STICK_Y > deadzone) {
				setAnimationState(PLAYER_RUN);
				getTransform()->position.y += m_maxSpeed;
			}
			else if (EventManager::Instance().getGameController(0)->LEFT_STICK_Y < -deadzone) {
				setAnimationState(PLAYER_RUN);
				getTransform()->position.y -= m_maxSpeed;
			}
		}
		else 
		{
			setAnimationState(PLAYER_IDLE);
			getTransform()->position = getTransform()->position;
		}
	}
}

glm::vec2 Ship::getTargetPosition() const
{
	return m_targetPosition;
}

glm::vec2 Ship::getCurrentDirection() const
{
	return m_currentDirection;
}

float Ship::getMaxSpeed() const
{
	return m_maxSpeed;
}

float Ship::getLOSDistance() const
{
	return m_LOSDistance;
}

bool Ship::hasLOS() const
{
	return m_hasLOS;
}

float Ship::getCurrentHeading() const
{
	return m_currentHeading;
}

void Ship::setLOSDistance(const float distance)
{
	m_LOSDistance = distance;
}

void Ship::setHasLOS(const bool state)
{
	m_hasLOS = state;
	m_LOSColour = (m_hasLOS) ? glm::vec4(0, 1, 0, 1) : glm::vec4(1, 0, 0, 1);
}

void Ship::setCurrentHeading(const float heading)
{
	m_currentHeading = heading;
	m_changeDirection();
}

void Ship::setTargetPosition(glm::vec2 newPosition)
{
	m_targetPosition = newPosition;

}

void Ship::setCurrentDirection(glm::vec2 newDirection)
{
	m_currentDirection = newDirection;
}

void Ship::setMaxSpeed(float newSpeed)
{
	m_maxSpeed = newSpeed;
}



void Ship::m_checkBounds()
{

	if (getTransform()->position.x > Config::SCREEN_WIDTH)
	{
		getTransform()->position = glm::vec2(0.0f, getTransform()->position.y);
	}

	if (getTransform()->position.x < 0)
	{
		getTransform()->position = glm::vec2(800.0f, getTransform()->position.y);
	}

	if (getTransform()->position.y > Config::SCREEN_HEIGHT)
	{
		getTransform()->position = glm::vec2(getTransform()->position.x, 0.0f);
	}

	if (getTransform()->position.y < 0)
	{
		getTransform()->position = glm::vec2(getTransform()->position.x, 600.0f);
	}

}

void Ship::m_reset()
{
	getRigidBody()->isColliding = false;
	const int halfWidth = getWidth() * 0.5f;
	const auto xComponent = rand() % (640 - getWidth()) + halfWidth + 1;
	const auto yComponent = -getHeight();
	getTransform()->position = glm::vec2(xComponent, yComponent);
}

void Ship::m_changeDirection()
{
	const auto x = cos(m_currentHeading * Util::Deg2Rad);
	const auto y = sin(m_currentHeading * Util::Deg2Rad);
	m_currentDirection = glm::vec2(x, y);

	glm::vec2 size = TextureManager::Instance()->getTextureSize("ship");
}

void Ship::m_buildAnimations() {
	// Idle
	Animation idleAnimation = Animation();
	idleAnimation.name = "idle";
	
	std::string tmp_str = "player-idle-";
	for (int i = 0; i < 2; i++)
		idleAnimation.frames.push_back(getSpriteSheet()->getFrame(tmp_str + std::to_string(i)));
	setAnimation(idleAnimation);

	// Run
	Animation runAnimation = Animation();
	runAnimation.name = "run";

	tmp_str = "player-run-";
		for (int i = 0; i < 3; i++)
			runAnimation.frames.push_back(getSpriteSheet()->getFrame(tmp_str + std::to_string(i)));
	setAnimation(runAnimation);

	// Hurt
	Animation hurtAnimation = Animation();
	hurtAnimation.name = "hurt";

	tmp_str = "player-hurt-";
	for (int i = 0; i < 9; i++)
		hurtAnimation.frames.push_back(getSpriteSheet()->getFrame(tmp_str + std::to_string(i)));
	setAnimation(hurtAnimation);

	// Melee
	Animation meleeAnimation = Animation();
	meleeAnimation.name = "melee";

	tmp_str = "player-melee-";
	for (int i = 0; i < 3; i++)
		meleeAnimation.frames.push_back(getSpriteSheet()->getFrame(tmp_str + std::to_string(i)));
	setAnimation(meleeAnimation);
}

void Ship::updateRotation() {
	if (SDL_NumJoysticks() < 1) {
		int Delta_x, Delta_y,
			mouse_x, mouse_y;

		SDL_GetMouseState(&mouse_x, &mouse_y);
		Delta_x = getTransform()->position.x - mouse_x;
		Delta_y = getTransform()->position.y - mouse_y;

		m_currentHeading = (atan2(Delta_y, Delta_x) * 180.0000) / 3.14159265 + 180;
		m_currentDirection = { -Delta_x , -Delta_y };
	}
	else
	{
		int Delta_x, Delta_y,
			game_x, game_y;

		game_x = EventManager::Instance().getGameController(0)->RIGHT_STICK_X;
		game_y = EventManager::Instance().getGameController(0)->RIGHT_STICK_Y;
		Delta_x = getTransform()->position.x - game_x;
		Delta_y = getTransform()->position.y - game_y;

		m_currentHeading = (atan2(Delta_y, Delta_x) * 180.0000) / 3.14159265 + 180;
		m_currentDirection = { -Delta_x , -Delta_y };
	}
}

void Ship::shoot() {
	m_playerBullets.push_back(new Bullet(getTransform()->position, m_currentDirection, m_currentHeading));
	setAnimationState(PLAYER_MELEE);
}

void Ship::deleteBullet(int _pos) {
	delete m_playerBullets[_pos];
	m_playerBullets.shrink_to_fit();
}

void Ship::setAnimationState(const PlayerAnimationState new_state) { m_currentAnimationState = new_state; }
Bullet* Ship::getBullet() { return m_playerBullets.at(m_playerBullets.size() - 1); }