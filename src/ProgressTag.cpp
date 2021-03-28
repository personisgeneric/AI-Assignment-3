#include "ProgressTag.h"

ProgressTag::ProgressTag()
{
	TextureManager::Instance()->load("../Assets/textures/enemiesLeft0.png", "enemiesLeft0");
	TextureManager::Instance()->load("../Assets/textures/enemiesLeft1.png", "enemiesLeft1");
	TextureManager::Instance()->load("../Assets/textures/enemiesLeft2.png", "enemiesLeft2");
	TextureManager::Instance()->load("../Assets/textures/enemiesLeft3.png", "enemiesLeft3");
	TextureManager::Instance()->load("../Assets/textures/enemiesLeft4.png", "enemiesLeft4");
}

ProgressTag::~ProgressTag()
= default;

void ProgressTag::draw() {
	switch (numEnemies) {
	case 4:
		TextureManager::Instance()->draw("enemiesLeft4", 555, 40, 0, 255, true);
		break;
	case 3:
		TextureManager::Instance()->draw("enemiesLeft3", 555, 40, 0, 255, true);
		break;
	case 2:
		TextureManager::Instance()->draw("enemiesLeft2", 555, 40, 0, 255, true);
		break;
	case 1:
		TextureManager::Instance()->draw("enemiesLeft1", 555, 40, 0, 255, true);
		break;
	case 0:
		TextureManager::Instance()->draw("enemiesLeft0", 555, 40, 0, 255, true);
		break;
	default:
		TextureManager::Instance()->draw("enemiesLeft4", 555, 40, 0, 255, true);
		break;
	}
}
void ProgressTag::update()
{	
}

void ProgressTag::clean()
{
}