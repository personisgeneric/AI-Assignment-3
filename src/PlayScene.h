#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Button.h"
#include "Label.h"
#include "Obstacle.h"
#include "ship.h"
#include "SpaceShip.h"
#include "Target.h"
#include "Enemy.h"
#include "Player.h"
#include "Tile.h"

struct Node {
	Tile* position;
	Node* next;
	Node() {};
	Node(Tile* value1, Node* next1 = nullptr) {
		position = value1;
		next = next1;
	}
};

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

	

private:
	// IMGUI Function
	void GUI_Function();
	std::string m_guiTitle;
	glm::vec2 m_mousePosition;
	bool m_isGridEnabled;

	std::vector<Tile*> m_pGrid;
	Tile* m_getTile(int col, int row);
	Tile* m_getTile(glm::vec2 grid_position);

	Node patrolPath1;
	Node patrolPath2;
	Node patrolPath3;
	Node patrolPath4;

	Target* m_pTarget;
	Ship* m_pShip;
	Obstacle* m_pObstacle1;
	Obstacle* m_pObstacle2;
	Obstacle* m_pObstacle3;
	Player* m_pPlayer;
	Enemy* m_pEnemy1;
	Enemy* m_pEnemy2;
	Enemy* m_pEnemy3;
	Enemy* m_pEnemy4;
	void m_CheckEnemyLOS(Enemy* enemy, DisplayObject* object);
	void m_buildGrid();
	void m_drawGrid();
};





#endif /* defined (__PLAY_SCENE__) */
