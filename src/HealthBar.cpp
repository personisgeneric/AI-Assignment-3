#include "HealthBar.h"


HealthBar::HealthBar() {
	TextureManager::Instance()->load("...Assets/Textures/HealthBar3.png", "healthbar3");
	TextureManager::Instance()->load("...Assets/Textures/HealthBar2.png", "healthbar2");
	TextureManager::Instance()->load("...Assets/Textures/HealthBar1.png", "healthbar1");
	TextureManager::Instance()->load("...Assets/Textures/HealthBar0.png", "healthbar0");

}

HealthBar::~HealthBar()
= default;

void HealthBar::draw() {
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;
	switch (health) {
	case 3:
		TextureManager::Instance()->draw("healthbar3", x, y, 0, 255, true);
		break;
	case 2:
		TextureManager::Instance()->draw("healthbar2", x, y, 0, 255, true);
		break;
	case 1:
		TextureManager::Instance()->draw("healthbar1", x, y, 0, 255, true);
		break;
	case 0:
		TextureManager::Instance()->draw("healthbar0", x, y, 0, 255, true);
		break;
	default:
		TextureManager::Instance()->draw("healthbar3", x, y, 0, 255, true);
		break;
	}
}

void HealthBar::update(){}
void HealthBar::clean(){}