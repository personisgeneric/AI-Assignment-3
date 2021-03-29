#pragma once
#ifndef __HEALTH_BAR__
#define __HEALTH_BAR__
#include "DisplayObject.h"
#include "TextureManager.h"


class HealthBar : public DisplayObject {
public:
	HealthBar();
	~HealthBar();
	void draw() override;
	void update() override;
	void clean() override;
	
	void setHealth(int n) { health = n; }
	int getHealth() { return health; }

private:
	int health = 3;

};

#endif
