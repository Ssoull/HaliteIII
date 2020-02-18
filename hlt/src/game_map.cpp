#include "game_map.hpp"

#include "../utils/input.hpp"

GameMap::GameMap()
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
  for (int y = 0; y < m_height; ++y)
  {
    for (int x = 0; x < m_width; ++x)
    {
      m_cells[y][x].markShip(false);
    }
  }
  int update_count;
  input::get_sstream() >> update_count;

  for (int i = 0; i < update_count; ++i)
  {
    int x, y, halite;
    input::get_sstream() >> x >> y >> halite;
    m_cells[y][x].setHalite(halite);
  }
}

std::shared_ptr<GameMap> GameMap::generate()
{
  std::shared_ptr<GameMap> map = std::make_shared<GameMap>();

  input::get_sstream() >> map->m_width >> map->m_height;

  map->m_cells.resize((size_t)map->m_height);
  for (int y = 0; y < map->m_height; ++y)
  {
    auto in = input::get_sstream();

    map->m_cells[y].reserve((size_t)map->m_width);
    for (int x = 0; x < map->m_width; ++x)
    {
      int halite;
      in >> halite;

      map->m_cells[y].push_back(MapCell(Position(x, y), halite));
    }
  }
  return map;
}