#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	/*TextureManager::Instance()->loadSpriteSheet("../Assets/sprites/tilesetCondensed.png", "tilesetAtlas", "tileset");*/


	if(EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();	
	}
	TextureManager::Instance()->load("../Assets/textures/enemiesLeft0.png", "enemiesLeft0");
	TextureManager::Instance()->load("../Assets/textures/enemiesLeft1.png", "enemiesLeft1");
	TextureManager::Instance()->load("../Assets/textures/enemiesLeft2.png", "enemiesLeft2");
	TextureManager::Instance()->load("../Assets/textures/enemiesLeft3.png", "enemiesLeft3");
	TextureManager::Instance()->load("../Assets/textures/enemiesLeft4.png", "enemiesLeft4");
	TextureManager::Instance()->draw("enemiesLeft4", 555, 40, 0, 255, true);
	drawDisplayList();
	
	
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();

	/*m_CheckEnemyLOS(m_pEnemy1, m_pPlayer);
	m_CheckEnemyLOS(m_pEnemy2, m_pPlayer);
	m_CheckEnemyLOS(m_pEnemy3, m_pPlayer);
	m_CheckEnemyLOS(m_pEnemy4, m_pPlayer);*/
	m_pProgress->setNumEnemies(m_pNumEnemies);
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_H))
	{
		m_pNumEnemies--;

	}
	
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_K))
	{
		/*m_pEnemy1->setAnimationState(DAMAGE);
		m_pEnemy2->setAnimationState(DAMAGE);
		m_pEnemy3->setAnimationState(DAMAGE);
		m_pEnemy4->setAnimationState(DAMAGE);*/
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_P))
	{
		/*isPatroling(m_pEnemy1);
		isPatroling(m_pEnemy2);
		isPatroling(m_pEnemy3);
		isPatroling(m_pEnemy4);*/
	}
	if (m_pProgress->getNumEnemies() == 3) {
		TextureManager::Instance()->draw("enemiesLeft3", 555, 40, 0, 255, true);
	}
	if (m_pProgress->getNumEnemies() == 2) {
		TextureManager::Instance()->draw("enemiesLeft2", 555, 40, 0, 255, true);
	}
	if (m_pProgress->getNumEnemies() == 1) {
		TextureManager::Instance()->draw("enemiesLeft1", 555, 40, 0, 255, true);
	}
	if (m_pProgress->getNumEnemies() == 0) {
		TextureManager::Instance()->draw("enemiesLeft0", 555, 40, 0, 255, true);
	}
	


	
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";
	//TextureManager::Instance()->draw("enemiesLeft4", 555, 40, 0, 255, true);
	// add the ship to the scene as a start point
	m_pShip = new Ship();
	m_pShip->getTransform()->position = glm::vec2(200.0f, 300.0f);
	addChild(m_pShip, 2);

	// add the Obstacle to the scene as a start point
	m_pObstacle1 = new Obstacle();
	m_pObstacle1->getTransform()->position = glm::vec2(400.0f, 300.0f);
	addChild(m_pObstacle1);

	// add the Obstacle to the scene as a start point
	m_pObstacle2 = new Obstacle();
	m_pObstacle2->getTransform()->position = glm::vec2(400.0f, 100.0f);
	addChild(m_pObstacle2);

	// add the Obstacle to the scene as a start point
	m_pObstacle3 = new Obstacle();
	m_pObstacle3->getTransform()->position = glm::vec2(600.0f, 500.0f);
	addChild(m_pObstacle3);
	
	// added the target to the scene a goal
	m_pTarget = new Target();
	m_pTarget->getTransform()->position = glm::vec2(600.0f, 300.0f);
	addChild(m_pTarget);

	const SDL_Color blue = { 0, 0, 255, 255 };
	m_pProgressLabel = new Label("Enemies left: ", "Consolas", 40, blue, glm::vec2(400.0f, 40.0f));
	m_pProgressLabel->setParent(this);
	addChild(m_pProgressLabel);

	m_pProgress = new ProgressTag();
	m_pProgress->getTransform()->position = glm::vec2(555.0f, 40.0f);
	addChild(m_pProgress);
	
	//m_buildGrid();
	//m_drawGrid();

}

