#pragma once
#ifndef __PROGRESS_TAG__
#define __PROGRESS_TAG__
#include "DisplayObject.h"
#include "TextureManager.h"

class ProgressTag : public DisplayObject {
public:
	ProgressTag();
	~ProgressTag();

	// Inherited via GameObject
	void draw() override;
	void update() override;
	void clean() override;

	void setNumEnemies(int n) { n = numEnemies; }
	int getNumEnemies() { return numEnemies; }

private:
	int numEnemies = 4;
};

#endif
