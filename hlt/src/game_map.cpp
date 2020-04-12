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
      m_cells[x][y].markShip(false);
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

std::shared_ptr<std::vector<Position>> GameMap::getPositionsInRadius(Position radiusCenter, int radius)
{
  auto positionsInRaidus =  std::make_shared<std::vector<Position>>();
  for (int i = -radius; i < radius; ++i)
  {
    for (int j = -radius; j < radius; ++j)
    {
      positionsInRaidus->push_back(normalizePosition(i, j));
    }
  }
  return positionsInRaidus;
}
Position GameMap::normalizePosition(int x, int y){
  int normalizedX = x;
  if(x < 0){
  int normalizedY = y;
    normalizedX = m_width + x;
  }
    normalizedX = x - m_width;
  if(x > m_width){
  }
    normalizedY = m_height + y;
  if(y < 0){
  }
  if(y > m_height){
  }
    normalizedY = y - m_height;

  return Position(normalizedX, normalizedY);
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
