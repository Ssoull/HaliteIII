#include <algorithm>
#include "game_map.hpp"
#include "../utils/input.hpp"

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

// Getters
int GameMap::getWidth() const
{
  return m_width;
}

int GameMap::getHeight() const
{
  return m_height;
}
