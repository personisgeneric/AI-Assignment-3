#include "Tile.h"

#include <iomanip>
#include <sstream>

#include "Config.h"
#include "TextureManager.h"
#include "Util.h"

Tile::Tile() :m_cost(0.0f)
{
	setWidth(Config::TILE_SIZE);
	setHeight(Config::TILE_SIZE);
	
	
}

Tile::~Tile()
= default;

void Tile::draw()
{
	Util::DrawRect(getTransform()->position, getWidth(), getHeight());
}

void Tile::update()
{
}

void Tile::clean()
{
}

Tile* Tile::getNeighbourTile(const NeighbourTile position)
{
	return m_neighbours[position];
}

void Tile::setNeighbourTile(const NeighbourTile position, Tile* tile)
{
	m_neighbours[position] = tile;
}

float Tile::getTileCost() const
{
	return m_cost;
}

void Tile::setTileCost(const float cost)
{
	m_cost = cost;

	// format string to 1 decimal place
	std::stringstream stream;
	stream << std::fixed << std::setprecision(1) << cost;
	const std::string cost_string = stream.str();

	m_costLabel->setText(cost_string);
}

TileStatus Tile::getTileStatus() const
{
	return m_status;
}

void Tile::setTileStatus(const TileStatus status)
{

	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;
	m_status = status;

	/*switch (status)
	{
	case TOP_LEFT:
		TextureManager::Instance()->draw("topLeft", x, y, 0, 255, true);
		break;
	case TOP_MIDDLE:
		TextureManager::Instance()->draw("topMiddle", x, y, 0, 255, true);
		break;
	case TOP_RIGHT:
		TextureManager::Instance()->draw("topRight", x, y, 0, 255, true);
		break;
	case MIDDLE_LEFT:
		TextureManager::Instance()->draw("middleLeft", x, y, 0, 255, true);
		break;
	case MIDDLE_RIGHT:
		TextureManager::Instance()->draw("middleRight", x, y, 0, 255, true);
		break;
	case BOTTOM_LEFT:
		TextureManager::Instance()->draw("bottomLeft", x, y, 0, 255, true);
		break;
	case BOTTOM_MIDDLE:
		TextureManager::Instance()->draw("bottomMiddle", x, y, 0, 255, true);
		break;
	case BOTTOM_RIGHT:
		TextureManager::Instance()->draw("bottomRight", x, y, 0, 255, true);
		break;
	case IMPASSABLE:
		m_statusLabel->setText("I");
		break;

	}*/
}

void Tile::addLabels()
{
	auto offset = glm::vec2(Config::TILE_SIZE * 0.5f, Config::TILE_SIZE * 0.5f);
	
	m_costLabel = new Label("99.9", "Consolas", 12);
	m_costLabel->getTransform()->position = getTransform()->position + offset + glm::vec2(0.0f, -6.0f);
	getParent()->addChild(m_costLabel);
	m_costLabel->setEnabled(false);

	m_statusLabel = new Label("--", "Consolas", 12);
	m_statusLabel->getTransform()->position = getTransform()->position + offset + glm::vec2(0.0f, 6.0f);;
	getParent()->addChild(m_statusLabel);
	m_statusLabel->setEnabled(false);
}

void Tile::setLabelsEnabled(const bool state)
{
	m_costLabel->setEnabled(state);
	m_statusLabel->setEnabled(state);
}

