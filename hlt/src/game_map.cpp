#include "game_map.hpp"

#include "../utils/input.hpp"
#include "../utils/constants.hpp"

#include <algorithm>

GameMap::GameMap(const int width, const int height) : m_width(width), m_height(height), m_cells(width, std::vector<MapCell>(height))
{
}

MapCell *GameMap::at(const Position &position)
{
  return &m_cells[position.getXCoord()][position.getYCoord()];
}

MapCell *GameMap::at(const Entity &entity)
{
  return (at(entity.getPosition()));
}

MapCell *GameMap::at(const Entity *entity)
{
  return at(entity->getPosition());
}

void GameMap::update()
{
  for (int x = 0; x < m_width; ++x)
  {
    for (int y = 0; y < m_height; ++y)
    {
      m_cells[x][y].markShip(false, false);
    }
  }
  int update_count;
  input::get_sstream() >> update_count;

  for (int i = 0; i < update_count; ++i)
  {
    int x, y, halite;
    input::get_sstream() >> x >> y >> halite;
    m_cells[x][y].setHalite(halite);
  }
}

std::shared_ptr<GameMap> GameMap::generate()
{
  int width, height;
  input::get_sstream() >> width >> height;

  std::shared_ptr<GameMap> map = std::make_shared<GameMap>(width, height);

  // The board is stored row by row
  for (int y = 0; y < map->m_height; ++y)
  {
    auto in = input::get_sstream();
    for (int x = 0; x < map->m_width; ++x)
    {
      int halite;
      in >> halite;

      map->m_cells[x][y] = MapCell(Position(x, y), halite);
      // To debug the generation
      // Commented by default otherwise there is to much data displayed in logs
      // custom_logger::log(Position(x, y).to_string() + ", halite : " + std::to_string(halite));
    }
  }
  return map;
}

Position GameMap::normalizePosition(int x, int y)
{
  int normalizedX = x;
  int normalizedY = y;
  if (x < 0)
  {
    normalizedX = m_width - 1 + x;
  }
  if (x >= m_width)
  {
    normalizedX = x - m_width;
  }
  if (y < 0)
  {
    normalizedY = m_height - 1 + y;
  }
  if (y >= m_height)
  {
    normalizedY = y - m_height;
  }
  return Position(normalizedX, normalizedY);
}

int GameMap::computeManathanDistance(Position p1, Position p2)
{
  int dx = abs(p1.getXCoord() - p2.getXCoord());
  int dy = abs(p1.getYCoord() - p2.getYCoord());

  if (dx > m_width / 2)
  {
    dx = m_width - dx;
  }

  if (dy > m_height / 2)
  {
    dy = m_height - dy;
  }
  return dx + dy;
}
// Getters
int GameMap::getWidth() const
{
  return m_width;
}

int GameMap::getHeight() const
{
  return m_height;
}

double GameMap::getCost(const Position &pos) const
{
  return (double)m_cells[pos.getXCoord()][pos.getYCoord()].getHalite() / (double)constants::MOVE_COST_RATIO;
}

int GameMap::getTotalHalite() const
{
  int totalHalite = 0;
  for (int i = 0; i < m_width; ++i)
  {
    for (int j = 0; j < m_height; ++j)
    {
      // totalHalite += GameMap::at(Position(i,j))->getHalite();
      totalHalite += m_cells[i][j].getHalite();
    }
  }
  return totalHalite;
}

std::vector<Position> GameMap::getPositionsInRadius(Position radiusCenter, int radius)
{
  // custom_logger::log("Looking for positions in radius with center " + radiusCenter.to_string());
  auto positionsInRaidus = std::vector<Position>();
  for (int i = radiusCenter.getXCoord() - radius; i < radiusCenter.getXCoord() + radius; ++i)
  {
    for (int j = radiusCenter.getYCoord() - radius; j < radiusCenter.getYCoord() + radius; ++j)
    {
      if (computeManathanDistance(radiusCenter, normalizePosition(i, j)))
      {
        // custom_logger::log("adding " + normalizePosition(i, j).to_string());
        positionsInRaidus.push_back(normalizePosition(i, j));
      }
    }
  }
  return positionsInRaidus;
}