void PlayScene::GUI_Function() 
{
	//TODO: We need to deal with this
	auto offset = glm::vec2(Config::TILE_SIZE * 0.5f, Config::TILE_SIZE * 0.5f);
	
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("GAME3001 - Assignment 3", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	// allow ship rotation
	static int angle;
	if(ImGui::SliderInt("Ship Direction", &angle, -360, 360))
	{
		m_pShip->setCurrentHeading(angle);
	}
	
	ImGui::Separator();

	static int shipPosition[] = { m_pShip->getTransform()->position.x, m_pShip->getTransform()->position.y };
	if (ImGui::SliderInt2("Ship Position", shipPosition, 0, 800))
	{
		m_pShip->getTransform()->position.x = shipPosition[0];
		m_pShip->getTransform()->position.y = shipPosition[1];
	}
	
	static int targetPosition[] = { m_pTarget->getTransform()->position.x, m_pTarget->getTransform()->position.y };
	if(ImGui::SliderInt2("Target Position", targetPosition, 0, 800))
	{
		m_pTarget->getTransform()->position.x = targetPosition[0];
		m_pTarget->getTransform()->position.y = targetPosition[1];
	}
	
	ImGui::Separator();
	
	if (ImGui::Button("Start"))
	{

	}

	ImGui::SameLine();
	
	if (ImGui::Button("Reset"))
	{
		// reset everything back to initial values
		
	}

	ImGui::Separator();

	
	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}

//void PlayScene::m_buildGrid()
//{
//	auto tileSize = Config::TILE_SIZE;
//
//	// add tiles to the grid
//	for (int row = 0; row < Config::ROW_NUM; ++row)
//	{
//		for (int col = 0; col < Config::COL_NUM; ++col)
//		{
//			Tile* tile = new Tile(); // create empty tile
//			tile->getTransform()->position = glm::vec2(col * tileSize, row * tileSize);
//			tile->setGridPosition(col, row);
//			addChild(tile);
//			tile->addLabels();
//			tile->setEnabled(false);
//			m_pGrid.push_back(tile);
//		}
//	}
//
//	// create references for each tile to its neighbours
//	for (int row = 0; row < Config::ROW_NUM; ++row)
//	{
//		for (int col = 0; col < Config::COL_NUM; ++col)
//		{
//			Tile* tile = m_getTile(col, row);
//
//			// Topmost row
//			if (row == 0)
//			{
//				tile->setNeighbourTile(TOP_TILE, nullptr);
//			}
//			else
//			{
//				tile->setNeighbourTile(TOP_TILE, m_getTile(col, row - 1));
//			}
//
//			// rightmost column
//			if (col == Config::COL_NUM - 1)
//			{
//				tile->setNeighbourTile(RIGHT_TILE, nullptr);
//			}
//			else
//			{
//				tile->setNeighbourTile(RIGHT_TILE, m_getTile(col + 1, row));
//			}
//
//			// bottommost row
//			if (row == Config::ROW_NUM - 1)
//			{
//				tile->setNeighbourTile(BOTTOM_TILE, nullptr);
//			}
//			else
//			{
//				tile->setNeighbourTile(BOTTOM_TILE, m_getTile(col, row + 1));
//			}
//
//			// leftmost  column
//			if (col == 0)
//			{
//				tile->setNeighbourTile(LEFT_TILE, nullptr);
//			}
//			else
//			{
//				tile->setNeighbourTile(LEFT_TILE, m_getTile(col - 1, row));
//			}
//		}
//	}
//
//	std::cout << m_pGrid.size() << std::endl;
//}
//
////void PlayScene::m_drawGrid() {
////	
////	m_getTile(0,0)->
////}
//
//Tile* PlayScene::m_getTile(const int col, const int row)
//{
//	return m_pGrid[(row * Config::COL_NUM) + col];
//}
//
//Tile* PlayScene::m_getTile(const glm::vec2 grid_position)
//{
//	const auto col = grid_position.x;
//	const auto row = grid_position.y;
//	return m_pGrid[(row * Config::COL_NUM) + col];
//}

//void PlayScene::m_CheckEnemyLOS(Enemy* enemy_object, DisplayObject* target_object)
//{
//	// if ship to target distance is less than or equal to LOS Distance
//	auto EnemyToTargetDistance = Util::distance(enemy_object->getTransform()->position, target_object->getTransform()->position);
//	if (EnemyToTargetDistance <= enemy_object->getLOSDistance())
//	{
//		std::vector<DisplayObject*> contactList;
//		for (auto object : getDisplayList())
//		{
//			// check if object is farther than than the target
//			auto EnemyToObjectDistance = Util::distance(enemy_object->getTransform()->position, object->getTransform()->position);
//
//			if (EnemyToObjectDistance <= EnemyToTargetDistance)
//			{
//				if ((object->getType() != enemy_object->getType()) && (object->getType() != target_object->getType()))
//				{
//					contactList.push_back(object);
//				}
//			}
//		}
//		contactList.push_back(target_object); // add the target to the end of the list
//		auto hasLOS = CollisionManager::LOSCheck(enemy_object->getTransform()->position,
//			enemy_object->getTransform()->position + enemy_object->getCurrentDirection() * enemy_object->getLOSDistance(), contactList, target_object);
//
//		enemy_object->setHasLOS(hasLOS);
//	}
//}
//
//void isPatroling(Enemy* enemy_object) {
//	if (enemy_object->getCurrentAnimationState() == PATROL) {
//		enemy_object->setAnimationState(IDLE);
//	}
//	if (enemy_object->getCurrentAnimationState() == IDLE) {
//		enemy_object->setAnimationState(PATROL);
//	}
//}
